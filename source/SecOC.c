/* "Copyright [2022/2023] <Tanta University>" */
#include "SecOC_Lcfg.h"
#include "SecOC_Cfg.h"
#include "SecOC_PBcfg.h"
#include "SecOC_Cbk.h"
#include "ComStack_Types.h"
#include "Rte_SecOC.h"
#include "SecOC.h"
#include "PduR_SecOC.h"
#include "Csm.h"
#include "Rte_SecOC_Type.h"
#include "PduR_Com.h"
#include "PduR_SecOC.h"


#include <string.h>

extern SecOC_TxPduProcessingType SecOC_TxPduProcessing;

static PduInfoType SecOC_Buffer[SECOC_BUFFERLENGTH];
/*
#define SECOC_CAN_DATAFRAME_MAX ((uint8)8)
#define SECOC_CAN_DATA_MAX      ((uint16)(SECOC_CAN_DATAFRAME_MAX - (SECOC_AUTH_INFO_TRUNC_LENGTH / 8)))

#define SECOC_SDATA_MAX         ((uint8)4)
#define SECOC_FRESHNESS_MAX     ((uint8)16)
#define SECOC_MACLEN_MAX        ((uint8)32)
*/

/****************************************************
 *          * Function Info *                           *
 *                                                      *
 * Function_Name        : constructDataToAuthenticator  *
 * Function_Index       : SecOC internal                *
 * Parameter in         : TxPduId                       *
 * Parameter in/out     : DataToAuth                    *
 * Parameter in/out     : DataToAuthLen                 *
 * Parameter in         : AuthPdu                       *
 * Function_Descripton  : This function constructs the  *
 * DataToAuthenticator using Data Identifier, secured   *
 * part of the * Authentic I-PDU, and freshness value   *
 *******************************************************/
static Std_ReturnType constructDataToAuthenticator(const PduIdType TxPduId, uint8 *DataToAuth, uint32 *DataToAuthLen, const PduInfoType* AuthPdu)
{
    Std_ReturnType result;
    *DataToAuthLen = 0;

    // Data Identifier
    memcpy(&DataToAuth[*DataToAuthLen], &TxPduId, sizeof(TxPduId));
    *DataToAuthLen += sizeof(TxPduId);

    // secured part of the Authentic I-PDU
    memcpy(&DataToAuth[*DataToAuthLen], AuthPdu->SduDataPtr, AuthPdu->SduLength);
    *DataToAuthLen += AuthPdu->SduLength;
    
    // Complete Freshness Value
    uint8 FreshnessVal[SECOC_TX_FRESHNESS_VALUE_LENGTH] ={0};
    uint32 FreshnesslenBits = SecOC_TxPduProcessing.SecOCFreshnessValueLength * 8;

    result = SecOC_GetTxFreshness(TxPduId, FreshnessVal, &FreshnesslenBits);
    if(result != E_OK)
    {
        return result;
    }

    uint32 FreshnesslenBytes = BIT_TO_BYTES(FreshnesslenBits);

    memcpy(&DataToAuth[*DataToAuthLen], &FreshnessVal[SecOC_TxPduProcessing.SecOCFreshnessValueLength - FreshnesslenBytes], FreshnesslenBytes);
    *DataToAuthLen += FreshnesslenBytes;

    return E_OK;
}

/*******************************************************
 *          * Function Info *                           *
 *                                                      *
 * Function_Name            : generateMAC               *
 * Function_Index           : SecOC internal            *
 * Parameter in             : TxPduId                   *
 * Parameter in             : DataToAuth                *
 * Parameter in             : DataToAuthLen             *
 * Parameter in/out         : authenticatorPtr          *
 * Parameter in/out         : authenticatorLen          *
 * Function_Descripton  : This function generates MAC   *
 * based on the DataToAuthenticator                     *
 *******************************************************/
static Std_ReturnType generateMAC(const PduIdType TxPduId, uint8 const *DataToAuth, const uint32 *DataToAuthLen, uint8  *authenticatorPtr, uint32  *authenticatorLen)
{
    Std_ReturnType result;

    *authenticatorLen = BIT_TO_BYTES(*authenticatorLen);
    result = Csm_MacGenerate(TxPduId, 0, DataToAuth, *DataToAuthLen, authenticatorPtr, authenticatorLen);

    return result;
}

