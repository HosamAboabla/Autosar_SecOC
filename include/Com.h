#ifndef INCLUDE_COM_H_
#define INCLUDE_COM_H_

#include "Std_Types.h"
#include "ComStack_Types.h"

void Com_TxConfirmation(PduIdType TxPduId, Std_ReturnType result);

void Com_RxIndication(PduIdType RxPduId, const PduInfoType* PduInfoPtr);

#endif