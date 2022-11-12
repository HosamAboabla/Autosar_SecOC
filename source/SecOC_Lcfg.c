/******************************************************************************
 * File Name   : Std_Types                                                    *
 * Description : Header file of SecOC configuration                           *
 * Created on  : April 6, 2020                                                *
 ******************************************************************************/

#include "SecOC_Lcfg.h"
#include "SecOC_Cfg.h"

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
