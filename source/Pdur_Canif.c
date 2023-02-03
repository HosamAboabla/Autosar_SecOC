#include "PduR_CanIf.h"
#include "SecOC.h"

void PduR_CanIfTxConfirmation(PduIdType TxPduId, Std_ReturnType result)
{
	SecOC_TxConfirmation( TxPduId,  result );
}


void PduR_CanIfRxIndication(PduIdType RxPduId, const PduInfoType* PduInfoPtr)
{
	SecOC_RxIndication(RxPduId, PduInfoPtr);
}