/********************************************************
 *          * Function Info *                           *
 *                                                      *
 * Function_Name        : authenticate                  *
 * Function_Index       : SecOC internal                *
 * Parameter in         : TxPduId                       *
 * Parameter in         : AuthPdu                       *
 * Parameter out        : SecPdu                        * 
 * Function_Descripton  : This function generates the   *
 * secured PDU using authenticator, payload, freshness  * 
 *  value                                               *
 *******************************************************/
static Std_ReturnType authenticate(const PduIdType TxPduId, const PduInfoType* AuthPdu, PduInfoType* SecPdu)
{
    Std_ReturnType result;
    
    // DataToAuthenticator = Data Identifier | secured part of the Authentic I-PDU | Complete Freshness Value
    uint8 DataToAuth[SECOC_TX_DATA_TO_AUTHENTICATOR_LENGTH];
    uint32 DataToAuthLen = 0;
    result = constructDataToAuthenticator(TxPduId, DataToAuth, &DataToAuthLen, AuthPdu);

    // MAC generation
    uint8  authenticatorPtr[SECOC_AUTHENTICATOR_MAX_LENGTH];
    uint32  authenticatorLen = SecOC_TxPduProcessing.SecOCAuthInfoTruncLength ;
    result = generateMAC(TxPduId, DataToAuth, &DataToAuthLen, authenticatorPtr, &authenticatorLen);

    // Create secured IPDU
    SecPdu->MetaDataPtr = AuthPdu->MetaDataPtr;
    SecPdu->SduLength = SECOC_SECPDU_MAX_LENGTH;

    // SECURED = HEADER(OPTIONAL) + AuthPdu + FreshnessValue(OPTIONAL) + Authenticator
    memcpy(SecPdu->SduDataPtr, AuthPdu->SduDataPtr, AuthPdu->SduLength);
    memcpy(&SecPdu->SduDataPtr[AuthPdu->SduLength], authenticatorPtr, authenticatorLen);        


   return result;
}


Std_ReturnType SecOC_IfTransmit(PduIdType TxPduId, const PduInfoType* PduInfoPtr) {
    Std_ReturnType result = E_OK;
    if (TxPduId < SECOC_BUFFERLENGTH) {
        SecOC_Buffer[TxPduId] = *PduInfoPtr;
    } else {
        result = E_NOT_OK;
    }

    return result;
}


void SecOC_TxConfirmation(PduIdType TxPduId, Std_ReturnType result) {
    if (result == E_OK) {
        // clear buffer
        SecOC_Buffer[TxPduId].MetaDataPtr = NULL;
        SecOC_Buffer[TxPduId].SduDataPtr = NULL;
        SecOC_Buffer[TxPduId].SduLength = 0;
    }
    PduR_SecOCIfTxConfirmation(TxPduId, result);
}



Std_ReturnType SecOC_GetTxFreshness(uint16 SecOCFreshnessValueID, uint8* SecOCFreshnessValue,
uint32* SecOCFreshnessValueLength) {
    SecOC_GetTxFreshnessCalloutType PTR = (SecOC_GetTxFreshnessCalloutType)FVM_GetTxFreshness;
Std_ReturnType result = PTR(SecOCFreshnessValueID, SecOCFreshnessValue, SecOCFreshnessValueLength);
    return result;
}





SecOC_StateType SecOc_State = SECOC_UNINIT;

const SecOC_GeneralType* tmpSecOCGeneral;
const SecOC_RxPduProcessingType* tmpSecOCRxPduProcessing;
const SecOC_TxPduProcessingType* tmpSecOCTxPduProcessing;

static Std_VersionInfoType _SecOC_VersionInfo ={(uint16)1,(uint16) 1,(uint8)1,(uint8)0,(uint8)0};

#if (SECOC_ERROR_DETECT == STD_ON)
#define VALIDATE_STATE_INIT()\
	if(SECOC_INIT!=SecOc_State){\
		Det_ReportError(); \
		return; \
	}

