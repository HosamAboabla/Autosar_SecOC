#ifndef INCLUDE_SOAD_H_
#define INCLUDE_SOAD_H_

#include "Std_Types.h"
#include "ComStack_Types.h"

#define SOAD_BUFFERLENGTH  ((uint32)100)

Std_ReturnType SoAd_IfTransmit (
PduIdType TxPduId,
const PduInfoType* PduInfoPtr
);

Std_ReturnType SoAd_TpTransmit (
PduIdType TxPduId,
const PduInfoType* PduInfoPtr
);

#endif  // INCLUDE_SOAD_H_