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
#include "CanTP.h"
#include "SecOC_Debug.h"

#include <string.h>

const SecOC_TxPduProcessingType     *SecOCTxPduProcessing;
const SecOC_RxPduProcessingType     *SecOCRxPduProcessing;
const SecOC_GeneralType             *SecOCGeneral;

extern SecOC_TxCountersType         SecOC_TxCounters[SECOC_NUM_OF_TX_PDU_PROCESSING];
extern SecOC_RxCountersType         SecOC_RxCounters[SECOC_NUM_OF_RX_PDU_PROCESSING];


static SecOC_StateType SecOCState = SECOC_UNINIT;
static PduLengthType bufferRemainIndex[SECOC_NUM_OF_TX_PDU_PROCESSING] = {0};

/* Internal functions */
static Std_ReturnType constructDataToAuthenticatorTx(const PduIdType TxPduId, uint8 *DataToAuth, uint32 *DataToAuthLen, const PduInfoType* AuthPdu);
static Std_ReturnType generateMAC(const PduIdType TxPduId, uint8 const *DataToAuth, const uint32 *DataToAuthLen, uint8  *authenticatorPtr, uint32  *authenticatorLen);
static Std_ReturnType authenticate(const PduIdType TxPduId, PduInfoType* AuthPdu, PduInfoType* SecPdu);

static Std_ReturnType parseSecuredPdu(PduIdType RxPduId, PduInfoType* SecPdu, SecOC_RxIntermediateType *SecOCIntermediate);
static Std_ReturnType constructDataToAuthenticatorRx(PduIdType RxPduId, uint8 *DataToAuth, uint32 *DataToAuthLen, SecOC_RxIntermediateType *SecOCIntermediate);
static Std_ReturnType verify(PduIdType RxPduId, PduInfoType* SecPdu, SecOC_VerificationResultType *verification_result);


