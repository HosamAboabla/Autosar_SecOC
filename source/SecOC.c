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
#include "Pdur_CanTP.h"

#include <string.h>

extern SecOC_TxPduProcessingType SecOC_TxPduProcessing;


static PduInfoType SecOC_Buffer[SECOC_BUFFERLENGTH];

PduInfoType SecOC_Buffer_Rx[SECOC_BUFFERLENGTH] = { {NULL, 0}};






extern SecOC_TxAuthenticPduLayerType SecOC_TxAuthenticPduLayer;
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
    uint8 FreshnessVal[SECOC_TX_FRESHNESS_VALUE_LENGTH] = {0};
    uint32 FreshnesslenBits = SecOC_TxPduProcessing.SecOCFreshnessValueLength;

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

    // Authenticator generation
    uint8  authenticatorPtr[SECOC_AUTHENTICATOR_MAX_LENGTH];
    uint32  authenticatorLen = BIT_TO_BYTES(SecOC_TxPduProcessing.SecOCAuthInfoTruncLength);
    result = generateMAC(TxPduId, DataToAuth, &DataToAuthLen, authenticatorPtr, &authenticatorLen);

    // Create secured IPDU
    SecPdu->MetaDataPtr = AuthPdu->MetaDataPtr;
    SecPdu->SduLength = SECOC_SECPDU_MAX_LENGTH;

    // Truncated freshness value
    uint8 FreshnessVal[SECOC_TX_FRESHNESS_VALUE_TRUNC_LENGTH] = {0};
    uint32 FreshnesslenBits = SecOC_TxPduProcessing.SecOCFreshnessValueTruncLength;
    result = SecOC_GetTxFreshness(TxPduId, FreshnessVal, &FreshnesslenBits);

    uint32 FreshnesslenBytes = BIT_TO_BYTES(SecOC_TxPduProcessing.SecOCFreshnessValueTruncLength);

    // SECURED = HEADER(OPTIONAL) + AuthPdu + TruncatedFreshnessValue(OPTIONAL) + Authenticator
    PduLengthType SecPduLen = 0;

    // AuthPdu
    memcpy(SecPdu->SduDataPtr, AuthPdu->SduDataPtr, AuthPdu->SduLength);
    SecPduLen += AuthPdu->SduLength;

    // TruncatedFreshnessValue
    memcpy(&SecPdu->SduDataPtr[SecPduLen], FreshnessVal, FreshnesslenBytes);
    SecPduLen += FreshnesslenBytes;

    // Authenticator
    memcpy(&SecPdu->SduDataPtr[SecPduLen], authenticatorPtr, authenticatorLen);
    SecPduLen += authenticatorLen;
    
    SecPdu->SduLength = SecPduLen;

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

void SecOC_MainFunctionRx(void)
{
    PduIdType idx = 0;
    SecOC_VerificationResultType result ,macResult;
    extern SecOC_RxPduProcessingType SecOC_RxPduProcessing; 

    
    for (idx = 0 ; idx < SECOC_BUFFERLENGTH ; idx++) {
        // check if there is data
        if ( SecOC_Buffer_Rx[idx].SduLength > 0 ) {
            
            result = verify(idx , &SecOC_Buffer_Rx[idx] ,&SecOC_RxPduProcessing ,&macResult);
            if( result == SECOC_VERIFICATIONSUCCESS )
            {
                PduR_SecOCIfRxIndication(idx,  &SecOC_Buffer_Rx[idx]);
            }

        }
    }

}

void SecOC_TpTxConfirmation(PduIdType TxPduId,Std_ReturnType result)
{
    if (result == E_OK) {
        // clear buffer
        SecOC_Buffer[TxPduId].MetaDataPtr = NULL;
        SecOC_Buffer[TxPduId].SduDataPtr = NULL;
        SecOC_Buffer[TxPduId].SduLength = 0;
    }

    if (SecOC_TxAuthenticPduLayer.SecOCPduType == SECOC_TPPDU)
    {
        PduR_SecOCTpTxConfirmation(TxPduId, result);
    }
    else if (SecOC_TxAuthenticPduLayer.SecOCPduType == SECOC_IFPDU)
    {
        PduR_SecOCIfTxConfirmation(TxPduId, result);
    }
    else
    {
        // DET Report Error
    }

}

// #if (SECOC_USE_TX_CONFIRMATION == 1)
//     void SecOc_SPduTxConfirmation(uint16 SecOCFreshnessValueID) {
//         /* Specific User's Code need to be written here*/
//     }
// #endif




void SecOC_RxIndication (PduIdType RxPduId, const PduInfoType* PduInfoPtr)
{   /* The SecOC copies the Authentic I-PDU to its own buffer */
    if (RxPduId < SECOC_BUFFERLENGTH) SecOC_Buffer_Rx[RxPduId] = *PduInfoPtr;
}




Std_ReturnType SecOC_GetTxFreshnessTruncData (uint16 SecOCFreshnessValueID,uint8* SecOCFreshnessValue,
uint32* SecOCFreshnessValueLength,uint8* SecOCTruncatedFreshnessValue,uint32* SecOCTruncatedFreshnessValueLength) 
{
    Std_ReturnType result = FVM_GetTxFreshnessTruncData(SecOCFreshnessValueID, SecOCFreshnessValue , SecOCFreshnessValueLength,
    SecOCTruncatedFreshnessValue, SecOCTruncatedFreshnessValueLength);
    return result;
}


