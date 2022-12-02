#ifndef INCLUDE_SECOC_H_
#define INCLUDE_SECOC_H_

#include "SecOC_Cfg.h"

void PduR_CanIfTxConfirmation(PduIdType TxPduId, Std_ReturnType result);

void PduR_SecOCIfTxConfirmation(PduIdType TxPduId, Std_ReturnType result);

void Com_TxConfirmation(PduIdType TxPduId, Std_ReturnType result);

#endif