/********************************************************
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
    #ifdef SECOC_DEBUG
        printf("######## in constructDataToAuthenticatorTx\n");
    #endif
    Std_ReturnType result;
    *DataToAuthLen = 0;

    /* Data Identifier */
    (void)memcpy(&DataToAuth[*DataToAuthLen], &TxPduId, sizeof(TxPduId));
    *DataToAuthLen += sizeof(TxPduId);

    /* secured part of the Authentic I-PDU */
    (void)memcpy(&DataToAuth[*DataToAuthLen], AuthPdu->SduDataPtr, AuthPdu->SduLength);
    *DataToAuthLen += AuthPdu->SduLength;
    
    /* Complete Freshness Value */
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
    #ifdef SECOC_DEBUG
        printf("######## in generateMAC \n");
    #endif
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
static Std_ReturnType authenticate(const PduIdType TxPduId,  PduInfoType* AuthPdu, PduInfoType* SecPdu)
{
    /* [SWS_SecOC_00031] authentication steps */
    #ifdef SECOC_DEBUG
        printf("######## in authenticate \n");
    #endif
    Std_ReturnType result = E_NOT_OK;
    Std_ReturnType result_Fv;
    
    /* DataToAuthenticator = Data Identifier | secured part of the Authentic I-PDU | Complete Freshness Value */
    uint8 DataToAuth[SECOC_TX_DATA_TO_AUTHENTICATOR_LENGTH];
    uint32 DataToAuthLen = 0;

    /* [SWS_SecOC_00034] */
    result = constructDataToAuthenticatorTx(TxPduId, DataToAuth, &DataToAuthLen, AuthPdu);
    /* Authenticator generation */
    uint8  authenticatorPtr[SECOC_AUTHENTICATOR_MAX_LENGTH];
    uint32  authenticatorLen = BIT_TO_BYTES(SecOCTxPduProcessing[TxPduId].SecOCAuthInfoTruncLength);

    /* [SWS_SecOC_00035], [SWS_SecOC_00036]*/
    result = generateMAC(TxPduId, DataToAuth, &DataToAuthLen, authenticatorPtr, &authenticatorLen);
    result = E_NOT_OK;

    /* Truncated freshness value */
    uint8 FreshnessVal[SECOC_FRESHNESS_MAX_LENGTH/8] = {0};
    uint32 FreshnesslenBits = SecOCTxPduProcessing[TxPduId].SecOCFreshnessValueTruncLength;
    uint32 SecOCFreshnessValueLength = SecOCTxPduProcessing[TxPduId].SecOCFreshnessValueLength;

    /* [SWS_SecOC_00094] */
    result_Fv = SecOC_GetTxFreshnessTruncData(SecOCTxPduProcessing[TxPduId].SecOCFreshnessValueId, FreshnessVal, &SecOCFreshnessValueLength, FreshnessVal, &FreshnesslenBits);

    uint32 FreshnesslenBytes = BIT_TO_BYTES(SecOCTxPduProcessing[TxPduId].SecOCFreshnessValueTruncLength);

    /* [SWS_SecOC_00037] SECURED = HEADER(OPTIONAL) + AuthPdu + TruncatedFreshnessValue(OPTIONAL) + Authenticator */
    PduLengthType SecPduLen = 0;

    boolean authenticationFailure = FALSE; 
 
    if(result_Fv == E_OK)
    {
        if( result == E_OK )
        {

            /* [SWS_SecOC_00262] Header */
            uint32 headerLen = SecOCTxPduProcessing[TxPduId].SecOCTxSecuredPduLayer->SecOCTxSecuredPdu->SecOCAuthPduHeaderLength;
            if(headerLen > 0)
            {
                /* [SWS_SecOC_00261] The Secured I-PDU Header shall indicate the length of the Authentic I-PDU in bytes */
                (void)memcpy(&SecPdu->SduDataPtr[SecPduLen], &AuthPdu->SduLength, headerLen);
                SecPduLen += headerLen;        
            }
            /* AuthPdu */
            (void)memcpy(&SecPdu->SduDataPtr[SecPduLen], AuthPdu->SduDataPtr, AuthPdu->SduLength);
            SecPduLen += AuthPdu->SduLength;

            /* [SWS_SecOC_00094] TruncatedFreshnessValue */
            (void)memcpy(&SecPdu->SduDataPtr[SecPduLen], FreshnessVal, FreshnesslenBytes);
            SecPduLen += FreshnesslenBytes;

            /* Authenticator */
            (void)memcpy(&SecPdu->SduDataPtr[SecPduLen], authenticatorPtr, authenticatorLen);
            SecPduLen += authenticatorLen;

            SecPdu->SduLength = SecPduLen;

            /* [SWS_SecOC_00212] */
            SecPdu->MetaDataPtr = AuthPdu->MetaDataPtr;

            /* clear Auth */
            AuthPdu->SduLength = 0;
        }

        else if( (result == E_BUSY) || (result == QUEUE_FULL) )
        {
            /* [SWS_SecOC_00227] */
            SecOC_TxCounters[TxPduId].AuthenticationCounter++;
            #ifdef COUNTERS_DEBUG
            printf("SecOC_TxCounters[%d].AuthenticationCounter = %d\n",TxPduId,SecOC_TxCounters[TxPduId].AuthenticationCounter);
            printf("SecOCTxPduProcessing[%d].SecOCAuthenticationBuildAttempts = %d\n",TxPduId,SecOCTxPduProcessing[TxPduId].SecOCAuthenticationBuildAttempts);
            #endif
            if( SecOC_TxCounters[TxPduId].AuthenticationCounter == SecOCTxPduProcessing[TxPduId].SecOCAuthenticationBuildAttempts )
            {
                authenticationFailure = TRUE;
            }
            else
            {
                /* [SWS_SecOC_00228] */
            }
        }

        else
        {
            authenticationFailure = TRUE;
        }
    }

    else if( result_Fv == E_BUSY )
    {
        /* [SWS_SecOC_00227] */
        SecOC_TxCounters[TxPduId].AuthenticationCounter++;
        #ifdef COUNTERS_DEBUG
        printf("SecOC_TxCounters[%d].AuthenticationCounter = %d\n",TxPduId,SecOC_TxCounters[TxPduId].AuthenticationCounter);
        printf("SecOCTxPduProcessing[%d].SecOCAuthenticationBuildAttempts = %d\n",TxPduId,SecOCTxPduProcessing[TxPduId].SecOCAuthenticationBuildAttempts);
        #endif
        if( SecOC_TxCounters[TxPduId].AuthenticationCounter == SecOCTxPduProcessing[TxPduId].SecOCAuthenticationBuildAttempts )
        {
            authenticationFailure = TRUE;
        }
        else
        {
            /* [SWS_SecOC_00228] */
        }
    }

    else /* E_NOT_OK */
    {
        authenticationFailure = TRUE;
    }

    if( authenticationFailure == TRUE )
    {
        /* [SWS_SecOC_00229] */
        if( SecOCGeneral->SecOCDefaultAuthenticationInformationPattern > 0 )
        {
            /* SecOC_SendDefaultAuthenticationInformation(SecOCTxPduProcessing[TxPduId].SecOCFreshnessValueId, TRUE) */
        }
        AuthPdu->SduLength = 0;
    }

    #ifdef SECOC_DEBUG
        printf("result of authenticate is %d\n", result);
    #endif
    return result;
}