#else
#define VALIDATE_STATE_INIT(_api)
#endif



uint8 success=1;
void SecOC_Init(const SecOC_ConfigType *config)
{
    tmpSecOCGeneral = config->general;
    tmpSecOCTxPduProcessing = config->secOCTxPduProcessings;
    tmpSecOCRxPduProcessing = config->secOCRxPduProcessings;
    if(!success)
    {
        SecOc_State = SECOC_E_UNINIT;        
    }                                   
    SecOc_State = SECOC_INIT;
}                   


void SecOC_GetVersionInfo (Std_VersionInfoType* versioninfo)
{

    VALIDATE_STATE_INIT();
    memcpy(versioninfo, &_SecOC_VersionInfo, sizeof(Std_VersionInfoType));//copy from source to distination with the length
}


extern void SecOC_MainFunctionTx(void) {
    // check if initialized or not;
    if (SecOc_State == SECOC_UNINIT) {
        // cppcheck-suppress misra-c2012-15.5
        return;
    }
    PduIdType idx;
    PduInfoType transmitPduInfo;
    uint8 temp[8];
    transmitPduInfo.SduDataPtr = temp;
    

    
    
    for (idx = 0 ; idx < SECOC_BUFFERLENGTH ; idx++) {
        // check if there is data
        if ( SecOC_Buffer[idx].SduLength > 0 ) {
            authenticate(idx , &SecOC_Buffer[idx] , &transmitPduInfo);
            PduR_SecOCTransmit(idx , &transmitPduInfo);

        }
    }
}




// #if (SECOC_USE_TX_CONFIRMATION == 1)
//     void SecOc_SPduTxConfirmation(uint16 SecOCFreshnessValueID) {
//         /* Specific User's Code need to be written here*/
//     }
// #endif

/*
#define MAX_COUNTER_FRESHNESS_IDS   10

Std_ReturnType SecOC_GetTxFreshnessTruncData (uint16 SecOCFreshnessValueID,uint8* SecOCFreshnessValue,
uint32* SecOCFreshnessValueLength,uint8* SecOCTruncatedFreshnessValue,uint32* SecOCTruncatedFreshnessValueLength) 
{
    Std_ReturnType result = E_OK; 
    if (SecOCFreshnessValueID > (MAX_COUNTER_FRESHNESS_IDS-1)) 
    {
        result = E_NOT_OK;
    }
    else if (SecOCTruncatedFreshnessValueLength > SECOC_MAX_FRESHNESS_SIZE) 
    {
        result = E_NOT_OK;
    }
    SecOC_FreshnessArrayType counter[MAX_COUNTER_FRESHNESS_IDS] = {0};
    uint32 Datalength = SECOC_MAX_FRESHNESS_SIZE - (*SecOCTruncatedFreshnessValueLength);
    
    int DataIndex = (SECOC_MAX_FRESHNESS_SIZE - 1); 
    uint8 big_End_index =0;
    for ( ; ((DataIndex >= Datalength) && (big_End_index < (*SecOCTruncatedFreshnessValueLength))); DataIndex-- , big_End_index++) 
    {
        SecOCTruncatedFreshnessValue[big_End_index] = counter[SecOCFreshnessValueID][DataIndex];
    }
    return result;
}
*/
#include <stdio.h>
void SecOC_test()
{
   // uint8_t adata[100] = "hello, world";
    uint8_t adata[100] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    uint8_t sdata[100];
    PduInfoType AuthPdu, SecPdu;
    AuthPdu.SduDataPtr = adata;
    AuthPdu.SduLength = SECOC_AUTHPDU_MAX_LENGTH;
    SecPdu.SduDataPtr = sdata;
    SecPdu.SduLength = SECOC_SECPDU_MAX_LENGTH;
    
    for(int i = 0; i < AuthPdu.SduLength; i++)
        printf("%d ", AuthPdu.SduDataPtr[i]);
    printf("\n");

    authenticate(0, &AuthPdu, &SecPdu);

    for(int i = 0; i < SecPdu.SduLength; i++)
        printf("%d ", SecPdu.SduDataPtr[i]);
    printf("\n");
    printf("done");
    
}