#include "Pdur_CanTP.h"
#include "SecOC.h"

void PduR_CanTpTxConfirmation(PduIdType TxPduId, Std_ReturnType result)
{
    // forward result to SecOC
    SecOC_TpTxConfirmation(TxPduId, result);
}
