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