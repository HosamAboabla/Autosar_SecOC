#include "SecOC.h"
#
#include "SecOC_Lcfg.h"
#include <stdio.h>

extern SecOC_ConfigType SecOC_Config;

const SecOC_TxPduProcessingType     *SecOCTxPduProcessing;
const SecOC_RxPduProcessingType     *SecOCRxPduProcessing;
const SecOC_GeneralType             *SecOCGeneral;

extern Std_ReturnType authenticate(const PduIdType TxPduId, PduInfoType* AuthPdu, PduInfoType* SecPdu);

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
    
    // Creating te Authentic PDU
    memcpy(authPdu->SduDataPtr, data, len);
    authPdu->SduLength = len;

    Std_ReturnType result;
    result = authenticate(configId , authPdu , securedPdu);

    return errorString(result);

}

uint8_t* GUIInterface_getSecuredPDU(uint8_t configId, uint8_t *len)
{
    PduInfoType *securedPdu = &(SecOCTxPduProcessing[configId].SecOCTxSecuredPduLayer->SecOCTxSecuredPdu->SecOCTxSecuredLayerPduRef);
    
    *len = securedPdu->SduLength;
    return securedPdu->SduDataPtr;
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

