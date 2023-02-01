#ifndef INCLUDE_SECOC_H_
#define INCLUDE_SECOC_H_

#include "SecOC_Cfg.h"
#include "SecOC_Types.h"
#include "SecOC_Lcfg.h"
#include "SchM_SecOC.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "Det.h"

Std_ReturnType SecOC_IfTransmit(
    PduIdType                  TxPduId,
    const PduInfoType*         PduInfoPtr
);



void SecOC_test();

void SecOC_TxConfirmation(PduIdType TxPduId, Std_ReturnType result);

void SecOC_Init(const SecOC_ConfigType *config);



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
#define SECOC_START_SEC_GetTxFreshness_CODE

Std_ReturnType SecOC_GetTxFreshness(uint16 SecOCFreshnessValueID, uint8* SecOCFreshnessValue,
uint32* SecOCFreshnessValueLength);

#define SECOC_END_SEC_GetTxFreshness_CODE



void SecOC_GetVersionInfo(Std_VersionInfoType* versioninfo);
//void memcpy(versionInfo, &_SecOC_VersionInfo, sizeof(Std_VersionInfoType));





/****************************************************
 *          * Function Info *                           *
 *                                                      *
 * Function_Name        : SecOC_SPduTxConfirmation      *
 * Function_Index       : 8.5.5 [SWS_SecOC_91005]       *
 * Function_File        : SWS of secOC                  *
 * Function_Descripton  : This interface is used by     *
 * SecOC to indicate that the Secured I-PDU has been    *
 * initiated for transmission                           *
 ***************************************************/
void SecOc_SPduTxConfirmation(uint16 SecOCFreshnessValueID);




/*******************************************************
 *          * Function Info *                           *
 *                                                      *
 * Function_Name        : SecOC_CopyTxData              *
 * Function_Index       : 8.4.7 [SWS_SecOC_00129]       *
 * Function_File        : SWS of SecOC                  *
 * Function_Descripton  : This function is called to    *
 * acquire the transmit data of an I-PDU segment (N-PDU)*
 * Each call to this function provides the next part of *
 * the I-PDU data unless retry->Tp DataState is         *
 * TP_DATARETRY. In this case the function restarts to  *
 * copy the data beginning at the offset from the       *
 * current position indicated by retry->TxTpDataCnt.    *
 * The size of the remaining data is written to the     *
 * position indicated by availableDataPtr.              *
 *******************************************************/
BufReq_ReturnType SecOC_CopyTxData (
    PduIdType id,
    const PduInfoType* info,
    const RetryInfoType* retry,
    PduLengthType* availableDataPtr
);


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
Std_ReturnType SecOC_GetTxFreshnessTruncData(
    uint16 SecOCFreshnessValueID,
    uint8* SecOCFreshnessValue,
    uint32* SecOCFreshnessValueLength,
    uint8* SecOCTruncatedFreshnessValue,
    uint32* SecOCTruncatedFreshnessValueLength
);

#define SECOC_E_UNINIT 					0x02

#endif  // INCLUDE_SECOC_H_
