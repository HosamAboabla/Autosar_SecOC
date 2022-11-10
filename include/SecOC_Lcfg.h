#ifndef INCLUDE_SECOC_LCFG_H_
#define INCLUDE_SECOC_LCFG_H_


/*- INCLUDES -----------------------------------------------*/
#include "Std_Types.h"
#include "Rte_SecOC.h"
/*- CONSTANTS ----------------------------------------------*/
/*- PRIMITIVE TYPES ----------------------------------------*/
/*- ENUMS --------------------------------------------------*/
/*- STRUCTS AND UNIONS -------------------------------------*/
/*- FUNCTION-LIKE MACROS -----------------------------------*/
/*- FUNCTION DECLARATIONS ----------------------------------*/





/*************************************************************
*                          Container                         *
* Name : SecOCMainFunctionTx                                 *
* Description : Each element of this container defines one   *
* instance of SecOC_MainFunctionTx.                          *
* parent : SecOC                                             *
* Index : 10.1.4                                             *
**************************************************************/

/***NOT SURE ABOUT THAT TYPE*/
typedef uint16              SecOC_MainFunctionTxPartitionRefType;


typedef struct 
{
    float64 SecOCMainFunctionPeriodTx;
    SecOC_MainFunctionTxPartitionRefType *SecOCMainFunctionTxPartitionRef;

}SecOC_MainFunctionRxType;






/*************************************************************
*                          Container                         *
* Name : SecOCMainFunctionRx                                 *
* Description : Each element of this container defines one   *
* instance of SecOC_MainFunctionRx.                          *
* parent : SecOC                                             *
* Index : 10.1.3                                             *
**************************************************************/



/***NOT SURE ABOUT THAT TYPE*/
typedef uint16              SecOC_MainFunctionRxPartitionRefType;

typedef struct 
{
    float64 SecOCMainFunctionPeriodRx;
    SecOC_MainFunctionRxPartitionRefType *SecOCMainFunctionRxPartitionRef;

}SecOC_MainFunctionRxType;








/*container ->dont know where is it*/
typedef struct
{
    
}SecOC_SecurityEventRefsType;

typedef enum {
    CFUNC,
    RTE,
} SecOC_QueryFreshnessValueType;






/*callout function --> what should i do*/


typedef void (*SecOC_VerificationStatusCalloutType) (SecOC_VerificationStatusType verificationStatus);




/*************************************************************
*                          Container                         *
* Name : SecOCGeneral                                        *
* Description : Contains the general configuration           *
* parameters of the SecOC module.                            *
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
    /*
    EcucStringParamDef 
    This type can be e.g. uint8, uint16 or uint32.
    */
    uint8 SecOCMaxAlignScalarType[100];
    boolean SecOCOverrideStatusWithDataId;
    boolean SecOCPropagateOnlyFinalVerificationStatus;
    SecOC_QueryFreshnessValueType SecOCQueryFreshnessValue;
    SecOC_VerificationStatusCalloutType SecOCVerificationStatusCallout;
    boolean SecOCVersionInfoApi;
    SecOC_SecurityEventRefsType *SecOCSecurityEventRefs;

}SecOC_GeneralType;


#endif