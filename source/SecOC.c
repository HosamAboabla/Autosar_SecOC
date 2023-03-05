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
#include "PduR_CanIf.h"
#include "SecOC_Debug.h"

#include <string.h>

static const SecOC_TxPduProcessingType     *SecOCTxPduProcessing;
static const SecOC_RxPduProcessingType     *SecOCRxPduProcessing;
static const SecOC_GeneralType             *SecOCGeneral;




static SecOC_StateType SecOCState = SECOC_UNINIT;

// Internal functions
static Std_ReturnType constructDataToAuthenticatorTx(const PduIdType TxPduId, uint8 *DataToAuth, uint32 *DataToAuthLen, const PduInfoType* AuthPdu);
static Std_ReturnType generateMAC(const PduIdType TxPduId, uint8 const *DataToAuth, const uint32 *DataToAuthLen, uint8  *authenticatorPtr, uint32  *authenticatorLen);
static Std_ReturnType authenticate(const PduIdType TxPduId, const PduInfoType* AuthPdu, PduInfoType* SecPdu);

static Std_ReturnType parseSecuredPdu(PduIdType RxPduId, PduInfoType* SecPdu, SecOC_RxIntermediateType *SecOCIntermediate);
static Std_ReturnType constructDataToAuthenticatorRx(PduIdType RxPduId, uint8 *DataToAuth, uint32 *DataToAuthLen, SecOC_RxIntermediateType *SecOCIntermediate);
static Std_ReturnType verify(PduIdType RxPduId, PduInfoType* SecPdu, SecOC_VerificationResultType *verification_result);


/****************************************************
 *          * Function Info *                           *
 *                                                      *
 * Function_Name        : constructDataToAuthenticatorTx*
 * Function_Index       : SecOC internal                *
 * Parameter in         : TxPduId                       *
 * Parameter in         : DataToAuth                    *
 * Parameter in/out     : DataToAuthLen                 *
 * Parameter in         : AuthPdu                       *
 * Function_Descripton  : This function constructs the  *
 * DataToAuthenticator using Data Identifier, secured   *
 * part of the * Authentic I-PDU, and freshness value   *
 *******************************************************/
