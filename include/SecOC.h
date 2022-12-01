#ifndef INCLUDE_SECOC_H_
#define INCLUDE_SECOC_H_

#include "SecOC_Cfg.h"

Std_ReturnType CanIf_Transmit(PduIdType,const PduInfoType*);

void SecOC_TxConfirmation (PduIdType,Std_ReturnType);

#endif
