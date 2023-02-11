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

const SecOC_TxPduProcessingType     *SecOCTxPduProcessing;
const SecOC_RxPduProcessingType     *SecOCRxPduProcessing;
const SecOC_GeneralType             *SecOCGeneral;





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
    
    uint32 FreshnesslenBits = SecOCTxPduProcessing[TxPduId].SecOCFreshnessValueLength;

    result = SecOC_GetTxFreshness(TxPduId, FreshnessVal, &FreshnesslenBits);
    if(result != E_OK)
    {
        return result;
    }

    uint32 FreshnesslenBytes = BIT_TO_BYTES(FreshnesslenBits);

    memcpy(&DataToAuth[*DataToAuthLen], &FreshnessVal[SecOCTxPduProcessing[TxPduId].SecOCFreshnessValueLength - FreshnesslenBytes], FreshnesslenBytes);
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
    uint32  authenticatorLen = BIT_TO_BYTES(SecOCTxPduProcessing[TxPduId].SecOCAuthInfoTruncLength);
    result = generateMAC(TxPduId, DataToAuth, &DataToAuthLen, authenticatorPtr, &authenticatorLen);

    // Create secured IPDU
    SecPdu->MetaDataPtr = AuthPdu->MetaDataPtr;
    SecPdu->SduLength = SECOC_SECPDU_MAX_LENGTH;

    // Truncated freshness value
    uint8 FreshnessVal[SECOC_TX_FRESHNESS_VALUE_TRUNC_LENGTH] = {0};
    uint32 FreshnesslenBits = SecOCTxPduProcessing[TxPduId].SecOCFreshnessValueTruncLength;
    result = SecOC_GetTxFreshness(TxPduId, FreshnessVal, &FreshnesslenBits);

    uint32 FreshnesslenBytes = BIT_TO_BYTES(SecOCTxPduProcessing[TxPduId].SecOCFreshnessValueTruncLength);

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


Std_ReturnType SecOC_IfTransmit(PduIdType TxPduId, const PduInfoType* PduInfoPtr) 
{
    Std_ReturnType result = E_OK;

    PduInfoType *authpdu = &(SecOCTxPduProcessing[TxPduId].SecOCTxAuthenticPduLayer->SecOCTxAuthenticLayerPduRef);
    
    memcpy(authpdu->SduDataPtr, PduInfoPtr->SduDataPtr, PduInfoPtr->SduLength);
    authpdu->MetaDataPtr = PduInfoPtr->MetaDataPtr;
    authpdu->SduLength = PduInfoPtr->SduLength;


    return result;
}


void SecOC_TxConfirmation(PduIdType TxPduId, Std_ReturnType result) 
{
    PduInfoType *authPdu = &(SecOCTxPduProcessing[TxPduId].SecOCTxAuthenticPduLayer->SecOCTxAuthenticLayerPduRef);
    PduInfoType *securedPdu = &(SecOCTxPduProcessing[TxPduId].SecOCTxSecuredPduLayer->SecOCTxSecuredPdu->SecOCTxSecuredLayerPduRef);

    if (result == E_OK) {
        // clear buffer
        authPdu->SduLength = 0;
        securedPdu->SduLength = 0;
    }

    PduR_SecOCIfTxConfirmation(TxPduId, result);
}



Std_ReturnType SecOC_GetTxFreshness(uint16 SecOCFreshnessValueID, uint8* SecOCFreshnessValue,
uint32* SecOCFreshnessValueLength) {
    SecOC_GetTxFreshnessCalloutType PTR = (SecOC_GetTxFreshnessCalloutType)FVM_GetTxFreshness;
Std_ReturnType result = PTR(SecOCFreshnessValueID, SecOCFreshnessValue, SecOCFreshnessValueLength);
    return result;
}







void SecOC_Init(const SecOC_ConfigType *config)
{
    SecOCGeneral = config->General;
    SecOCTxPduProcessing = config->SecOCTxPduProcessings;
    SecOCRxPduProcessing = config->SecOCRxPduProcessings;
    
}                   




