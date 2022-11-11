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
    SECOC_DEFAULT_AUTHENTICATION_INFORMATION_PATTERN,
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