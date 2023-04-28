/********************************************************************************************************/
/************************************************INCULDES************************************************/
/********************************************************************************************************/
#include <stdio.h>
#include "SecOC.h"
#include "SecOC_Lcfg.h"
#include "Std_Types.h"


/********************************************************************************************************/
/******************************************GlobalVaribles************************************************/
/********************************************************************************************************/
extern SecOC_ConfigType SecOC_Config;

extern const SecOC_TxPduProcessingType     *SecOCTxPduProcessing;
extern const SecOC_RxPduProcessingType     *SecOCRxPduProcessing;
extern const SecOC_GeneralType             *SecOCGeneral;
extern SecOC_TxCountersType         SecOC_TxCounters[SECOC_NUM_OF_TX_PDU_PROCESSING];

extern Std_ReturnType authenticate(const PduIdType TxPduId, PduInfoType* AuthPdu, PduInfoType* SecPdu);
extern Std_ReturnType verify(PduIdType RxPduId, PduInfoType* SecPdu, SecOC_VerificationResultType *verification_result);
extern Std_ReturnType seperatePduCollectionTx(const PduIdType TxPduId,uint32 AuthPduLen , PduInfoType* securedPdu, PduInfoType* AuthPduCollection, PduInfoType* CryptoPduCollection, PduIdType* authPduId, PduIdType* cryptoPduId);

/********************************************************************************************************/
/********************************************Functions***************************************************/
/********************************************************************************************************/
static char* errorString(Std_ReturnType error)
{
    switch(error)
    {
        case E_OK:
            return "E_OK";
        break;
        case E_NOT_OK:
            return "E_NOT_OK";
        break;
        case E_BUSY:
            return "E_BUSY";
        break;
        case QUEUE_FULL:
            return "QUEUE_FULL";
        break;
    }
}

void GUIInterface_init()
{
    SecOC_Init(&SecOC_Config);
}

char* GUIInterface_authenticate(uint8_t configId, uint8_t *data, uint8_t len)
{

    PduInfoType *authPdu = &(SecOCTxPduProcessing[configId].SecOCTxAuthenticPduLayer->SecOCTxAuthenticLayerPduRef);
    PduInfoType *securedPdu = &(SecOCTxPduProcessing[configId].SecOCTxSecuredPduLayer->SecOCTxSecuredPdu->SecOCTxSecuredLayerPduRef);
    
    /* [SWS_SecOC_00226], [SWS_SecOC_00225] */
    SecOC_TxCounters[configId].AuthenticationCounter = 0;


    // Creating te Authentic PDU
    memcpy(authPdu->SduDataPtr, data, len);
    authPdu->SduLength = len;

    Std_ReturnType result;
    result = authenticate(configId , authPdu , securedPdu);
    authPdu->SduLength = len;

    return errorString(result);

}

char* GUIInterface_verify(uint8_t configId)
{
    PduInfoType *authPdu = &(SecOCRxPduProcessing[configId].SecOCRxAuthenticPduLayer->SecOCRxAuthenticLayerPduRef);
    PduInfoType *securedPdu = &(SecOCRxPduProcessing[configId].SecOCRxSecuredPduLayer->SecOCRxSecuredPdu->SecOCRxSecuredLayerPduRef);

    SecOC_VerificationResultType result_ver;
    Std_ReturnType result;
    result = verify(configId, securedPdu, &result_ver);

    return errorString(result);

}

char* GUIInterface_getSecuredPDU(uint8_t configId, uint8_t *len)
{
    PduInfoType *securedPdu = &(SecOCTxPduProcessing[configId].SecOCTxSecuredPduLayer->SecOCTxSecuredPdu->SecOCTxSecuredLayerPduRef);
    *len = securedPdu->SduLength;

    static char securedStr[100]; /* Static to be passed to the python program*/

    uint8_t headerIdx = SecOCTxPduProcessing[configId].SecOCTxSecuredPduLayer->SecOCTxSecuredPdu->SecOCAuthPduHeaderLength;
    uint8_t authIdx = *len - BIT_TO_BYTES(SecOCTxPduProcessing[configId].SecOCAuthInfoTruncLength);
    uint8_t freshIdx = authIdx - BIT_TO_BYTES(SecOCTxPduProcessing[configId].SecOCFreshnessValueTruncLength);
    
    int i, stri;
    for(i = 0, stri = 0; i < *len; i++)
    {
        if((headerIdx != 0 && i == headerIdx) || (i == authIdx) || ((SecOCTxPduProcessing[configId].SecOCFreshnessValueTruncLength != 0) && i == freshIdx))
        {
            stri += sprintf(&securedStr[stri], "%s", " - ");
        }
        stri += sprintf(&securedStr[stri], "%x ", securedPdu->SduDataPtr[i]);
    }
    securedStr[stri] = '\0';

    *len = stri; /* Updated the length to match the created string */
    
    return securedStr;
}