Std_ReturnType SecOC_IfTransmit(PduIdType TxPduId, const PduInfoType* PduInfoPtr) 
{
    #ifdef SECOC_DEBUG
        printf("######## in SecOC_IfTransmit \n");
    #endif
    Std_ReturnType result = E_OK;

    PduInfoType *authpdu = &(SecOCTxPduProcessing[TxPduId].SecOCTxAuthenticPduLayer->SecOCTxAuthenticLayerPduRef);
    
    /* [SWS_SecOC_00252] The SecOC module shall copy the complete Authentic I-PDU to its internal memory before transmission */
    /* [SWS_SecOC_00110] Transmissions the upper layer shall overwrite the Authentic I-PDU without affecting the respective Secured I-PDU.*/
    (void)memcpy(authpdu->SduDataPtr, PduInfoPtr->SduDataPtr, PduInfoPtr->SduLength);
    authpdu->MetaDataPtr = PduInfoPtr->MetaDataPtr;
    authpdu->SduLength = PduInfoPtr->SduLength;

    #ifdef SECOC_DEBUG
        printf("###### Getting The Auth PDU \n");
        for(int i = 0; i < authpdu->SduLength; i++)
            printf("%d ", authpdu->SduDataPtr[i]);
        printf("\n");
    #endif

    return result;
}


void SecOC_TxConfirmation(PduIdType TxPduId, Std_ReturnType result) 
{
    #ifdef SECOC_DEBUG
        printf("######## in SecOC_TxConfirmation \n");
    #endif
    PduInfoType *securedPdu = &(SecOCTxPduProcessing[TxPduId].SecOCTxSecuredPduLayer->SecOCTxSecuredPdu->SecOCTxSecuredLayerPduRef);

    /* [SWS_SecOC_00064] */
    if (result == E_OK) 
    {
        securedPdu->SduLength = 0;
    }
    /* [SWS_SecOC_00063] */
    PduR_SecOCIfTxConfirmation(TxPduId, result);
}



Std_ReturnType SecOC_GetTxFreshness(uint16 SecOCFreshnessValueID, uint8* SecOCFreshnessValue,
uint32* SecOCFreshnessValueLength) {
    #ifdef SECOC_DEBUG
        printf("######## in SecOC_GetTxFreshness\n");
    #endif
    SecOC_GetTxFreshnessCalloutType PTR = (SecOC_GetTxFreshnessCalloutType)FVM_GetTxFreshness;
Std_ReturnType result = PTR(SecOCFreshnessValueID, SecOCFreshnessValue, SecOCFreshnessValueLength);
    return result;
}







void SecOC_Init(const SecOC_ConfigType *config)
{
    #ifdef SECOC_DEBUG
        printf("######## in SecOC_Init \n");
    #endif
    /* [SWS_SecOC_00054] */
    SecOCGeneral = config->General;
    SecOCTxPduProcessing = config->SecOCTxPduProcessings;
    SecOCRxPduProcessing = config->SecOCRxPduProcessings;

    /* Increase all freshness counters to make it fresh */
    uint8 idx;
    for (idx = 0 ; idx < SECOC_NUM_OF_TX_PDU_PROCESSING ; idx++) 
    {      
        FVM_IncreaseCounter(SecOCTxPduProcessing[idx].SecOCFreshnessValueId);
    }

    SecOCState = SECOC_INIT;
    
}                   


void SecOC_DeInit(void)
{
    #ifdef SECOC_DEBUG
        printf("######## in SecOC_DeInit \n");
    #endif
    if(SecOCState != SECOC_INIT)
    {
        return;
    }

    SecOCState = SECOC_UNINIT;

    /* [SWS_SecOC_00157] */
    /* Emptying Tx/Rx buffers */
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
    #ifdef SECOC_DEBUG
        printf("######## in SecOCMainFunctionTx \n");
    #endif
    /* [SWS_SecOC_00177] */
    if(SecOCState == SECOC_UNINIT)
    {
        return;
    }
        
    PduIdType idx;
    for (idx = 0 ; idx < SECOC_NUM_OF_TX_PDU_PROCESSING ; idx++) 
    {

        PduInfoType *authPdu = &(SecOCTxPduProcessing[idx].SecOCTxAuthenticPduLayer->SecOCTxAuthenticLayerPduRef);
        PduInfoType *securedPdu = &(SecOCTxPduProcessing[idx].SecOCTxSecuredPduLayer->SecOCTxSecuredPdu->SecOCTxSecuredLayerPduRef);

        /* Check if there is data */
        if (authPdu->SduLength > 0) 
        {
            /* [SWS_SecOC_00060], [SWS_SecOC_00061] */
            authenticate(idx , authPdu , securedPdu);
            
            FVM_IncreaseCounter(SecOCTxPduProcessing[idx].SecOCFreshnessValueId);

            /* [SWS_SecOC_00062] */
            PduR_SecOCTransmit(idx , securedPdu);
            

        }
    }
}