static Std_ReturnType constructDataToAuthenticatorTx(const PduIdType TxPduId, uint8 *DataToAuth, uint32 *DataToAuthLen, const PduInfoType* AuthPdu)
{
    Std_ReturnType result;
    *DataToAuthLen = 0;

    // Data Identifier
    (void)memcpy(&DataToAuth[*DataToAuthLen], &TxPduId, sizeof(TxPduId));
    *DataToAuthLen += sizeof(TxPduId);

    // secured part of the Authentic I-PDU
    (void)memcpy(&DataToAuth[*DataToAuthLen], AuthPdu->SduDataPtr, AuthPdu->SduLength);
    *DataToAuthLen += AuthPdu->SduLength;
    
    // Complete Freshness Value
    uint8 FreshnessVal[SECOC_FRESHNESS_MAX_LENGTH/8] = {0};

    uint32 FreshnesslenBits = SecOCTxPduProcessing[TxPduId].SecOCFreshnessValueLength;

    result = SecOC_GetTxFreshness(SecOCTxPduProcessing[TxPduId].SecOCFreshnessValueId, FreshnessVal, &FreshnesslenBits);

    if(result != E_OK)
    {
        return result;
    }

    uint32 FreshnesslenBytes = BIT_TO_BYTES(FreshnesslenBits);

    (void)memcpy(&DataToAuth[*DataToAuthLen], FreshnessVal, FreshnesslenBytes);
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
    result = constructDataToAuthenticatorTx(TxPduId, DataToAuth, &DataToAuthLen, AuthPdu);

    // Authenticator generation
    uint8  authenticatorPtr[SECOC_AUTHENTICATOR_MAX_LENGTH];
    uint32  authenticatorLen = BIT_TO_BYTES(SecOCTxPduProcessing[TxPduId].SecOCAuthInfoTruncLength);
    result = generateMAC(TxPduId, DataToAuth, &DataToAuthLen, authenticatorPtr, &authenticatorLen);
    

    // Truncated freshness value
    uint8 FreshnessVal[SECOC_FRESHNESS_MAX_LENGTH/8] = {0};
    uint32 FreshnesslenBits = SecOCTxPduProcessing[TxPduId].SecOCFreshnessValueTruncLength;
    uint32 SecOCFreshnessValueLength = SecOCTxPduProcessing[TxPduId].SecOCFreshnessValueLength;

    result = SecOC_GetTxFreshnessTruncData(SecOCTxPduProcessing[TxPduId].SecOCFreshnessValueId, FreshnessVal, &SecOCFreshnessValueLength, FreshnessVal, &FreshnesslenBits);

    uint32 FreshnesslenBytes = BIT_TO_BYTES(SecOCTxPduProcessing[TxPduId].SecOCFreshnessValueTruncLength);

    // SECURED = HEADER(OPTIONAL) + AuthPdu + TruncatedFreshnessValue(OPTIONAL) + Authenticator
    PduLengthType SecPduLen = 0;

    // HEADER
    uint32 headerLen = SecOCTxPduProcessing[TxPduId].SecOCTxSecuredPduLayer->SecOCTxSecuredPdu->SecOCAuthPduHeaderLength;
    (void)memcpy(&SecPdu->SduDataPtr[SecPduLen], &AuthPdu->SduLength, headerLen);
    SecPduLen += headerLen;
    

    // AuthPdu
    (void)memcpy(&SecPdu->SduDataPtr[SecPduLen], AuthPdu->SduDataPtr, AuthPdu->SduLength);
    SecPduLen += AuthPdu->SduLength;

    // TruncatedFreshnessValue
    (void)memcpy(&SecPdu->SduDataPtr[SecPduLen], FreshnessVal, FreshnesslenBytes);
    SecPduLen += FreshnesslenBytes;

    // Authenticator
    (void)memcpy(&SecPdu->SduDataPtr[SecPduLen], authenticatorPtr, authenticatorLen);
    SecPduLen += authenticatorLen;


    SecPdu->SduLength = SecPduLen;
    SecPdu->MetaDataPtr = AuthPdu->MetaDataPtr;


    return result;
}


Std_ReturnType SecOC_IfTransmit(PduIdType TxPduId, const PduInfoType* PduInfoPtr) 
{
    Std_ReturnType result = E_OK;

    PduInfoType *authpdu = &(SecOCTxPduProcessing[TxPduId].SecOCTxAuthenticPduLayer->SecOCTxAuthenticLayerPduRef);
    
    (void)memcpy(authpdu->SduDataPtr, PduInfoPtr->SduDataPtr, PduInfoPtr->SduLength);
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
    // [SWS_SecOC_00054]
    SecOCGeneral = config->General;
    SecOCTxPduProcessing = config->SecOCTxPduProcessings;
    SecOCRxPduProcessing = config->SecOCRxPduProcessings;

    uint8 idx;
    for (idx = 0 ; idx < SECOC_NUM_OF_TX_PDU_PROCESSING ; idx++) 
    {      
        FVM_IncreaseCounter(SecOCTxPduProcessing[idx].SecOCFreshnessValueId);
    }

    SecOCState = SECOC_INIT;
    
}                   


