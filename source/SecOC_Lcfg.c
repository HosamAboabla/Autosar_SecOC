/******************************************************************************
 * File Name   : SecOC_Lcfg                                                    *
 * Description : Header file of SecOC configuration                           *
 * Created on  : November 9, 2022                                                *
 ******************************************************************************/
#include "SecOC_Cfg.h"
#include "SecOC_Lcfg.h"

SecOC_TxAuthenticPduLayerType SecOC_TxAuthenticPduLayer=
{
    SECOC_PDU_TYPE,
    SECOC_TX_AUTHENTIC_LAYER_PDUID,
    &EcuC_Pdu,
};

SecOC_TxSecuredPduType SecOC_TxSecuredPdu=
{
    SECOC_AUTH_PDU_HEADER_LENGTH,
    SECOC_TX_SECURED_LAYER_PDUID,
    &EcuC_Pdu,
};

















































































// SecOC_TxAuthenticPduLayerType SecOC_TxAuthenticPduLayer = 
// {
//     SECOC_PDU_TYPE,
//     SECOC_TX_AUTHENTIC_LAYER_PDU_ID,
// }

SecOC_TxPduProcessingType SecOC_TxPduProcessing = {
    SECOC_AUTHENTICATION_BUILD_ATTEMPTS,
    SECOC_AUTH_INFO_TRUNC_LENGTH,
    SECOC_DATA_ID,
    SECOC_FRESHNESS_VALUE_ID,
    SECOC_FRESHNESS_VALUE_LENGTH,
    SECOC_FRESHNESS_VALUE_TRUNC_LENGTH,
    SECOC_PROVIDE_TX_TRUNCATED_FRESHNESS_VALUE,
    SECOC_RE_AUTHENTICATE_AFTER_TRIGGER_TRANSMIT,
    SECOC_TX_PDU_UNUSED_AREAS_DEFAULT,
    SECOC_USE_TX_CONFIRMATION,
    //                                                  SecOCSameBufferPduRef;
    //                                                  SecOCTxAuthServiceConfigRef
    //                                                  SecOCTxPduMainFunctionRef;

};


