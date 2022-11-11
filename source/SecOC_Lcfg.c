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
    SECOC_TX_AUTHENTIC_LAYER_PDUREF,
};

SecOC_TxSecuredPduType SecOC_TxSecuredPdu=
{
    SECOC_AUTH_PDU_HEADER_LENGTH,
    SECOC_TX_SECURED_LAYER_PDUID,
    SECOC_TX_SECURED_LAYER_PDUREF,
};

SecOC_UseMessageLinkType SecOC_UseMessageLink=
{
    SECOC_MESSAGE_LINKLEN,
    SECOC_MESSAGE_LINKPOS,
};

SecOC_TxCryptographicPduType SecOC_TxCryptographicPdu=
{
    SECOC_TX_CRYPTOGRAPHIC_PDUID,
    SECOC_TX_CRYPTOGRAPHIC_PDUREF,
};

SecOC_TxAuthenticPduType SecOC_TxAuthenticPdu=
{
    SECOC_AUTH_PDUHEADER_LENGTH,
    SECOC_TX_AUTHENTIC_PDUID,
    SECOC_TX_AUTHENTIC_PDUREF,
};

SecOC_TxSecuredPduCollectionType SecOC_TxSecuredPduCollection=
{
    &SecOC_TxAuthenticPdu,
    &SecOC_TxCryptographicPdu,
    &SecOC_UseMessageLink,
};