void SecOC_DeInit(void)
{
    if(SecOCState != SECOC_INIT)
    {
        return;
    }

    SecOCState = SECOC_UNINIT;

    // [SWS_SecOC_00157]
    // Emptying Tx/Rx buffers
    PduIdType idx;
    for (idx = 0 ; idx < SECOC_NUM_OF_TX_PDU_PROCESSING; idx++) 
    {

        PduInfoType *authPdu = &(SecOCTxPduProcessing[idx].SecOCTxAuthenticPduLayer->SecOCTxAuthenticLayerPduRef);
        authPdu->SduLength = 0;
    }

    for (idx = 0 ; idx < SECOC_NUM_OF_RX_PDU_PROCESSING; idx++) 
    {

        PduInfoType *securedPdu = &(SecOCRxPduProcessing[idx].SecOCRxSecuredPduLayer->SecOCRxSecuredPdu->SecOCRxSecuredLayerPduRef);
        securedPdu->SduLength = 0;
    }

    SecOCGeneral = NULL;
    SecOCTxPduProcessing = NULL;
    SecOCRxPduProcessing = NULL;

}


void SecOCMainFunctionTx(void) 
{

    // [SWS_SecOC_00177]
    if(SecOCState == SECOC_UNINIT)
    {
        return;
    }
        
    PduIdType idx;
    for (idx = 0 ; idx < SECOC_NUM_OF_TX_PDU_PROCESSING ; idx++) 
    {

        PduInfoType *authPdu = &(SecOCTxPduProcessing[idx].SecOCTxAuthenticPduLayer->SecOCTxAuthenticLayerPduRef);
        PduInfoType *securedPdu = &(SecOCTxPduProcessing[idx].SecOCTxSecuredPduLayer->SecOCTxSecuredPdu->SecOCTxSecuredLayerPduRef);

        // check if there is data
        if (authPdu->SduLength > 0) 
        {
            authenticate(idx , authPdu , securedPdu);
            
            FVM_IncreaseCounter(SecOCTxPduProcessing[idx].SecOCFreshnessValueId);
            PduR_SecOCTransmit(idx , securedPdu);

        }
    }
}

