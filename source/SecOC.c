#include "SecOC_Lcfg.h"
#include "SecOC_PBcfg.h"
#include "SecOC_Cbk.h"
#include "Det.h"
#include "Rte_SecOC.h"
#include "SecOC.h"


void PduR_CanIfTxConfirmation(PduIdType TxPduId, Std_ReturnType result)
{
	SecOC_TxConfirmation( TxPduId,  result );
}

void PduR_SecOCIfTxConfirmation(PduIdType TxPduId, Std_ReturnType result)
{
	Com_TxConfirmation(TxPduId, result);
}

