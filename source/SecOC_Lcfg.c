/******************************************************************************
 * File Name   : SecOC_Lcfg                                                    *
 * Description : Header file of SecOC configuration                           *
 * Created on  : November 9, 2022                                                *
 ******************************************************************************/
#include "SecOC_Cfg.h"
#include "SecOC_Lcfg.h"

SecOC_TxAuthenticPduLayerType SecOC_TxAuthenticPduLayer=
{
    SECOC_IFPDU,
    SECOC_TX_AUTHENTIC_LAYER_PDUID,
    &EcuC_Pdu,
};