void SecOCMainFunctionRx(void)
{
    #ifdef SECOC_DEBUG
        printf("######## in SecOCMainFunctionRx \n");
    #endif
    /* [SWS_SecOC_00172] */
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

        /* Check if there is data */
        if ( securedPdu->SduLength > 0 ) {
            
            /* [SWS_SecOC_00079] */
            result = verify(idx, securedPdu, &macResult);
            if( result == SECOC_VERIFICATIONSUCCESS )
            {
                #ifdef SECOC_DEBUG
                (void)printf("Verify success for id: %d\n", idx);
                #endif

                /* [SWS_SecOC_00050], [SWS_SecOC_00080] */
                PduR_SecOCIfRxIndication(idx,  authPdu);
            }
            else if( result == SECOC_VERIFICATIONFAILURE )
            {
                #ifdef SECOC_DEBUG
                printf("MAC failed for id: %d\n", idx);
                #endif
            }
            else
            {
                #ifdef SECOC_DEBUG
                printf("FV failed for id: %d\n", idx);
                #endif
            }

        }
    }

}

void SecOC_TpTxConfirmation(PduIdType TxPduId,Std_ReturnType result)
{
    PduInfoType *securedPdu = &(SecOCTxPduProcessing[TxPduId].SecOCTxSecuredPduLayer->SecOCTxSecuredPdu->SecOCTxSecuredLayerPduRef);
    #ifdef SECOC_DEBUG
        printf("########  In SecOC_TpTxConfirmation \n result of SecOC_TpTxConfirmation is %d \n" , result);
    #endif
    if (result == E_OK) {
        /* Clear buffer */
        securedPdu->SduLength = 0;
        bufferRemainIndex[TxPduId] = 0;
    }

    /* [SWS_SecOC_00074] */
    if (SecOCTxPduProcessing[TxPduId].SecOCTxAuthenticPduLayer->SecOCPduType == SECOC_TPPDU)
    {
        /* [SWS_SecOC_00063] */
        PduR_SecOCTpTxConfirmation(TxPduId, result);
    }
    else if (SecOCTxPduProcessing[TxPduId].SecOCTxAuthenticPduLayer->SecOCPduType == SECOC_IFPDU)
    {
        /* [SWS_SecOC_00063] */
        PduR_SecOCIfTxConfirmation(TxPduId, result);
    }
    else
    {
        /* DET Report Error */
    }

}

void SecOC_TpRxIndication(PduIdType Id,Std_ReturnType result)
{
    #ifdef SECOC_DEBUG
        printf("######## in SecOC_TpRxIndication \n");
    #endif
    PduInfoType *securedPdu = &(SecOCRxPduProcessing[Id].SecOCRxSecuredPduLayer->SecOCRxSecuredPdu->SecOCRxSecuredLayerPduRef);

    if (result==E_NOT_OK)
    {
        /* Clear buffer */
        securedPdu->SduLength = 0;
    }
}



