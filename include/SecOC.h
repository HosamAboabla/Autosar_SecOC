#ifndef INCLUDE_SECOC_H_
#define INCLUDE_SECOC_H_

#include "SecOC_Cfg.h"
#include "SecOC_Types.h"

void SecOC_MainFunctionTx ( void );


Std_ReturnType SecOC_IfTransmit(
    PduIdType                  TxPduId,
    const PduInfoType*         PduInfoPtr
);

void SecOC_TxConfirmation (PduIdType TxPduId,Std_ReturnType result);



#endif