void SecOC_MainFunctionTx(void) {

    PduInfoType *secured = &(SecOCRxPduProcessing[0].SecOCRxSecuredPduLayer->SecOCRxSecuredPdu->SecOCRxSecuredLayerPduRef);
    PduInfoType *auth = &(SecOCRxPduProcessing[0].SecOCRxAuthenticPduLayer->SecOCRxAuthenticLayerPduRef);
    PduIdType idx;
    for (idx = 0 ; idx < 1 ; idx++) 
    {

        PduInfoType *authPdu = &(SecOCTxPduProcessing[idx].SecOCTxAuthenticPduLayer->SecOCTxAuthenticLayerPduRef);
        PduInfoType *securedPdu = &(SecOCTxPduProcessing[idx].SecOCTxSecuredPduLayer->SecOCTxSecuredPdu->SecOCTxSecuredLayerPduRef);

        // check if there is data
        if (authPdu->SduLength > 0) 
        {
            authenticate(idx , authPdu , securedPdu);
            PduR_SecOCTransmit(idx , securedPdu);

        }
    }
}

void SecOC_TpTxConfirmation(PduIdType TxPduId,Std_ReturnType result)
{
    PduInfoType *authPdu = &(SecOCTxPduProcessing[TxPduId].SecOCTxAuthenticPduLayer->SecOCTxAuthenticLayerPduRef);
    PduInfoType *securedPdu = &(SecOCTxPduProcessing[TxPduId].SecOCTxSecuredPduLayer->SecOCTxSecuredPdu->SecOCTxSecuredLayerPduRef);

    if (result == E_OK) {
        // clear buffer
        authPdu->SduLength = 0;
        securedPdu->SduLength = 0;
    }

    if (SecOCTxPduProcessing[TxPduId].SecOCTxAuthenticPduLayer->SecOCPduType == SECOC_TPPDU)
    {
        PduR_SecOCTpTxConfirmation(TxPduId, result);
    }
    else if (SecOCTxPduProcessing[TxPduId].SecOCTxAuthenticPduLayer->SecOCPduType == SECOC_IFPDU)
    {
        PduR_SecOCIfTxConfirmation(TxPduId, result);
    }
    else
    {
        // DET Report Error
    }

}





void SecOC_RxIndication (PduIdType RxPduId, const PduInfoType* PduInfoPtr)
{   /* The SecOC copies the Authentic I-PDU to its own buffer */
   // if (RxPduId < SECOC_BUFFERLENGTH) SecOC_Buffer_Rx[RxPduId] = *PduInfoPtr;
}


#include <stdio.h>


extern SecOC_ConfigType SecOC_Config;
void SecOC_test()
{
     //FVM_IncreaseCounter(0, 100);
   // uint8_t adata[100] = "hello, world";
    uint8_t adata[100] = {0, 1, 2, 3, 9, 5, 6, 7, 8, 9, 10, 11, 12};
    uint8_t sdata[100];
    PduInfoType AuthPdu, SecPdu;
    AuthPdu.SduDataPtr = adata;
    AuthPdu.SduLength = SECOC_AUTHPDU_MAX_LENGTH;

    
    SecOC_Init(&SecOC_Config);
    SecOC_IfTransmit(0, &AuthPdu);
    // Changing parameters: Authentic I-PDU(constant for now), Freshness Value, Authenticator
    //SecOC_TxPduProcessing[0].SecOCFreshnessValueTruncLength = 16;
    //SecOC_TxPduProcessing[0].SecOCAuthInfoTruncLength = 32; // BITS

    for(int i = 0; i < AuthPdu.SduLength; i++)
        printf("%d ", AuthPdu.SduDataPtr[i]);
    printf("\n");

    // main function
    
     PduInfoType *secured = &(SecOCTxPduProcessing[0].SecOCTxSecuredPduLayer->SecOCTxSecuredPdu->SecOCTxSecuredLayerPduRef);
     PduInfoType *auth = &(SecOCTxPduProcessing[0].SecOCTxAuthenticPduLayer->SecOCTxAuthenticLayerPduRef);
    // authenticate(0, auth, secured);
    SecOC_MainFunctionTx();

    for(int i = 0; i < secured->SduLength; i++)
        printf("%d ", secured->SduDataPtr[i]);
    printf("\n");
    printf("done");   
}