BufReq_ReturnType SecOC_StartOfReception ( PduIdType id, const PduInfoType* info, PduLengthType TpSduLength, PduLengthType* bufferSizePtr )
{
    #ifdef SECOC_DEBUG
        printf("######## in SecOC_StartOfReception \n");
    #endif
	uint8 AuthHeadlen;
	AuthHeadlen=SecOCRxPduProcessing[id].SecOCRxSecuredPduLayer->SecOCRxSecuredPdu->SecOCAuthPduHeaderLength;
    // [SWS_SecOC_00082]
    PduInfoType *securedPdu = &(SecOCRxPduProcessing[id].SecOCRxSecuredPduLayer->SecOCRxSecuredPdu->SecOCRxSecuredLayerPduRef);
    *bufferSizePtr = SECOC_SECPDU_MAX_LENGTH - securedPdu->SduLength;
    BufReq_ReturnType r=BUFREQ_OK;
    uint32 datalen=0;
    // [SWS_SecOC_00130] /*description*/
    if(TpSduLength>*bufferSizePtr)
    {
        r=BUFREQ_E_OVFL;
        //[SWS_SecOC_00215]
        if(SecOCRxPduProcessing[id].SecOCReceptionOverflowStrategy==SECOC_REJECT)
        {
            r=BUFREQ_E_NOT_OK;
        }
    }
    else if (TpSduLength == 0)
    {
        // [SWS_SecOC_00181] 
        r=BUFREQ_E_NOT_OK;
    }
    else
    {
        //receiving first Byte if not Null
        if((info->SduDataPtr != NULL))
        {
            //[SWS_SecOC_00263] /*check if dynamic*/            
            if(AuthHeadlen>0)
            {
                switch (AuthHeadlen)
                {
                case 1:
                    datalen=info->SduDataPtr[0];
                    if((uint8)datalen > SECOC_AUTHPDU_MAX_LENGTH)
                    {
                        r=BUFREQ_E_NOT_OK;
                    }
                    break;

                case 2:
                    datalen=((info->SduDataPtr[1])<<8)|(info->SduDataPtr[0]);
                    if((uint16)datalen> SECOC_AUTHPDU_MAX_LENGTH)
                    {
                        r=BUFREQ_E_NOT_OK;
                    }
                    break;

                case 3:
                    datalen=((info->SduDataPtr[2])<<16)|((info->SduDataPtr[1])<<8)|(info->SduDataPtr[0]);
                    if((uint32)datalen> SECOC_AUTHPDU_MAX_LENGTH)
                    {
                        r=BUFREQ_E_NOT_OK;
                    }
                    break;

                case 4:
                    datalen=((info->SduDataPtr[3])<<24)|((info->SduDataPtr[2])<<16)|((info->SduDataPtr[1])<<8)|(info->SduDataPtr[0]);
                    if((uint32)datalen> SECOC_AUTHPDU_MAX_LENGTH)
                    {
                        r=BUFREQ_E_NOT_OK;
                    }
                    break;

                default:
                    break;
                }
            }
        }
    }
        
    if(SecOCRxPduProcessing[id].SecOCRxAuthenticPduLayer->SecOCPduType==SECOC_TPPDU)
    {
		//r=PduR_SecOCTpStartOfReception();
	}
    #ifdef SECOC_DEBUG
        printf("result of SecOC_StartOfReception is %d\n", r);
    #endif
	return r;
}

Std_ReturnType SecOC_IfCancelTransmit(PduIdType TxPduId)
{
    #ifdef SECOC_DEBUG
        printf("######## in SecOC_IfCancelTransmit \n");
    #endif
    Std_ReturnType result = E_OK;

    PduInfoType *authpdu = &(SecOCTxPduProcessing[TxPduId].SecOCTxAuthenticPduLayer->SecOCTxAuthenticLayerPduRef);
    
    authpdu->SduLength = 0;
    return result;
}



void SecOC_RxIndication(PduIdType RxPduId, const PduInfoType* PduInfoPtr)
{   
    #ifdef SECOC_DEBUG
        printf("######## in SecOC_RxIndication \n");
    #endif
    /* The SecOC copies the Authentic I-PDU to its own buffer */
    PduInfoType *securedPdu = &(SecOCRxPduProcessing[RxPduId].SecOCRxSecuredPduLayer->SecOCRxSecuredPdu->SecOCRxSecuredLayerPduRef);
    uint32 headerLen = SecOCRxPduProcessing[RxPduId].SecOCRxSecuredPduLayer->SecOCRxSecuredPdu->SecOCAuthPduHeaderLength;

    /* [SWS_SecOC_00268] static Pdu*/
    if(headerLen == 0 && (PduInfoPtr->SduLength < securedPdu->SduLength))
    {
        return;
    }

    (void)memcpy(securedPdu->SduDataPtr, PduInfoPtr->SduDataPtr, PduInfoPtr->SduLength);
    securedPdu->MetaDataPtr = PduInfoPtr->MetaDataPtr;

    /* [SWS_SecOC_00078] */
    securedPdu->SduLength = MIN(PduInfoPtr->SduLength, SECOC_SECPDU_MAX_LENGTH);
}





