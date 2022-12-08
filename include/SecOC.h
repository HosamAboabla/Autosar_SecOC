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



/********************************************************
 *          * Function Info *                           *
 *                                                      *
 * Function_Name        : SecOC_GetTxFreshness          *
 * Function_Index       : 8.5.3 [SWS_SecOC_00126]       *
 * Function_File        : SWS of SecOC                  *
 * Function_Descripton  : This API returns the freshness*
 * value from the Most Significant Bits in the first    *
 * byte in the array (SecOCFreshnessValue),             *
 * in big endian format.                                *
 *******************************************************/

Std_ReturnType SecOC_GetTxFreshness (uint16 SecOCFreshnessValueID,uint8* SecOCFreshnessValue,uint32* SecOCFreshnessValueLength);


#endif
