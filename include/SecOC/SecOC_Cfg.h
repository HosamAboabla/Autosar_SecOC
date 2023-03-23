#ifndef INCLUDE_SECOC_CFG_H_
#define INCLUDE_SECOC_CFG_H_



/*
* Start of General
*/


/*************************************************************
*                          Container                         *
* Name : SecOCMainFunctionTx                                 *
* parent : SecOC                                             *
* Index : 10.1.4                                             *
**************************************************************/

/*
* Configration parameter for SecOCMainFunctionPeriodTx
*/
#define SECOC_MAIN_FUNCTION_PERIOD_TX                                   ((float64)0)    

/*
* Configration parameter for SecOCMainFunctionTxPartitionRef
*/
#define SECOC_MAIN_FUNCTION_TX_PARTITION_REF                            ((SecOC_MainFunctionTxPartitionRefType*)NULL)  




/*************************************************************
*                          Container                         *
* Name : SecOCMainFunctionRx                                 *
* parent : SecOC                                             *
* Index : 10.1.3                                             *
**************************************************************/

/*
* Configration parameter for SecOCMainFunctionPeriodRx
*/
#define SECOC_MAIN_FUNCTION_PERIOD_RX                                   ((float64)0)    

/*
* Configration parameter for SecOCMainFunctionRxPartitionRef
*/
#define SECOC_MAIN_FUNCTION_RX_PARTITION_REF                            ((SecOC_MainFunctionRxPartitionRefType*)NULL)    




/*************************************************************
*                          Container                         *
* Name : SecOCGeneral                                        *
* parent : SecOC                                             *
* Index : 10.1.2                                             *
**************************************************************/

/*
* Configration parameter for SecOCDefaultAuthenticationInformationPatternMultiplicity
*/
#define SECOC_DEFAULT_AUTHENTICATION_INFORMATION_PATTERN_MULTIPLICITY    ((uint8)0)      
 
 /*
* Configration parameter for SecOCDefaultAuthenticationInformationPatternValue
*/
#define SECOC_DEFAULT_AUTHENTICATION_INFORMATION_PATTERN_VALUE           ((uint8)0)
 
/* 
* Configration parameter for SecOCDevErrorDetect 
*/ 
#define SECOC_DEV_ERROR_DETECT                                           ((boolean)FALSE)


/* 
* Configration parameter for SecOCEnableForcedPassOverride 
*/ 
#define SECOC_ENABLE_FORCED_PASS_OVERRIDE                                ((boolean)FALSE)     
 

/* 
* Configration parameter for SecOCEnableSecurityEventReporting 
*/ 
#define SECOC_ENABLE_SECURITY_EVENT_REPORTING                            ((boolean)FALSE)   


/* 
* Configration parameter for SecOCIgnoreVerificationResult 
*/ 
#define SECOC_IGNORE_VERIFICATION_RESULT                                 ((boolean)FALSE)


/* 
* Configration parameter for SecOCMaxAlignScalarType 
*/ 
#define SECOC_MAX_ALIGN_SCALAR_TYPE                                      ((uint8)0)


/* 
* Configration parameter for SecOCOverrideStatusWithDataId 
*/ 
#define SECOC_OVERRIDE_STATUS_WITH_DATA_ID                              ((boolean)FALSE)


/* 
* Configration parameter for SecOCPropagateOnlyFinalVerificationStatus 
*/ 
#define SECOC_PROPAGATE_ONLY_FINAL_VERIFICATION_STATUS                   ((boolean)FALSE)


/* 
* Configration parameter for SecOCQueryFreshnessValue 
*/ 
#define SECOC_QUERY_FRESHNESS_VALUE                                     ((SecOC_QueryFreshnessValue_Type)SECOC_CFUNC)


/* 
* Configration parameter for SecOCVerificationStatusCallout 
*/ 
#define SECOC_VERIFICATION_STATUS_CALLOUT                               ((SecOC_VerificationStatusCalloutType*)NULL) /* Here a address for function */



