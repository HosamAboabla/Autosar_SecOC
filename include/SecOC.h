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


// Derived configuration
#define SECOC_AUTHENTICATOR_MAX_LENGTH                              ((uint8)32)
#define SECOC_FRESHNESS_MAX_LENGTH                                  ((uint8)16)
#define SECOC_AUTHPDU_MAX_LENGTH                                    ((uint32)4)
#define SECOC_DATA_TO_AUTHENTICATOR_LENGTH                          (sizeof(PduIdType) + SECOC_AUTHPDU_MAX_LENGTH + SECOC_FRESHNESS_MAX_LENGTH)
#define SECOC_SECPDU_MAX_LENGTH                                     (SECOC_AUTHPDU_HEADERLENGTH + SECOC_AUTHPDU_MAX_LENGTH + SECOC_FRESHNESS_MAX_LENGTH / 8 + SECOC_AUTHENTICATOR_MAX_LENGTH / 8)

Std_ReturnType SecOC_IfTransmit(
    PduIdType                  TxPduId,
    const PduInfoType*         PduInfoPtr
);



void SecOC_test();

void SecOC_TxConfirmation(PduIdType TxPduId, Std_ReturnType result);

void SecOC_Init(const SecOC_ConfigType *config);


/****************************************************
 *          * Function Info *                           *
 *                                                      *
 * Function_Name        : SecOC_RxIndication            *
 * Function_Index       : 8.4.1 [SWS_SecOC_00124]       *
 * Function_File        : SWS of secOC                  *
 * Function_Descripton  : Indication of a received PDU  *
 * from a lower layer communication interface module.   *
 ***************************************************/
void SecOC_RxIndication (PduIdType RxPduId, const PduInfoType* PduInfoPtr);

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

Std_ReturnType construct_RX_DataToAuthenticator(PduIdType TxPduId, PduInfoType* secPdu,SecOC_RxPduProcessingType *SecOCRxPduProcessing, uint8 *DataToAuth, uint32 *DataToAuthLen);

/*******************************************************
 *          * Function Info *                           *
 *                                                      *
 * Function_Name        : verify                        *
 * Function_Index       :  SecOC internal               *
 * Function_File        : SWS of SecOC                  *
 * Function_Descripton  : Verification of I-PDUs        *
 *******************************************************/

Std_ReturnType verify(PduIdType TxPduId, PduInfoType* SecPdu, SecOC_RxPduProcessingType *SecOCRxPduProcessing, SecOC_VerificationResultType *verification_result);

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


/*******************************************************
 *          * Function Info *                           *
 *                                                      *
 * Function_Name        : SecOC_TpTxConfirmation        *
 * Function_Index       : 8.4.4                         *
 * Function_File        : SWS of SecOC                  *
 * Function_Descripton  : This function is called after *
 * the I-PDU has been transmitted on its network, the   *
 * result indicates whether the transmission was        *
 * successful or not.                                   *
 *******************************************************/
void SecOC_TpTxConfirmation(PduIdType id,Std_ReturnType result);



#define SECOC_E_UNINIT 					0x02

#endif  // INCLUDE_SECOC_H_
