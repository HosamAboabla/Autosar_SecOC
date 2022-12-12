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





void SecOC_TxConfirmation(PduIdType TxPduId, Std_ReturnType result);

void SecOC_Init(const SecOC_ConfigType *config);



/*******************************************************
 *          * Function Info *                           *
 *                                                      *
 * Function_Name        : SecOC_GetRxFreshness          *
 * Function_Index       : 8.5.1 [SWS_SecOC_91007]       *
 * Function_File        : SWS of SecOC                  *
 * Function_Descripton  : This interface is used by the *
 * SecOC to obtain the current freshness value          *
 *******************************************************/

Std_ReturnType SecOC_GetRxFreshness(uint16 SecOCFreshnessValueID, const uint8* SecOCTruncatedFreshnessValue,
uint32 SecOCTruncatedFreshnessValueLength, uint16 SecOCAuthVerifyAttempts, uint8* SecOCFreshnessValue,
uint32* SecOCFreshnessValueLength);

/*******************************************************
 *          * Function Info *                           *
 *                                                      *
 * Function_Name        : SecOC_GetRxFreshnessAuthData  *
 * Function_Index       : 8.5.2 [SWS_SecOC_91006]       *
 * Function_File        : SWS of SecOC                  *
 * Function_Descripton  : This interface is used by the *
 * SecOC to obtain the current freshness value          *
 *******************************************************/

Std_ReturnType SecOC_GetRxFreshnessAuthData(uint16 SecOCFreshnessValueID , const uint8* SecOCTruncatedFreshnessValue ,
uint32 SecOCTruncatedFreshnessValueLength , const uint8* SecOCAuthDataFreshnessValue,
 uint16 SecOCAuthDataFreshnessValueLength , uint16 SecOCAuthVerifyAttempts,
 uint8* SecOCFreshnessValue, uint32* SecOCFreshnessValueLength);
 
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


/*******************************************************
 *          * Function Info *                           *
 *                                                      *
 * Function_Name        : verify                        *
 * Function_Index       :  SecOC internal               *
 * Function_File        : SWS of SecOC                  *
 * Function_Descripton  : Verification of I-PDUs        *
 *******************************************************/

Std_ReturnType verify(PduIdType RxPduId, PduInfoType* SPDU, PduInfoType* A_PDU, SecOC_RxPduProcessingType SecOCRxPduProcessing);

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