Std_ReturnType SecOC_GetTxFreshnessTruncData (uint16 SecOCFreshnessValueID,uint8* SecOCFreshnessValue,
uint32* SecOCFreshnessValueLength,uint8* SecOCTruncatedFreshnessValue,uint32* SecOCTruncatedFreshnessValueLength) 
{
    #ifdef SECOC_DEBUG
        printf("######## in SecOC_GetTxFreshnessTruncData\n");
    #endif
    Std_ReturnType result = FVM_GetTxFreshnessTruncData(SecOCFreshnessValueID, SecOCFreshnessValue , SecOCFreshnessValueLength,
    SecOCTruncatedFreshnessValue, SecOCTruncatedFreshnessValueLength);
    return result;
}


Std_ReturnType SecOC_GetRxFreshness(uint16 SecOCFreshnessValueID,const uint8* SecOCTruncatedFreshnessValue,uint32 SecOCTruncatedFreshnessValueLength,
    uint16 SecOCAuthVerifyAttempts,uint8* SecOCFreshnessValue,uint32* SecOCFreshnessValueLength)
{
    #ifdef SECOC_DEBUG
        printf("######## in SecOC_GetRxFreshness \n");
    #endif
    return FVM_GetRxFreshness(SecOCFreshnessValueID,SecOCTruncatedFreshnessValue,SecOCTruncatedFreshnessValueLength,
    SecOCAuthVerifyAttempts,SecOCFreshnessValue,SecOCFreshnessValueLength);
}

BufReq_ReturnType SecOC_CopyTxData (PduIdType id,const PduInfoType* info,
const RetryInfoType* retry, PduLengthType* availableDataPtr)
{
    #ifdef SECOC_DEBUG
        printf("######## in SecOC_CopyTxData \n");
    #endif
    BufReq_ReturnType result = BUFREQ_OK;
    PduInfoType *securedPdu = &(SecOCTxPduProcessing[id].SecOCTxSecuredPduLayer->SecOCTxSecuredPdu->SecOCTxSecuredLayerPduRef);
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
    #ifdef SECOC_DEBUG
        printf("The result of SecOC_CopyTxData is %d \n and the info have : ",result );
        for(int h = 0; h < info->SduLength; h++)
            printf("%d ", info->SduDataPtr[h]);
        printf("\n");
    #endif
    return result;
}

static Std_ReturnType parseSecuredPdu(PduIdType RxPduId, PduInfoType* SecPdu, SecOC_RxIntermediateType *SecOCIntermediate)
{
    #ifdef SECOC_DEBUG
        printf("######## in parseSecuredPdu \n");
    #endif
    /* Track the current byte of secured to be parsed */
    uint32 SecCursor = 0;  

    /* Get data length from configuration or header if found */
    uint32 headerLen = SecOCRxPduProcessing[RxPduId].SecOCRxSecuredPduLayer->SecOCRxSecuredPdu->SecOCAuthPduHeaderLength;
    SecOCIntermediate->authenticPduLen = 0;
    if(headerLen > 0)
    {
        /* [SWS_SecOC_00259] */
        (void)memcpy(&SecOCIntermediate->authenticPduLen, &SecPdu->SduDataPtr[SecCursor], headerLen);
        SecCursor += headerLen;
    }
    else
    {
        /* [SWS_SecOC_00257] */
        SecOCIntermediate->authenticPduLen =  SecOCRxPduProcessing[RxPduId].SecOCRxAuthenticPduLayer->SecOCRxAuthenticLayerPduRef.SduLength;
    }

    /* Copy authenticPdu to intermediate */
    (void)memcpy(SecOCIntermediate->authenticPdu, &SecPdu->SduDataPtr[SecCursor], SecOCIntermediate->authenticPduLen);
    SecCursor += SecOCIntermediate->authenticPduLen;

    uint16 authVeriAttempts = 0;
    /* Get Rx freshness from FVM using the truncated freshness in SecPdu */ 
    const uint8* SecOCTruncatedFreshnessValue = &SecPdu->SduDataPtr[SecCursor];
    uint32 SecOCTruncatedFreshnessValueLength = SecOCRxPduProcessing[RxPduId].SecOCFreshnessValueTruncLength;
    SecOCIntermediate->freshnessLenBits = SecOCRxPduProcessing[RxPduId].SecOCFreshnessValueLength;
    /* init freshness in struct SecOCIntermediate with 0 */
    (void)memset(SecOCIntermediate->freshness, 0, sizeof(SecOCIntermediate->freshness));

    SecOCIntermediate->freshnessResult = SecOC_GetRxFreshness(
            SecOCRxPduProcessing[RxPduId].SecOCFreshnessValueId,
            SecOCTruncatedFreshnessValue, 
            SecOCTruncatedFreshnessValueLength, 
            authVeriAttempts,
            SecOCIntermediate->freshness, 
            &SecOCIntermediate->freshnessLenBits
    );

    SecCursor += BIT_TO_BYTES(SecOCTruncatedFreshnessValueLength);

    /* Copy Mac to intermediate */
    SecOCIntermediate->macLenBits = SecOCRxPduProcessing[RxPduId].SecOCAuthInfoTruncLength;

    (void)memcpy(SecOCIntermediate->mac, &SecPdu->SduDataPtr[SecCursor], BIT_TO_BYTES(SecOCIntermediate->macLenBits));
    SecCursor += BIT_TO_BYTES(SecOCIntermediate->macLenBits);

    return E_OK;
}

