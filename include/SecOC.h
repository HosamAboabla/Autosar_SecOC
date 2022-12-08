#ifndef INCLUDE_SECOC_H_
#define INCLUDE_SECOC_H_

#include "SecOC_Cfg.h"
#include "SecOC_Types.h"

void SecOC_MainFunctionTx ( void );


Std_ReturnType SecOC_IfTransmit(
    PduIdType                  TxPduId,
    const PduInfoType*         PduInfoPtr
);

void SecOC_TxConfirmation (PduIdType TxPduId,Std_ReturnType result);

/*******************************************************
 *          * Function Info *                           *
 *                                                      *
 * Function_Name        : SecOC_GetTxFreshnessTruncData *
 * Function_Index       : 8.5.4 [SWS_SecOC_91003]       *
 * Function_File        : SWS of SecOC                  *
 * Function_Descripton  : This interface is used by the *
 * SecOC to obtain the current freshness value          *
 * The interface function provides also the truncated   *
 * freshness transmitted in the secured I-PDU.          *
 *******************************************************/
Std_ReturnType SecOC_GetTxFreshnessTruncData (
uint16 SecOCFreshnessValueID,
uint8* SecOCFreshnessValue,
uint32* SecOCFreshnessValueLength,
uint8* SecOCTruncatedFreshnessValue,
uint32* SecOCTruncatedFreshnessValueLength
);


#endif