void SecOCMainFunctionRx(void)
{
    // [SWS_SecOC_00172]
    if(SecOCState == SECOC_UNINIT)
    {
        return;
    }

    PduIdType idx = 0;
    SecOC_VerificationResultType result;
    SecOC_VerificationResultType macResult;

    
    for (idx = 0 ; idx < SECOC_NUM_OF_RX_PDU_PROCESSING; idx++) 
    {

        PduInfoType *authPdu = &(SecOCRxPduProcessing[idx].SecOCRxAuthenticPduLayer->SecOCRxAuthenticLayerPduRef);
        PduInfoType *securedPdu = &(SecOCRxPduProcessing[idx].SecOCRxSecuredPduLayer->SecOCRxSecuredPdu->SecOCRxSecuredLayerPduRef);

        // check if there is data
        if ( securedPdu->SduLength > 0 ) {
            
            result = verify(idx, securedPdu, &macResult);
            if( result == SECOC_VERIFICATIONSUCCESS )
            {
                #ifdef SECOC_DEBUG
                printf("Verify success for id: %d\n", idx);
                #endif
                PduR_SecOCIfRxIndication(idx,  authPdu);
            }

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

void SecOC_TpRxIndication(PduIdType Id,Std_ReturnType result)
{
    PduInfoType *securedPdu = &(SecOCRxPduProcessing[Id].SecOCRxSecuredPduLayer->SecOCRxSecuredPdu->SecOCRxSecuredLayerPduRef);

    if (result==E_NOT_OK)
    {
        // clear buffer
        securedPdu->SduLength = 0;
    }
}


Std_ReturnType SecOC_IfCancelTransmit(PduIdType TxPduId)
{
    Std_ReturnType result = E_OK;

    PduInfoType *authpdu = &(SecOCTxPduProcessing[TxPduId].SecOCTxAuthenticPduLayer->SecOCTxAuthenticLayerPduRef);
    
    authpdu->SduLength = 0;
    return result;
}



void SecOC_RxIndication(PduIdType RxPduId, const PduInfoType* PduInfoPtr)
{   
    /* The SecOC copies the Authentic I-PDU to its own buffer */
    PduInfoType *securedPdu = &(SecOCRxPduProcessing[RxPduId].SecOCRxSecuredPduLayer->SecOCRxSecuredPdu->SecOCRxSecuredLayerPduRef);

    (void)memcpy(securedPdu->SduDataPtr, PduInfoPtr->SduDataPtr, PduInfoPtr->SduLength);
    securedPdu->MetaDataPtr = PduInfoPtr->MetaDataPtr;
    securedPdu->SduLength = PduInfoPtr->SduLength;
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
    return FVM_GetRxFreshness(SecOCFreshnessValueID,SecOCTruncatedFreshnessValue,SecOCTruncatedFreshnessValueLength,
    SecOCAuthVerifyAttempts,SecOCFreshnessValue,SecOCFreshnessValueLength);
}

BufReq_ReturnType SecOC_CopyTxData (PduIdType id,const PduInfoType* info,
const RetryInfoType* retry, PduLengthType* availableDataPtr)
{
    BufReq_ReturnType result = BUFREQ_OK;
    PduInfoType *securedPdu = &(SecOCTxPduProcessing[id].SecOCTxSecuredPduLayer->SecOCTxSecuredPdu->SecOCTxSecuredLayerPduRef);
    static PduLengthType bufferRemainIndex[SECOC_NUM_OF_TX_PDU_PROCESSING] = {0};
    PduLengthType remainingBytes = securedPdu->SduLength - bufferRemainIndex[id];
    /* - Check if there is data in the buffer to be copy */
    if(securedPdu->SduLength > 0)
    {
        /*  If not enough transmit data is available, no data is copied by the upper layer module 
        and BUFREQ_E_BUSY is returned */
        if(info->SduLength <= remainingBytes)
        {
            if(info->SduLength == 0)
            {
                /* Querey amount of avalible data in upperlayer */
                *availableDataPtr = remainingBytes;
            }
            else
            {
                if(retry != NULL)
                {
                    switch (retry->TpDataState)
                    {
                        case TP_DATACONF:

                            /* indicates that all data that has been copied before this call is confirmed and 
                            can be removed from the TP buffer. Data copied by this API call is excluded and will be confirmed later */
                            (void)memcpy(info->SduDataPtr, securedPdu->SduDataPtr + bufferRemainIndex[id], info->SduLength);
                            bufferRemainIndex[id] += info->SduLength;
                            remainingBytes -= info->SduLength;
                            break;
                        case TP_CONFPENDING:
                            /* the previously copied data must remain in the TP buffer to be available for error recovery */
                            /* do nothing */
                            (void)memcpy(info->SduDataPtr, securedPdu->SduDataPtr + bufferRemainIndex[id] - info->SduLength, info->SduLength);
                            break;
                        case TP_DATARETRY:
                            /* indicates that this API call shall copy previously copied data in order to recover from an error. 
                            In this case TxTpDataCnt specifies the offset in bytes from the current data copy position */
                            (void)memcpy(info->SduDataPtr, securedPdu->SduDataPtr + bufferRemainIndex[id] - retry->TxTpDataCnt, info->SduLength);
                            break;
                        default:
                            result = BUFREQ_E_NOT_OK;
                        break;  
                    }
                }
                else
                {
                    /* Copy data then remove from the buffer */
                    (void)memcpy(info->SduDataPtr, securedPdu->SduDataPtr + bufferRemainIndex[id], info->SduLength);
                    bufferRemainIndex[id] += info->SduLength;
                    remainingBytes -= info->SduLength;
                }
                *availableDataPtr = remainingBytes;
            }
        }
        else
        {
            result = BUFREQ_E_BUSY;
        }
    }
    else
    {
        result = BUFREQ_E_NOT_OK;
    }

    return result;
}

static Std_ReturnType parseSecuredPdu(PduIdType RxPduId, PduInfoType* SecPdu, SecOC_RxIntermediateType *SecOCIntermediate)
{
    uint32 SecCursor = 0; // Track the current byte of secured to be parsed

    // Get data length from configuration or header if found
    uint32 headerLen = SecOCRxPduProcessing[RxPduId].SecOCRxSecuredPduLayer->SecOCRxSecuredPdu->SecOCAuthPduHeaderLength;
    SecOCIntermediate->authenticPduLen = 0;
    if(headerLen > 0)
    {
        // [SWS_SecOC_00259]
        (void)memcpy(&SecOCIntermediate->authenticPduLen, &SecPdu->SduDataPtr[SecCursor], headerLen);
        SecCursor += headerLen;
    }
    else
    {
        // [SWS_SecOC_00257]
        SecOCIntermediate->authenticPduLen =  SecOCRxPduProcessing[RxPduId].SecOCRxAuthenticPduLayer->SecOCRxAuthenticLayerPduRef.SduLength;
    }

    // Copy authenticPdu to intermediate
    (void)memcpy(SecOCIntermediate->authenticPdu, &SecPdu->SduDataPtr[SecCursor], SecOCIntermediate->authenticPduLen);
    SecCursor += SecOCIntermediate->authenticPduLen;

    uint16 authVeriAttempts = 0;
    // Get Rx freshness from FVM using the truncated freshness in SecPdu 
    const uint8* SecOCTruncatedFreshnessValue = &SecPdu->SduDataPtr[SecCursor];
    uint32 SecOCTruncatedFreshnessValueLength = SecOCRxPduProcessing[RxPduId].SecOCFreshnessValueTruncLength;
    SecOCIntermediate->freshnessLenBits = SecOCRxPduProcessing[RxPduId].SecOCFreshnessValueLength;
    // init freshness in struct SecOCIntermediate with 0
    memset(SecOCIntermediate->freshness, 0, sizeof(SecOCIntermediate->freshness));

    SecOCIntermediate->freshnessResult = SecOC_GetRxFreshness(
            SecOCRxPduProcessing[RxPduId].SecOCFreshnessValueId,
            SecOCTruncatedFreshnessValue, 
            SecOCTruncatedFreshnessValueLength, 
            authVeriAttempts,
            SecOCIntermediate->freshness, 
            &SecOCIntermediate->freshnessLenBits
    );

    SecCursor += BIT_TO_BYTES(SecOCTruncatedFreshnessValueLength);

    // Copy Mac to intermediate
    SecOCIntermediate->macLenBits = SecOCRxPduProcessing[RxPduId].SecOCAuthInfoTruncLength;

    (void)memcpy(SecOCIntermediate->mac, &SecPdu->SduDataPtr[SecCursor], BIT_TO_BYTES(SecOCIntermediate->macLenBits));
    SecCursor += BIT_TO_BYTES(SecOCIntermediate->macLenBits);

    return E_OK;
}

static Std_ReturnType constructDataToAuthenticatorRx(PduIdType RxPduId, uint8 *DataToAuth, uint32 *DataToAuthLen, SecOC_RxIntermediateType *SecOCIntermediate)
{
	//copy the Id to buffer Data to Auth
    (void)memcpy(&DataToAuth[*DataToAuthLen], &RxPduId, sizeof(RxPduId));
    *DataToAuthLen += sizeof(RxPduId);	


    // copy the authenticPdu to buffer DatatoAuth
    (void)memcpy(&DataToAuth[*DataToAuthLen], SecOCIntermediate->authenticPdu, SecOCIntermediate->authenticPduLen);
    *DataToAuthLen += SecOCIntermediate->authenticPduLen;

    // copy the freshness value to buffer Data to Auth
    (void)memcpy(&DataToAuth[*DataToAuthLen], SecOCIntermediate->freshness, BIT_TO_BYTES(SecOCRxPduProcessing[RxPduId].SecOCFreshnessValueLength));
    *DataToAuthLen += (BIT_TO_BYTES(SecOCRxPduProcessing[RxPduId].SecOCFreshnessValueLength));

    return E_OK;
}

// header - auth_data - Freshness - MAC
static Std_ReturnType verify(PduIdType RxPduId, PduInfoType* SecPdu, SecOC_VerificationResultType *verification_result)
{

    SecOC_RxIntermediateType    SecOCIntermediate;
    parseSecuredPdu(RxPduId, SecPdu, &SecOCIntermediate);

    SecOC_VerificationResultType result;
    if(SecOCIntermediate.freshnessResult != E_OK)
    {
        // drop message
        SecPdu->SduLength = 0;
        result = SECOC_FRESHNESSFAILURE;
        return result;
    }

    uint8 DataToAuth[SECOC_RX_DATA_TO_AUTHENTICATOR_LENGTH] = {0};  // CAN payload
    uint32 DataToAuthLen = 0;

    constructDataToAuthenticatorRx(RxPduId, DataToAuth, &DataToAuthLen, &SecOCIntermediate);

    Crypto_VerifyResultType verify_var;
    Std_ReturnType Mac_verify = Csm_MacVerify(SecOCRxPduProcessing[RxPduId].SecOCDataId, Crypto_stub, DataToAuth, DataToAuthLen, SecOCIntermediate.mac, SecOCIntermediate.macLenBits, &verify_var);

    if (Mac_verify == E_OK) 
    {
        *verification_result = CRYPTO_E_VER_OK;
        result = SECOC_VERIFICATIONSUCCESS;

        PduInfoType *authPdu = &(SecOCRxPduProcessing[RxPduId].SecOCRxAuthenticPduLayer->SecOCRxAuthenticLayerPduRef);

        // Copy authenticPdu from secured layer to the authentic layer
        (void)memcpy(authPdu->SduDataPtr, SecOCIntermediate.authenticPdu, SecOCIntermediate.authenticPduLen);
        authPdu->SduLength = SecOCIntermediate.authenticPduLen;
        authPdu->MetaDataPtr = SecPdu->MetaDataPtr;

        FVM_UpdateCounter(SecOCRxPduProcessing[RxPduId].SecOCFreshnessValueId, SecOCIntermediate.freshness, SecOCIntermediate.freshnessLenBits);
    }
    else 
    {
        // drop message
        *verification_result = CRYPTO_E_VER_NOT_OK;
        result = SECOC_VERIFICATIONFAILURE;

        SecPdu->SduLength = 0;
    }


    return result;
}


BufReq_ReturnType SecOC_CopyRxData (PduIdType id, const PduInfoType* info, PduLengthType* bufferSizePtr)
{
    BufReq_ReturnType result = BUFREQ_OK;

    /*Create a pointer to the secured I-PDU buffer that we will store the data into it*/
    /*[SWS_SecOC_00082]*/
    PduInfoType *securedPdu = &(SecOCRxPduProcessing[id].SecOCRxSecuredPduLayer->SecOCRxSecuredPdu->SecOCRxSecuredLayerPduRef);


    if(info->SduLength == 0)
    {
        /* An SduLength of 0 can be used to query the
        * current amount of available buffer in the upper layer module. In this
        * case, the SduDataPtr may be a NULL_PTR.
        */
        *bufferSizePtr = SECOC_SECPDU_MAX_LENGTH - securedPdu->SduLength;
    }
    else if((info->SduLength > 0) && (info->SduDataPtr != NULL))
    {
        /*[SWS_SecOC_00083]*/
        (void)memcpy(securedPdu->SduDataPtr + securedPdu->SduLength, info->SduDataPtr, info->SduLength);
        securedPdu->SduLength += info->SduLength;

        *bufferSizePtr = SECOC_SECPDU_MAX_LENGTH - securedPdu->SduLength;
    }
    else
    {
        result = BUFREQ_E_NOT_OK;
    }


    return result;
}

#ifdef SECOC_DEBUG
extern SecOC_ConfigType SecOC_Config;  
void SecOC_test()
{
    
}
#endif