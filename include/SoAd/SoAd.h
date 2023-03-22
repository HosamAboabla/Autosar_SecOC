#ifndef INCLUDE_SOAD_H_
#define INCLUDE_SOAD_H_

#include "Std_Types.h"
#include "ComStack_Types.h"

#define SOAD_BUFFERLENGTH  ((uint32)100)
#define BUS_LENGTH              8

Std_ReturnType SoAd_IfTransmit (
PduIdType TxPduId,
const PduInfoType* PduInfoPtr
);

void PduR_SoAdIfRxIndication(PduIdType RxPduId, const PduInfoType* PduInfoPtr);


Std_ReturnType SoAd_TpTransmit (
PduIdType TxPduId,
const PduInfoType* PduInfoPtr
);

BufReq_ReturnType PduR_SoAdTpCopyTxData (PduIdType id,const PduInfoType* info,const RetryInfoType* retry,
PduLengthType* availableDataPtr);

void PduR_SoAdTpTxConfirmation(PduIdType TxPduId, Std_ReturnType result);

BufReq_ReturnType PduR_SoAdTpCopyRxData (PduIdType id,const PduInfoType* info,PduLengthType* bufferSizePtr);
BufReq_ReturnType PduR_SoAdStartOfReception(PduIdType id, const PduInfoType* info, PduLengthType TpSduLength, PduLengthType* bufferSizePtr);
void PduR_SoAdTpRxIndication (PduIdType id, Std_ReturnType result);


void SoAd_TxConfirmation(PduIdType TxPduId, Std_ReturnType result);
void SoAd_MainFunctionRx(void);
#endif  // INCLUDE_SOAD_H_