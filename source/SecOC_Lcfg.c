/******************************************************************************
 * File Name   : Std_Types                                                    *
 * Description : Header file of SecOC configuration                           *
 * Created on  : April 6, 2020                                                *
 ******************************************************************************/

#include "SecOC_Lcfg.h"
#include "SecOC_Cfg.h"



SecOC_MainFunctionTxType SecOC_MainFunctionTx = 
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
    SECOC_VERIFICATION_STATUS_CALLOUT,
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

SecOC_RxSecuredPduCollectionType SecOCRxSecuredPduCollection =
{
    SECOC_SECURED_RX_PDU_VERIFICATION,
    &SecOCRxAuthenticPdu,
    &SecOCRxCryptographicPdu,
    &SecOCUseMessageLink
};

SecOC_RxAuthenticPduLayerType SecOCRxAuthenticPduLayer = 
{
    SECOC_PDUTYPE,
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

SecOC_RxPduProcessingType SecOCRxPduProcessing = 
{
    SECOC_AUTHDATA_FRESHNESSLEN,
    SECOC_AUTHDATA_FRESHNESS_STARTPOSITION,
    SECOC_AUTHENTICATION_BUILDATTEMPTS,
    SECOC_AUTHENTICATION_VERIFYATTEMPTS,
    SECOC_AUTHINFO_TRUNCLENGTH,
    SECOC_CLIENTSERVER_VERIFICATIONSTATUS_PROPAGATIONMODE,
    SECOC_DATA_ID,
    SECOC_FRESHNESSVALUE_ID,
    SECOC_FRESHNESSVALUE_LENGTH,
    SECOC_FRESHNESSVALUE_TRUNCLENGTH,
    SECOC_RECEPTION_OVERFLOW_STRATEGY,
    SECOC_RECEPTION_QUEUESIZE,
    SECOC_USE_AUTHDATA_FRESHNESS,
    SECOC_VERIFICATIONSTATUS_PROPAGATIONMODE,
    &SecOCRxAuthServiceConfigRef,
    &SecOCRxPduMainFunctionRef,
    &SecOCSameBufferPduRef,
    &SecOCRxSecuredPduLayer,
    &SecOCRxAuthenticPduLayer,
    &SecOCRxPduSecuredArea
};
