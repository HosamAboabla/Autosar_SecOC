#ifndef INCLUDE_CANIF_H_
#define INCLUDE_CANIF_H_

#include "Std_Types.h"
#include "ComStack_Types.h"

#define SUCCESS     (1u)
#define FAILED      (0u)


#define CANIF_BUFFERLENGTH  ((uint32)100)

Std_ReturnType CanIf_Transmit(PduIdType TxPduId,const PduInfoType* PduInfoPtr);

#endif