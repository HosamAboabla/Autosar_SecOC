#ifndef INCLUDE_SECOC_LCFG_H_
#define INCLUDE_SECOC_LCFG_H_


#include "Std_Types.h"
#include "Rte_SecOC.h"






/*************************************************************
*                          Container                         *
* Name : SecOCMainFunctionTx                                 *
* parent : SecOC                                             *
* Index : 10.1.4                                             *
**************************************************************/

typedef uint16              SecOC_MainFunctionTxPartitionRefType;/* NOT SURE ABOUT THAT TYPE */


typedef struct 
{
    float64 SecOCMainFunctionPeriodTx;
    SecOC_MainFunctionTxPartitionRefType *SecOCMainFunctionTxPartitionRef; /* NOT SURE ABOUT THAT TYPE */

}SecOC_MainFunctionTxType;






/*************************************************************
*                          Container                         *
* Name : SecOCMainFunctionRx                                 *
* parent : SecOC                                             *
* Index : 10.1.3                                             *
**************************************************************/

typedef uint16              SecOC_MainFunctionRxPartitionRefType; /* NOT SURE ABOUT THAT TYPE */

typedef struct 
{
    float64 SecOCMainFunctionPeriodRx;
    SecOC_MainFunctionRxPartitionRefType *SecOCMainFunctionRxPartitionRef; /* NOT SURE ABOUT THAT TYPE */

}SecOC_MainFunctionRxType;







/*
/*container ->dont know where is it
typedef struct
{
    
}SecOC_SecurityEventRefsType;
*/

typedef enum {
    CFUNC,
    RTE,
} SecOC_QueryFreshnessValueType;




/* callout function --> what should i do */
typedef void (*SecOC_VerificationStatusCalloutType) (SecOC_VerificationStatusType verificationStatus);




/*************************************************************
*                          Container                         *
* Name : SecOCGeneral                                        *
* parent : SecOC                                             *
* Index : 10.1.2                                             *
**************************************************************/


typedef struct 
{
    uint8 SecOCDefaultAuthenticationInformationPattern;
    boolean SecOCDevErrorDetect;
    boolean SecOCEnableForcedPassOverride;
    boolean SecOCEnableSecurityEventReporting;
    boolean SecOCIgnoreVerificationResult;
    uint8 SecOCMaxAlignScalarType[100];  /* This type can be e.g. uint8, uint16 or uint32.*/
    boolean SecOCOverrideStatusWithDataId;
    boolean SecOCPropagateOnlyFinalVerificationStatus;
    SecOC_QueryFreshnessValueType SecOCQueryFreshnessValue;
    SecOC_VerificationStatusCalloutType SecOCVerificationStatusCallout;
    boolean SecOCVersionInfoApi;
    //SecOC_SecurityEventRefsType *SecOCSecurityEventRefs; /* can't have the container of it */

}SecOC_GeneralType;


#endif