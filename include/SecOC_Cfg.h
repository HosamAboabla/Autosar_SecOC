#ifndef INCLUDE_SECOC_CFG_H_
#define INCLUDE_SECOC_CFG_H_


/*************************************************************
*                          Container                         *
* Name : SecOCMainFunctionTx                                 *
* parent : SecOC                                             *
* Index : 10.1.4                                             *
**************************************************************/

/*
* Configration parameter for SecOCMainFunctionPeriodTx
*/
#define SECOC_MAIN_FUNCTION_PERIOD_TX                       ((float64)0)    

/*
* Configration parameter for SecOCMainFunctionTxPartitionRef
*/
#define SECOC_MAIN_FUNCTION_TX_PARTITION_REF                ((SecOC_MainFunctionTxPartitionRefType)NULL)  




/*************************************************************
*                          Container                         *
* Name : SecOCMainFunctionRx                                 *
* parent : SecOC                                             *
* Index : 10.1.3                                             *
**************************************************************/

/*
* Configration parameter for SecOCMainFunctionPeriodRx
*/
#define SECOC_MAIN_FUNCTION_PERIOD_RX                       ((float64)0)    

/*
* Configration parameter for SecOCMainFunctionRxPartitionRef
*/
#define SECOC_MAIN_FUNCTION_RX_PARTITION_REF                ((SecOC_MainFunctionRxPartitionRefType)NULL)    




/*************************************************************
*                          Container                         *
* Name : SecOCGeneral                                        *
* parent : SecOC                                             *
* Index : 10.1.2                                             *
**************************************************************/

/*
* Configration parameter for SecOCDefaultAuthenticationInformationPatternMultiplicity
*/
#define SECOC_DEFAULT_AUTHENTICATION_INFORMATION_PATTERN_MULTIPLICITY     ((uint8)0)      
 
 /*
* Configration parameter for SecOCDefaultAuthenticationInformationPatternValue
*/
#define SECOC_DEFAULT_AUTHENTICATION_INFORMATION_PATTERN_VALUE     ((uint8)0)
 
/* 
* Configration parameter for SecOCDevErrorDetect 
*/ 
#define SECOC_DEV_ERROR_DETECT                               ((boolean)FALSE)


/* 
* Configration parameter for SecOCEnableForcedPassOverride 
*/ 
#define SECOC_ENABLE_FORCED_PASS_OVERRIDE                    ((boolean)FALSE)     
 

/* 
* Configration parameter for SecOCEnableSecurityEventReporting 
*/ 
#define SECOC_ENABLE_SECURITY_EVENT_REPORTING                 ((boolean)FALSE)   


/* 
* Configration parameter for SecOCIgnoreVerificationResult 
*/ 
#define SECOC_IGNORE_VERIFICATION_RESULT                       ((boolean)FALSE)


/* 
* Configration parameter for SecOCMaxAlignScalarType 
*/ 
#define SECOC_MAX_ALIGN_SCALAR_TYPE                             ((uint8)0)


/* 
* Configration parameter for SecOCOverrideStatusWithDataId 
*/ 
#define SECOC_OVERRIDE_STATUS_WITH_DATA_ID                      ((boolean)FALSE)


/* 
* Configration parameter for SecOCPropagateOnlyFinalVerificationStatus 
*/ 
#define SECOC_PROPAGATE_ONLY_FINAL_VERIFICATION_STATUS          ((boolean)FALSE)


/* 
* Configration parameter for SecOCQueryFreshnessValue 
*/ 
#define SECOC_QUERY_FRESHNESS_VALUE                             ((SecOC_QueryFreshnessValueType)CFUNC)


/* 
* Configration parameter for SecOCVerificationStatusCallout 
*/ 
#define SECOC_VERIFICATION_STATUS_CALLOUT                       ((SecOC_VerificationStatusCalloutType)NULL) /* Here a address for function */



/* 
* Configration parameter for SecOCVersionInfoApi 
*/ 
#define SECOC_VERSION_INFO_API                                  ((boolean)FALSE)



// /* NOTE i don't container  */
// /* 
// * Configration parameter for SecOCSecurityEventRefs 
// */ 
// #define SECOC_SECURITY_EVENT_REFS                                  ((SecOC_SecurityEventRefsType)NULL)




#endif