static Std_ReturnType constructDataToAuthenticatorRx(PduIdType RxPduId, uint8 *DataToAuth, uint32 *DataToAuthLen, SecOC_RxIntermediateType *SecOCIntermediate)
{
    #ifdef SECOC_DEBUG
        printf("######## in constructDataToAuthenticatorRx \n");
    #endif
	/* Copy the Id to buffer Data to Auth */
    (void)memcpy(&DataToAuth[*DataToAuthLen], &RxPduId, sizeof(RxPduId));
    *DataToAuthLen += sizeof(RxPduId);	


    /* copy the authenticPdu to buffer DatatoAuth */
    (void)memcpy(&DataToAuth[*DataToAuthLen], SecOCIntermediate->authenticPdu, SecOCIntermediate->authenticPduLen);
    *DataToAuthLen += SecOCIntermediate->authenticPduLen;

    /* copy the freshness value to buffer Data to Auth */
    (void)memcpy(&DataToAuth[*DataToAuthLen], SecOCIntermediate->freshness, BIT_TO_BYTES(SecOCRxPduProcessing[RxPduId].SecOCFreshnessValueLength));
    *DataToAuthLen += (BIT_TO_BYTES(SecOCRxPduProcessing[RxPduId].SecOCFreshnessValueLength));

    return E_OK;
}