/* 
* Configration parameter for SecOCVersionInfoApi 
*/ 
#define SECOC_VERSION_INFO_API                                          ((boolean)FALSE)



/* NOTE i don't container  */
/* 
* Configration parameter for SecOCSecurityEventRefs 
*/ 
/* #define SECOC_SECURITY_EVENT_REFS                                  ((SecOC_SecurityEventRefsType)NULL)*/




/*
* End Of General
*/


/*
* Start of RxPduProcessing
*/



/*****************************************
 *          * Container Info *           *
 *                                       *
 * Container_Name        : SecOCSameBufferPduCollection *
 * Parent_Container_Name : SecOC           *
 * Container_Index       : 10.1.5        *
 *****************************************/

/*
* Configuration Parameter for SecOCBufferLength
*/
#define SECOC_BUFFERLENGTH                  ((uint32)100)

/*****************************************
 *          * Container Info *           *
 *                                       *
 * Container_Name        : SecOCRxPduProcessing *
 * Parent_Container_Name : SecOC           *
 * Container_Index       : 10.1.6        *
 *****************************************/

/*
* Configuration Parameter for SecOC_AuthDataFreshnessLen
*/
#define SECOC_AUTHDATA_FRESHNESSLEN     ((uint16)0)

/*
* Configuration Parameter for SecOC_AuthDataFreshnessStartPosition
*/
#define SECOC_AUTHDATA_FRESHNESS_STARTPOSITION      ((uint16)5)

/*
* Configuration Parameter for SecOC_AuthenticationBuildAttempts
*/
#define SECOC_AUTHENTICATION_BUILDATTEMPTS      ((uint16)3)

/*
* Configuration Parameter for SecOC_AuthenticationVerifyAttempts
*/
#define SECOC_AUTHENTICATION_VERIFYATTEMPTS     ((uint16)3)

/*
* Configuration Parameter for SecOC_AuthInfoTruncLength
*/
#define SECOC_RX_AUTH_INFO_TRUNCLENGTH      ((uint16)32)

/*
* Configuration Parameter for SecOC_ClientServerVerificationStatusPropagationMode
*/
#define SECOC_CLIENTSERVER_VERIFICATIONSTATUS_PROPAGATIONMODE       ((SecOC_StatusPropagationMode_Type)SECOC_NONE)

/*
* Configuration Parameter for SecOC_DataId
*/
#define SECOC_RX_DATA_ID        ((uint16)0)

/*
* Configuration Parameter for SecOC_FreshnessValueId
*/
#define SECOC_FRESHNESSVALUE_ID      ((uint16)10)

/*
* Configuration Parameter for SecOC_FreshnessValueLength
*/
#define SECOC_RX_FRESHNESS_VALUE_LENGTH     ((uint8)16)

/*
* Configuration Parameter for SecOC_FreshnessValueTruncLength
*/
#define SECOC_RX_FRESHNESS_VALUE_TRUNCLENGTH        ((uint8)14)

/*
* Configuration Parameter for SecOC_ReceptionOverflowStrategy
*/
#define SECOC_RECEPTION_OVERFLOW_STRATEGY       SECOC_QUEUE

/*
* Configuration Parameter for SecOC_ReceptionQueueSize
*/
#define SECOC_RECEPTION_QUEUESIZE       ((uint16)10)

/*
* Configuration Parameter for SecOC_UseAuthDataFreshness
*/
#define SECOC_USE_AUTHDATA_FRESHNESS        FALSE

/*
* Configuration Parameter for SecOC_VerificationStatusPropagationMode
*/
#define SECOC_VERIFICATIONSTATUS_PROPAGATIONMODE        ((SecOC_StatusPropagationMode_Type)SECOC_NONE)

/*
* Configuration Parameter for Csm_JobId
*/
#define CSM_JOBID        ((uint32)10)


