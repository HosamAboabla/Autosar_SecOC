#ifndef INCLUDE_SECOC_H_
#define INCLUDE_SECOC_H_

#include "SecOC_Cfg.h"


Std_ReturnType SecOC_IfTransmit(
    Pdu_IdType                  TxPduId,
    const Pdu_InfoType*         PduInfoPtr
);

void SecOC_TxConfirmation (PduIdType TxPduId,Std_ReturnType result);


#endif