static Std_ReturnType verify(PduIdType RxPduId, PduInfoType* SecPdu, SecOC_VerificationResultType *verification_result)
{
    #ifdef SECOC_DEBUG
        printf("######## in verify \n");
    #endif
    /* [SWS_SecOC_00040] verifcation steps */

    SecOC_RxIntermediateType    SecOCIntermediate;

    /* [SWS_SecOC_00042] Parsing */
    parseSecuredPdu(RxPduId, SecPdu, &SecOCIntermediate);

    *verification_result = E_OK;
 
    /* [SWS_SecOC_00256] */
    if(SecOCIntermediate.freshnessResult == E_OK)
    {
        uint8 DataToAuth[SECOC_RX_DATA_TO_AUTHENTICATOR_LENGTH] = {0};
        uint32 DataToAuthLen = 0;

        /* [SWS_SecOC_00046] */
        constructDataToAuthenticatorRx(RxPduId, DataToAuth, &DataToAuthLen, &SecOCIntermediate);

        Crypto_VerifyResultType verify_var;

        /* [SWS_SecOC_00047] */
        Std_ReturnType Mac_verify = Csm_MacVerify(SecOCRxPduProcessing[RxPduId].SecOCDataId, Crypto_stub, DataToAuth, DataToAuthLen, SecOCIntermediate.mac, SecOCIntermediate.macLenBits, &verify_var);

        if (Mac_verify == E_OK) 
        {
            /* [SWS_SecOC_00242] */
            *verification_result = SECOC_VERIFICATIONSUCCESS;

            PduInfoType *authPdu = &(SecOCRxPduProcessing[RxPduId].SecOCRxAuthenticPduLayer->SecOCRxAuthenticLayerPduRef);

            /* Copy authenticPdu from secured layer to the authentic layer */
            (void)memcpy(authPdu->SduDataPtr, SecOCIntermediate.authenticPdu, SecOCIntermediate.authenticPduLen);
            authPdu->SduLength = SecOCIntermediate.authenticPduLen;
            authPdu->MetaDataPtr = SecPdu->MetaDataPtr;

            /* [SWS_SecOC_00087] */
            SecPdu->SduLength = 0;

            FVM_UpdateCounter(SecOCRxPduProcessing[RxPduId].SecOCFreshnessValueId, SecOCIntermediate.freshness, SecOCIntermediate.freshnessLenBits);
        }

        else if ( (Mac_verify == E_BUSY) || (Mac_verify == QUEUE_FULL) )
        {
            /* [SWS_SecOC_00237] */
            SecOC_RxCounters[RxPduId].AuthenticationCounter++;

            #ifdef COUNTERS_DEBUG
            printf("SecOC_RxCounters[%d].AuthenticationCounter = %d\n",RxPduId,SecOC_RxCounters[RxPduId].AuthenticationCounter);
            printf("SecOCRxPduProcessing[%d].SecOCAuthenticationBuildAttempts = %d\n",RxPduId,SecOCRxPduProcessing[RxPduId].SecOCAuthenticationBuildAttempts);
            #endif

            /* [SWS_SecOC_00240] */
            if( SecOC_RxCounters[RxPduId].AuthenticationCounter == SecOCRxPduProcessing[RxPduId].SecOCAuthenticationBuildAttempts )
            {
                SecPdu->SduLength = 0;
                *verification_result = SECOC_AUTHENTICATIONBUILDFAILURE;
            }
            else
            {
                /* [SWS_SecOC_00238] */ /* shall be retried in next call */
            }
        }

        else if ( (Mac_verify == CRYPTO_E_KEY_NOT_VALID) || (Mac_verify == CRYPTO_E_KEY_EMPTY) )/* E_NOT_OK */
        {
            /* [SWS_SecOC_00239] */
            SecOC_RxCounters[RxPduId].AuthenticationCounter = 0; 
            SecOC_RxCounters[RxPduId].VerificationCounter++;

            #ifdef COUNTERS_DEBUG
            printf("SecOC_RxCounters[%d].VerificationCounter = %d\n",RxPduId,SecOC_RxCounters[RxPduId].VerificationCounter);
            printf("SecOCRxPduProcessing[%d].SecOCAuthenticationBuildAttempts = %d\n",RxPduId,SecOCRxPduProcessing[RxPduId].SecOCAuthenticationVerifyAttempts);
            #endif

            /* [SWS_SecOC_00241] */
            if( SecOC_RxCounters[RxPduId].VerificationCounter == SecOCRxPduProcessing[RxPduId].SecOCAuthenticationVerifyAttempts )
            {
                SecPdu->SduLength = 0;
                *verification_result = SECOC_VERIFICATIONFAILURE;
            }
            else
            {
                /* [SWS_SecOC_00121] */
            }
        }

        else /* E_NOT_OK || KEY_FAILURE */
        {
            /* [SWS_SecOC_00241] */
            SecPdu->SduLength = 0;
            *verification_result = SECOC_VERIFICATIONFAILURE;
        }
    }

    else if( SecOCIntermediate.freshnessResult == E_BUSY)
    {
        /* [SWS_SecOC_00236] */
        SecOC_RxCounters[RxPduId].AuthenticationCounter++;

        #ifdef COUNTERS_DEBUG
        printf("SecOC_RxCounters[%d].AuthenticationCounter = %d\n",RxPduId,SecOC_RxCounters[RxPduId].AuthenticationCounter);
        printf("SecOCRxPduProcessing[%d].SecOCAuthenticationBuildAttempts = %d\n",RxPduId,SecOCRxPduProcessing[RxPduId].SecOCAuthenticationBuildAttempts);

        #endif

        /* [SWS_SecOC_00240] */
        if( SecOC_RxCounters[RxPduId].AuthenticationCounter == SecOCRxPduProcessing[RxPduId].SecOCAuthenticationBuildAttempts )
        {
            SecPdu->SduLength = 0;
            *verification_result = SECOC_AUTHENTICATIONBUILDFAILURE;
        }
        else
        {
            /* [SWS_SecOC_00238]  should be retried in next call */
        }
    }

    else
    {
        /* [SWS_SecOC_00256] */
        /* [SWS_SecOC_00248] */
        SecPdu->SduLength = 0;
        *verification_result = SECOC_FRESHNESSFAILURE;

        /* [SWS_SecOC_00248] */
        /* DET Report Error */
    }

    printf("%d\n",*verification_result);
    return *verification_result;
}


BufReq_ReturnType SecOC_CopyRxData (PduIdType id, const PduInfoType* info, PduLengthType* bufferSizePtr)
{
    #ifdef SECOC_DEBUG
        printf("######## in SecOC_CopyRxData \n");
    #endif
    BufReq_ReturnType result = BUFREQ_OK;

    /* Create a pointer to the secured I-PDU buffer that we will store the data into it */
    /* [SWS_SecOC_00082] */
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


#ifdef DEBUG_ALL
extern SecOC_ConfigType SecOC_Config;
void SecOC_test()
{       
}
#endif