/*****************************************
 *          * Container Info *           *
 *                                       *
 * Container_Name        : SecOCRxSecuredPdu *
 * Parent_Container_Name : SecOCRxSecuredPduLayer           *
 * Container_Index       : 10.1.8        *
 *****************************************/
/*
* Configuration Parameter for SecOC_AuthPduHeaderLength
*/
#define SECOC_AUTHPDU_HEADERLENGTH      ((uint8)1)

/*
* Configuration Parameter for SecOC_RxSecuredLayerPduId
*/
#define SECOC_RX_SECUREDLAYER_PDUID        ((uint16)10)

/*
* Configuration Parameter for SecOC_SecuredRxPduVerification
*/
#define SECOC_SECURED_RX_PDUVERIFICATION        FALSE


/*****************************************
 *          * Container Info *           *
 *                                       *
 * Container_Name        : SecOCRxAuthenticPduLayer *
 * Parent_Container_Name : SecOCRxPduProcessing           *
 * Container_Index       : 10.1.9        *
 *****************************************/

/*
* Configuration Parameter for SecOC_Pdu
*/
#define SECOC_RX_PDUTYPE       SECOC_IFPDU

/*
* Configuration Parameter for SecOC_RxAuthenticLayerPduId
*/
#define SECOC_RXAUTHENTICLAYER_PDUID        ((uint16)10)

/*****************************************
 *          * Container Info *           *
 *                                       *
 * Container_Name        : SecOCRxSecuredPduCollection *
 * Parent_Container_Name : SecOCRxSecuredPduLayer           *
 * Container_Index       : 10.1.10        *
 *****************************************/
/*
* Configuration Parameter for SecOC_SecuredRxPduVerification
*/
#define SECOC_SECURED_RX_PDU_VERIFICATION       FALSE

/*****************************************
 *          * Container Info *           *
 *                                       *
 * Container_Name        : SecOCRxAuthenticPdu *
 * Parent_Container_Name : SecOCRxSecuredPduCollection           *
 * Container_Index       : 10.1.12        *
 *****************************************/
/*
* Configuration Parameter for SecOC_AuthPduHeaderLength
*/
#define SECOC_CRYPTO_AUTHPDU_HEADERLENGTH      ((uint8)1)

/*
* Configuration Parameter for SecOC_RxAuthenticPduId
*/
#define SECOC_CRYPTO_RXAUTHENTIC_PDUID         ((uint16)0)


/*****************************************
 *          * Container Info *           *
 *                                       *
 * Container_Name        : SecOCRxCryptographicPdu *
 * Parent_Container_Name : SecOCRxSecuredPduCollection           *
 * Container_Index       : 10.1.11        *
 *****************************************/
/*
* Configuration Parameter for SecOC_RxCryptographicPduId
*/
#define SECOC_RX_CRYPTOGRAPHIC_PDUID        ((uint16)0)



/*
* End of General
*/



/*
* Start of TxPduProcessing
*/





/**************************************************************
 *          * Container Info *                                *
 *                                                            *
 * Container_Name        : SecOC_TxAuthenticPduLayer          *
 * Parent_Container_Name : SecOC_TxPduProcessing              *
 * Container_Index       : 10.1.14                            *
 **************************************************************/

#define SECOC_TX_PDUTYPE                    ((SecOC_PduType_Type)SECOC_IFPDU)
#define SECOC_TX_AUTHENTIC_LAYER_PDUID      ((uint16)0)


/**************************************************************
 *          * Container Info *                                *
 *                                                            *
 * Container_Name        : SecOC_TxSecuredPdu                 *
 * Parent_Container_Name : SecOC_TxSecuredPduLayer             *
 * Container_Index       : 10.1.16                            *
 **************************************************************/

#define SECOC_AUTH_PDUHEADER_LENGTH        ((uint8)1)
#define SECOC_TX_SECURED_LAYER_PDUID        ((uint16)0)


