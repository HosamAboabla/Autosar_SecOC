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
#include <stdio.h>



static PduInfoType SecOC_Buffer[SECOC_BUFFERLENGTH] = { { NULL , 0} };

#define SECOC_CAN_DATAFRAME_MAX ((uint8)8)
#define SECOC_CAN_DATA_MAX      ((uint16)(SECOC_CAN_DATAFRAME_MAX - (SECOC_AUTH_INFO_TRUNC_LENGTH / 8)))

#define SECOC_SDATA_MAX         ((uint8)4)
#define SECOC_FRESHNESS_MAX     ((uint8)16)
#define SECOC_MACLEN_MAX        ((uint8)32)

/****************************************************
 *          * Function Info *                           *
 *                                                      *
 * Function_Name        : authenticate                  *
 * Function_Index       : SecOC internal                *
 * Parameter in         : TxPduId                       *
 * Function_Descripton  : The lower layer communication * 
 * interface module confirms  the transmission of a PDU *
 *        or the failure to transmit a PDU              *
 ***************************************************/
static Std_ReturnType authenticate(const PduIdType TxPduId, const PduInfoType* AuthPdu, PduInfoType* SecPdu)
{
    Std_ReturnType result;
    // 1. Prepare Secured I-PDU
    // 2. Construct Data for Authenticator
    uint8 DataToAuth[sizeof(TxPduId) + SECOC_SDATA_MAX + SECOC_FRESHNESS_MAX]; // CAN payload
    uint32 DataToAuthLen = 0;

    // DataToAuthenticator = Data Identifier | secured part of the Authentic I-PDU | Complete Freshness Value

    // Data Identifier
    memcpy(&DataToAuth[DataToAuthLen], &TxPduId, sizeof(TxPduId));
    DataToAuthLen += sizeof(TxPduId);

    // secured part of the Authentic I-PDU
    memcpy(&DataToAuth[DataToAuthLen], AuthPdu->SduDataPtr, AuthPdu->SduLength);
    DataToAuthLen += AuthPdu->SduLength;
    
    // Complete Freshness Value
    uint8 FreshnessVal[SECOC_FRESHNESS_MAX] ={0};
    uint32 FreshnesslenBits = SECOC_FRESHNESS_MAX * 8;

    result = SecOC_GetTxFreshness(TxPduId, FreshnessVal, &FreshnesslenBits);
    if(result != E_OK)
    {
        return result;
    }

    uint32 FreshnesslenBytes = BIT_TO_BYTES(FreshnesslenBits);

    memcpy(&DataToAuth[DataToAuthLen], &FreshnessVal[SECOC_FRESHNESS_MAX - FreshnesslenBytes], FreshnesslenBytes);
    DataToAuthLen += FreshnesslenBytes;

    // MAC generation
    uint8  authenticatorPtr[SECOC_MACLEN_MAX];
    uint32  authenticatorLen = SECOC_AUTH_INFO_TRUNC_LENGTH / 8;
    result = Csm_MacGenerate(TxPduId, 0, DataToAuth, DataToAuthLen, authenticatorPtr, &authenticatorLen);

    if(result != E_OK)
    {
        return result;
    }
    // Create secured IPDU
    SecPdu->MetaDataPtr = AuthPdu->MetaDataPtr;
    SecPdu->SduLength = SECOC_CAN_DATAFRAME_MAX;

    memcpy(SecPdu->SduDataPtr, AuthPdu->SduDataPtr, SECOC_CAN_DATA_MAX);
    memcpy(&SecPdu->SduDataPtr[SECOC_CAN_DATA_MAX], authenticatorPtr, authenticatorLen);        


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
        // SecOC_Buffer[TxPduId] = NULL;
        // clear buffer
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
    PduIdType idx = 0;
    PduInfoType transmitPduInfo;
    uint8 temp[8];
    transmitPduInfo.SduDataPtr = temp;
    authenticate(0 , &SecOC_Buffer[0] , &transmitPduInfo);

    PduR_SecOCTransmit(idx , &transmitPduInfo);
    // for ( ; idx < SECOC_BUFFERLENGTH ; idx++) {
    //     // check if there is data
    //     if ( SecOC_Buffer[idx].SduLength > 0 ) {
    //         // authenticate SecOC_Buffer[idx];
    //         // send authenticated data
    //         // authenticate( SecOC_Buffer[idx] , &transmitPduInfo)
    //         PduR_SecOCTransmit(idx , &transmitPduInfo);

    //     } else {
    //     }
    // }
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

Std_ReturnType verify(PduIdType RxPduId, PduInfoType* SPDU, SecOC_RxPduProcessingType SecOCRxPduProcessing, SecOC_VerificationResultType *verification_result)
{
    uint8 SecOCFreshnessValue[SECOC_FRESHNESS_MAX];
	uint32 SecOCFreshnessValueLength = SECOC_FRESHNESS_MAX;
    uint32 SecOCTruncatedFreshnessValueLength = SECOC_FRESHNESS_MAX;
    uint8 SecOCTruncatedFreshnessValue[SECOC_FRESHNESS_MAX];
    uint8 SecOCAuthDataFreshnessValue[SECOC_FRESHNESS_MAX];
    uint16 SecOCAuthDataFreshnessValueLength = SECOC_FRESHNESS_MAX;
    uint16 attempts = 0;
    uint8 mac[SECOC_MACLEN_MAX];
	uint32 mac_length = BIT_TO_BYTES(SECOC_MACLEN_MAX);
    Std_ReturnType Freshness_result;

    // waiting implemention function of freshness
    // if (tmpSecOCGeneral->SecOCQueryFreshnessValue == SECOC_CFUNC) 
    // {
    //     if (SecOCRxPduProcessing.SecOCUseAuthDataFreshness == TRUE) 
    //     {
    //         Freshness_result = SecOC_GetRxFreshnessAuthData(SecOCRxPduProcessing.SecOCFreshnessValueId,
    //         SecOCTruncatedFreshnessValue, SecOCTruncatedFreshnessValueLength,SecOCAuthDataFreshnessValue, 
    //         SecOCAuthDataFreshnessValueLength, attempts, SecOCFreshnessValue, &SecOCFreshnessValueLength);
    //     } 
    //     else 
    //     {
    //         Freshness_result = SecOC_GetRxFreshness(SecOCRxPduProcessing.SecOCFreshnessValueId,
    //         SecOCTruncatedFreshnessValue, SecOCTruncatedFreshnessValueLength, attempts,
    //         SecOCFreshnessValue, &SecOCFreshnessValueLength);
    //     }

    // }

    uint8 DataToAuth[sizeof(RxPduId) + SECOC_SDATA_MAX + SECOC_FRESHNESS_MAX];  // CAN payload
    uint32 DataToAuthLen = 0;

    printf("id = %d & len = %d\n",RxPduId,sizeof(RxPduId));

    // copy the Id to buffer Data to Auth
    memcpy(&DataToAuth[DataToAuthLen], &RxPduId, sizeof(RxPduId));
    DataToAuthLen += sizeof(RxPduId);

    for(uint8 i =0 ;i<DataToAuthLen;i++)
    {
    	printf("%d",DataToAuth[i]);
    	fflush(stdin); fflush(stdout);
    }
    printf("\n");

    // copy the data to buffer Data to Auth
    memcpy(&DataToAuth[DataToAuthLen], (SPDU->SduDataPtr), SECOC_SDATA_MAX);
    DataToAuthLen += SECOC_SDATA_MAX;

    for(uint8 i =0 ;i<DataToAuthLen;i++)
    {
    	printf("%d",DataToAuth[i]);
    	fflush(stdin); fflush(stdout);
    }
    printf("\n");

    
    // copy the freshness value to buffer Data to Auth
    memcpy(&DataToAuth[DataToAuthLen], SecOCFreshnessValue, BIT_TO_BYTES(SecOCFreshnessValueLength));
    DataToAuthLen += (BIT_TO_BYTES(SecOCFreshnessValueLength));



    // copy mac from secured data to MAC buffer
    memcpy(mac, (SPDU->SduDataPtr+SECOC_SDATA_MAX), mac_length);
    for(uint8 i=0;i<mac_length;i++)
    {
    	printf("%d",mac[i]);
    	fflush(stdin); fflush(stdout);
    }
    printf("\n");


    SecOC_VerificationResultType result;
    Crypto_VerifyResultType verify_var;

    if (Freshness_result == E_OK) 
    {
        Std_ReturnType Mac_verify = Csm_MacVerify(RxPduId, 0, DataToAuth, DataToAuthLen, mac, (mac_length)*8, &verify_var);
        if (Mac_verify == E_OK) 
        {
            *verification_result = CRYPTO_E_VER_OK;
            uint8 clear_buffer[(BIT_TO_BYTES(SECOC_MACLEN_MAX))] = {0};
            memcpy((SPDU->SduDataPtr+SECOC_SDATA_MAX), clear_buffer, mac_length);
            SPDU->SduLength = SECOC_SDATA_MAX;
            result = SECOC_VERIFICATIONSUCCESS;
        }
        else 
        {
            *verification_result = CRYPTO_E_VER_NOT_OK;
            result = SECOC_VERIFICATIONFAILURE;
        }
    }

    else
    {
        result = SECOC_VERIFICATIONFAILURE;
    }
    return result;
}

void SecOC_test()
{
    #define MAX 16
    uint8 x[MAX]={2,0,0,0,1,1,1,1,1};
    uint8 MAC[32];
    uint8 csm[4]={83,47,198,102};
    uint32 MAC_Length = 4;
    Csm_MacGenerate(10,0,x,MAX,MAC,&MAC_Length);
    for(int i =0 ; i<MAC_Length;i++)
    {
        printf("%d\t",MAC[i]);
    }
    printf("\n");
    Crypto_VerifyResultType _verify;
    Std_ReturnType Mac_status = Csm_MacVerify(10,0,x,MAX,csm,MAC_Length*8,&_verify);

    if ((Mac_status == E_OK)) 
    {
        printf("result = E_OK\n");
    } 
    else 
    {
        printf("result = E_NOT_OK\n");
    }

    uint8 buff[16]={1,1,1,1,1,1,0,0};
    PduLengthType len = 8;
    PduInfoType SPDU;
    SPDU.SduDataPtr = buff;
    SPDU.SduLength = len;
    SecOC_VerificationResultType verify_;
    SecOC_RxPduProcessingType SecOC_RxPduProcessing;
    verify(20, &SPDU, SecOC_RxPduProcessing,&verify_);
}
