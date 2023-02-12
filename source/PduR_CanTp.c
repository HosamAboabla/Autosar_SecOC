#include "PduR_CanTp.h"
#include "SecOC.h"

void PduR_CanTpTxConfirmation(PduIdType TxPduId, Std_ReturnType result)
{
	SecOC_TpTxConfirmation( TxPduId,  result );
}