/************************************************************
 *          * Container Info *                              *
 *                                                          *
 * Container_Name        : SecOC_UseMessageLink             *
 * Parent_Container_Name : SecOC_TxSecuredPduCollection     *
 * Container_Index       : 10.1.20                          *
 ***********************************************************/

#define SECOC_MESSAGE_LINKLEN               ((uint16)3)
#define SECOC_MESSAGE_LINKPOS               ((uint16)5)

/************************************************************
 *          * Container Info *                              *
 *                                                          *
 * Container_Name        : SecOC_TxCryptographicPdu         *
 * Parent_Container_Name : SecOC_TxSecuredPduCollection     *
 * Container_Index       : 10.1.19                          *
 ***********************************************************/

#define SECOC_TX_CRYPTOGRAPHIC_PDUID        ((uint16)0)
#define SECOC_TX_CRYPTOGRAPHIC_PDUREF       ((EcuC_PduType*)NULL) /*((EcuC_PduType*)&EcuC_Pdu)*/

/************************************************************
 *          * Container Info *                              *
 *                                                          *
 * Container_Name        : SecOC_TxAuthenticPdu             *
 * Parent_Container_Name : SecOC_TxSecuredPduCollection     *
 * Container_Index       : 10.1.18                          *
 ***********************************************************/

#define SECOC_CRYPTO_AUTH_PDUHEADER_LENGTH         ((uint8)1)
#define SECOC_CRYPTO_TX_AUTHENTIC_PDUID            ((uint16)0)
#define SECOC_CRYPTO_TX_AUTHENTIC_PDUREF           



/****************************************************
 *          * Container Info *                      *
 *                                                  *
 * Container_Name        : SecOC_RxPduSecuredArea   *
 * Parent_Container_Name : SecOC_RxPduProcessing    *
 * Container_Index       : 10.1.22                  *
 ***************************************************/          

#define SECOC_SECURED_RX_PDULENGTH          ((uint32)0)
#define SECOC_SECURED_RX_PDUOFFSET          ((uint32)0)



/****************************************************
 *          * Container Info *                      *
 *                                                  *
 * Container_Name        : SecOC_TxPduSecuredArea   *
 * Parent_Container_Name : SecOC_TxPduProcessing    *
 * Container_Index       : 10.1.21                  *
 ***************************************************/          

#define SECOC_SECURED_TX_PDULENGTH          ((uint32)0)
#define SECOC_SECURED_TX_PDUOFFSET          ((uint32)0)







/****************************************************
 *          * Container Info *                      *
 *                                                  *
 * Container_Name        : SecOC_TxPduProcessing    *
 * Parent_Container_Name :                          *
 * Container_Index       : 10.1.11                  *
 ***************************************************/

#define SECOC_AUTHENTICATION_BUILD_ATTEMPTS                         ((uint16) 5)
#define SECOC_TX_AUTH_INFO_TRUNC_LENGTH                             ((uint16) 32)
#define SECOC_TX_DATA_ID                                            ((uint16) 0)
#define SECOC_TX_FRESHNESS_VALUE_ID                                 ((uint16) 9)
#define SECOC_TX_FRESHNESS_VALUE_LENGTH                             ((uint8) 16)
#define SECOC_TX_FRESHNESS_VALUE_TRUNC_LENGTH                       ((uint8 ) 14)
#define SECOC_PROVIDE_TX_TRUNCATED_FRESHNESS_VALUE                  ((boolean) TRUE)
#define SECOC_RE_AUTHENTICATE_AFTER_TRIGGER_TRANSMIT                ((boolean) 1)
#define SECOC_TX_PDU_UNUSED_AREAS_DEFAULT                           ((uint8) 0)
#define SECOC_USE_TX_CONFIRMATION                                   (0)

/*                                                  SecOCSameBufferPduRef;*/
/*                                                  SecOCTxAuthServiceConfigRef*/
/*                                                  SecOCTxPduMainFunctionRef;*/



/*
* End of TxPduProcessing
*/

#endif