char* GUIInterface_getAuthPdu(uint8_t configId, uint8_t *len)
{
    Std_ReturnType result;
    int stri = 0;
    PduInfoType *authPdu = &(SecOCRxPduProcessing[configId].SecOCRxAuthenticPduLayer->SecOCRxAuthenticLayerPduRef);

    stri = authPdu->SduLength;
    *len = stri;

    return authPdu->SduDataPtr;
}

void GUIInterface_alterFreshness(uint8_t configId)
{
    uint32 FreshnesslenBytes = BIT_TO_BYTES(SecOCTxPduProcessing[configId].SecOCFreshnessValueTruncLength);
    PduInfoType *securedPdu = &(SecOCTxPduProcessing[configId].SecOCTxSecuredPduLayer->SecOCTxSecuredPdu->SecOCTxSecuredLayerPduRef);

    if(FreshnesslenBytes == 0 || securedPdu->SduLength == 0)
    {
        return;
    }


    uint8_t macLen = BIT_TO_BYTES(SecOCTxPduProcessing[configId].SecOCAuthInfoTruncLength);

    /* Get the offset of last freshness byte */
    uint8_t freshness_offset = securedPdu->SduLength - macLen - 1;

    securedPdu->SduDataPtr[freshness_offset]++;

}

void GUIInterface_alterAuthenticator(uint8_t configId)
{
    PduInfoType *securedPdu = &(SecOCTxPduProcessing[configId].SecOCTxSecuredPduLayer->SecOCTxSecuredPdu->SecOCTxSecuredLayerPduRef);

    if(securedPdu->SduLength == 0)
    {
        return;
    }

    securedPdu->SduDataPtr[securedPdu->SduLength - 1]++;

    
}

char* GUIInterface_transmit(uint8_t configId)
{
    Std_ReturnType result;

    /* TO BE IMPLEMENTED*/
    PduInfoType *authPdu = &(SecOCTxPduProcessing[configId].SecOCTxAuthenticPduLayer->SecOCTxAuthenticLayerPduRef);
    PduInfoType *securedPdu = &(SecOCTxPduProcessing[configId].SecOCTxSecuredPduLayer->SecOCTxSecuredPdu->SecOCTxSecuredLayerPduRef);
    SecOC_TxSecuredPduCollectionType * securePduCollection = (SecOCTxPduProcessing[configId].SecOCTxSecuredPduLayer->SecOCTxSecuredPduCollection);
    PduInfoType *AuthPduCollection;
    PduInfoType *CryptoPduCollection;

    /* Check if there is data */
    if (authPdu->SduLength > 0) 
    {
        uint32 AuthPduLen = authPdu->SduLength;

        PduIdType  authPduId , cryptoPduId;

        FVM_IncreaseCounter(SecOCTxPduProcessing[configId].SecOCFreshnessValueId);

        /* [SWS_SecOC_00201] */
        if(securePduCollection != NULL)
        {
            AuthPduCollection = &(SecOCTxPduProcessing[configId].SecOCTxSecuredPduLayer->SecOCTxSecuredPduCollection->SecOCTxAuthenticPdu->SecOCTxAuthenticPduRef);
            CryptoPduCollection = &(SecOCTxPduProcessing[configId].SecOCTxSecuredPduLayer->SecOCTxSecuredPduCollection->SecOCTxCryptographicPdu->SecOCTxCryptographicPduRef);
            seperatePduCollectionTx(configId, AuthPduLen , securedPdu , AuthPduCollection , CryptoPduCollection , &authPduId , &cryptoPduId);
            

            /* [SWS_SecOC_00062] */
            PduR_SecOCTransmit(authPduId , AuthPduCollection);
            PduR_SecOCTransmit(cryptoPduId , CryptoPduCollection);
        }
        else
        {
            /* [SWS_SecOC_00062] */
            PduR_SecOCTransmit(configId , securedPdu);
        }
        
    }

    return errorString(result);
}

char* GUIInterface_receive()
{
    Std_ReturnType result;

    /* TO BE IMPLEMENTED*/
    ethernet_RecieveMainFunction();

    return errorString(result);
}
