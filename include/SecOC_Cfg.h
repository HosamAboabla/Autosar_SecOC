#ifndef INCLUDE_SECOC_CFG_H_
#define INCLUDE_SECOC_CFG_H_

/*- INCLUDES -----------------------------------------------*/
#include "Std_Types.h"

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
typedef uint16              SecOCMainFunctionTxPartitionRefType;


typedef struct SecOCMainFunctionRx
{
    float64 SecOCMainFunctionPeriodTx;
    SecOCMainFunctionTxPartitionRefType *SecOCMainFunctionTxPartitionRef;

}SecOCMainFunctionRxType;






/*************************************************************
*                          Container                         *
* Name : SecOCMainFunctionRx                                 *
* Description : Each element of this container defines one   *
* instance of SecOC_MainFunctionRx.                          *
* parent : SecOC                                             *
* Index : 10.1.3                                             *
**************************************************************/



/***NOT SURE ABOUT THAT TYPE*/
typedef uint16              SecOCMainFunctionRxPartitionRefType;

typedef struct SecOCMainFunctionRx
{
    float64 SecOCMainFunctionPeriodRx;
    SecOCMainFunctionRxPartitionRefType *SecOCMainFunctionRxPartitionRef;

}SecOCMainFunctionRxType;








/*container ->dont know where is it*/
typedef struct SecOCSecurityEventRefs
{
    
}SecOCSecurityEventRefsType;

typedef enum {
    CFUNC,
    RTE,
} SecOCQueryFreshnessValueType;


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


typedef struct SecOC_general
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
    SecOCQueryFreshnessValueType SecOCQueryFreshnessValue;
    SecOC_VerificationStatusCalloutType SecOCVerificationStatusCallout;
    boolean SecOCVersionInfoApi;
    SecOCSecurityEventRefsType *SecOCSecurityEventRefs;

}SecOC_GeneralType;


#endif /*SecOC_Cfg.h*/

