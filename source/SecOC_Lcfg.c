/******************************************************************************
 * File Name   : SecOC_Lcfg                                                    *
 * Description : Header file of SecOC configuration                           *
 * Created on  : November 9, 2022                                                *
 ******************************************************************************/
#include "SecOC_Cfg.h"
#include "SecOC_Lcfg.h"


/*
* Start Of General
*/

SecOC_MainFunctionTxType SecOC_MainFunctionTxConf = 
{
    SECOC_MAIN_FUNCTION_PERIOD_TX,
    SECOC_MAIN_FUNCTION_TX_PARTITION_REF, /* NOT SURE ABOUT THAT TYPE */

};


SecOC_MainFunctionRxType SecOC_MainFunctionRx = 
{
    SECOC_MAIN_FUNCTION_PERIOD_RX,
    SECOC_MAIN_FUNCTION_RX_PARTITION_REF, /* NOT SURE ABOUT THAT TYPE */

};



SecOC_GeneralType SecOC_General = 
{
    SECOC_DEFAULT_AUTHENTICATION_INFORMATION_PATTERN_VALUE,
    SECOC_DEV_ERROR_DETECT,
    SECOC_ENABLE_FORCED_PASS_OVERRIDE,
    SECOC_ENABLE_SECURITY_EVENT_REPORTING,
    SECOC_IGNORE_VERIFICATION_RESULT,
    SECOC_MAX_ALIGN_SCALAR_TYPE,
    SECOC_OVERRIDE_STATUS_WITH_DATA_ID,
    SECOC_PROPAGATE_ONLY_FINAL_VERIFICATION_STATUS,
    SECOC_QUERY_FRESHNESS_VALUE,
    // SECOC_VERIFICATION_STATUS_CALLOUT,
    SECOC_VERSION_INFO_API,
    //SECOC_SECURITY_EVENT_REFS, /* can't have the container of it */

};



SecOC_RxCryptographicPduType SecOCRxCryptographicPdu =
{
    SECOC_RX_CRYPTOGRAPHIC_PDUID,
    &EcuC_Pdu
};

SecOC_RxAuthenticPduType SecOCRxAuthenticPdu =
{
    SECOC_AUTHPDU_HEADERLENGTH,
    SECOC_RXAUTHENTIC_PDUID,
    &EcuC_Pdu
};



SecOC_UseMessageLinkType SecOC_UseMessageLink=
{
    SECOC_MESSAGE_LINKLEN,
    SECOC_MESSAGE_LINKPOS,
};

SecOC_RxSecuredPduCollectionType SecOCRxSecuredPduCollection =
{
    SECOC_SECURED_RX_PDU_VERIFICATION,
    &SecOCRxAuthenticPdu,
    &SecOCRxCryptographicPdu,
    &SecOC_UseMessageLink
};

SecOC_RxAuthenticPduLayerType SecOCRxAuthenticPduLayer = 
{
    SECOC_RX_PDUTYPE,
    SECOC_RXAUTHENTICLAYER_PDUID,
    &EcuC_Pdu
};

SecOC_RxSecuredPduType SecOCRxSecuredPdu = 
{
    SECOC_AUTHPDU_HEADERLENGTH,
    SECOC_RX_SECUREDLAYER_PDUID,
    SECOC_SECURED_RX_PDUVERIFICATION,
    &EcuC_Pdu
};

SecOC_RxSecuredPduLayerType SecOCRxSecuredPduLayer =
{
    &SecOCRxSecuredPdu,
    &SecOCRxSecuredPduCollection    
};



Csm_JobType CsmJob = 
{
    CSM_JOBID
};



SecOC_RxAuthServiceConfigRefType SecOCRxAuthServiceConfigRef = 
{
    &CsmJob
};

SecOC_SameBufferPduCollectionType SecOCSameBufferPduRef=
{
    SECOC_BUFFERLENGTH
};








SecOC_TxAuthenticPduLayerType SecOC_TxAuthenticPduLayer=
{
    SECOC_TX_PDUTYPE,
    SECOC_TX_AUTHENTIC_LAYER_PDUID,
    &EcuC_Pdu,
};

SecOC_TxSecuredPduType SecOC_TxSecuredPdu=
{
    SECOC_AUTH_PDUHEADER_LENGTH,
    SECOC_TX_SECURED_LAYER_PDUID,
    &EcuC_Pdu,
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

SecOC_TxPduSecuredAreaType SecOC_TxPduSecuredArea=
{
    SECOC_SECURED_TX_PDULENGTH,
    SECOC_SECURED_TX_PDUOFFSET,
};


SecOC_RxPduSecuredAreaType SecOC_RxPduSecuredArea=
{
    SECOC_SECURED_RX_PDULENGTH,
    SECOC_SECURED_RX_PDUOFFSET,
};




SecOC_TxPduProcessingType SecOC_TxPduProcessing = {
    SECOC_AUTHENTICATION_BUILD_ATTEMPTS,
    SECOC_AUTH_INFO_TRUNC_LENGTH,
    SECOC_TX_DATA_ID,
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
    &SecOC_TxAuthenticPduLayer,
    &SecOC_TxPduSecuredArea,
    // &EcuC_Pdu,
};



SecOC_RxPduProcessingType SecOC_RxPduProcessing = 
{
    SECOC_AUTHDATA_FRESHNESSLEN,
    SECOC_AUTHDATA_FRESHNESS_STARTPOSITION,
    SECOC_AUTHENTICATION_BUILDATTEMPTS,
    SECOC_AUTHENTICATION_VERIFYATTEMPTS,
    SECOC_AUTHINFO_TRUNCLENGTH,
    SECOC_CLIENTSERVER_VERIFICATIONSTATUS_PROPAGATIONMODE,
    SECOC_RX_DATA_ID,
    SECOC_FRESHNESSVALUE_ID,
    SECOC_FRESHNESSVALUE_LENGTH,
    SECOC_FRESHNESSVALUE_TRUNCLENGTH,
    SECOC_RECEPTION_OVERFLOW_STRATEGY,
    SECOC_RECEPTION_QUEUESIZE,
    SECOC_USE_AUTHDATA_FRESHNESS,
    SECOC_VERIFICATIONSTATUS_PROPAGATIONMODE,
    &SecOCRxAuthServiceConfigRef,
    &SecOC_MainFunctionRx,
    &SecOCSameBufferPduRef,
    &SecOCRxSecuredPduLayer,
    &SecOCRxAuthenticPduLayer,
    &SecOC_RxPduSecuredArea
};