Std_ReturnType SecOC_GetRxFreshness(uint16 SecOCFreshnessValueID,const uint8* SecOCTruncatedFreshnessValue,uint32 SecOCTruncatedFreshnessValueLength,
    uint16 SecOCAuthVerifyAttempts,uint8* SecOCFreshnessValue,uint32* SecOCFreshnessValueLength)
{
    FVM_GetRxFreshness(SecOCFreshnessValueID,SecOCTruncatedFreshnessValue,SecOCTruncatedFreshnessValueLength,
    SecOCAuthVerifyAttempts,SecOCFreshnessValue,SecOCFreshnessValueLength);
}


Std_ReturnType construct_RX_DataToAuthenticator(PduIdType RxPduId, PduInfoType* secPdu,SecOC_RxPduProcessingType *SecOCRxPduProcessing, uint8 *DataToAuth, uint32 *DataToAuthLen, uint8 *TruncatedLength_Bytes)
{
    //*DataToAuthLen = 0;
	//copy the Id to buffer Data to Auth
    memcpy(&DataToAuth[*DataToAuthLen], &RxPduId, sizeof(RxPduId));
    *DataToAuthLen += sizeof(RxPduId);	

    // copy the data to buffer Data to Auth
    memcpy(&DataToAuth[*DataToAuthLen], (secPdu->SduDataPtr), SECOC_AUTHPDU_MAX_LENGTH);
    *DataToAuthLen += SECOC_AUTHPDU_MAX_LENGTH;

    uint32 SecOCFreshnessValueLength = SECOC_FRESHNESS_MAX_LENGTH;
    uint8 SecOCFreshnessValue[SECOC_FRESHNESS_MAX_LENGTH / 8] = {0};
    const uint8* SecOCTruncatedFreshnessValue = (secPdu->SduDataPtr+SECOC_AUTHPDU_MAX_LENGTH);
    uint32 SecOCTruncatedFreshnessValueLength = SecOCRxPduProcessing->SecOCFreshnessValueTruncLength;
    *TruncatedLength_Bytes = BIT_TO_BYTES(SecOCTruncatedFreshnessValueLength);
    Std_ReturnType Freshness_result;
    uint16 authVeriAttempts = 0;
    // Std_ReturnType Freshness_result = E_OK;

    Freshness_result = SecOC_GetRxFreshness(SecOCRxPduProcessing->SecOCFreshnessValueId,
    SecOCTruncatedFreshnessValue, SecOCTruncatedFreshnessValueLength, authVeriAttempts,
    SecOCFreshnessValue, &SecOCFreshnessValueLength);

    // copy the freshness value to buffer Data to Auth
    memcpy(&DataToAuth[*DataToAuthLen], SecOCFreshnessValue, BIT_TO_BYTES(SecOCFreshnessValueLength));
    *DataToAuthLen += (BIT_TO_BYTES(SecOCFreshnessValueLength));

    return Freshness_result;
}

// header - auth_data - Freshness - MAC
Std_ReturnType verify(PduIdType RxPduId, PduInfoType* SecPdu, SecOC_RxPduProcessingType *SecOCRxPduProcessing, SecOC_VerificationResultType *verification_result)
{
    uint8 DataToAuth[SECOC_RX_DATA_TO_AUTHENTICATOR_LENGTH] = {0};  // CAN payload
    uint32 DataToAuthLen = 0;
    uint8 TruncatedLength_Bytes;
    
    Std_ReturnType FV_result = construct_RX_DataToAuthenticator(RxPduId, SecPdu, SecOCRxPduProcessing, DataToAuth, &DataToAuthLen, &TruncatedLength_Bytes);

    uint32 mac_length_bit = SecOCRxPduProcessing->SecOCAuthInfoTruncLength;
    uint8 mac[SECOC_AUTHENTICATOR_MAX_LENGTH / 8] = {0};
    // copy mac from secured data to MAC buffer
    memcpy(mac, (SecPdu->SduDataPtr+SECOC_AUTHPDU_MAX_LENGTH+TruncatedLength_Bytes), BIT_TO_BYTES(mac_length_bit));

    SecOC_VerificationResultType result;
    Crypto_VerifyResultType verify_var;

    if(FV_result == E_OK)
    {
        Std_ReturnType Mac_verify = Csm_MacVerify(SecOCRxPduProcessing->SecOCDataId, Crypto_stub, DataToAuth, DataToAuthLen, mac, mac_length_bit, &verify_var);
        if (Mac_verify == E_OK) 
        {
            *verification_result = CRYPTO_E_VER_OK;
            SecPdu->SduLength = SECOC_AUTHPDU_MAX_LENGTH;
            result = SECOC_VERIFICATIONSUCCESS;
        }
        else 
        {
            // drop message
            SecPdu->SduDataPtr = NULL;
            SecPdu->SduLength = 0;
            *verification_result = CRYPTO_E_VER_NOT_OK;
            result = SECOC_VERIFICATIONFAILURE;
        }
    }
    else
    {
        // drop message
        SecPdu->SduDataPtr = NULL;
        SecPdu->SduLength = 0;
        result = SECOC_FRESHNESSFAILURE;
    }
    return result;
}

void SecOC_test()
{
    
}

