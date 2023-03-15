#include "PduR_CanIf.h"
#include "SecOC.h"
#include "SecOC_Debug.h"

void PduR_CanIfTxConfirmation(PduIdType TxPduId, Std_ReturnType result)
{
	#ifdef PDUR_DEBUG
        printf("######## in PduR_CanIfTxConfirmation \n");
    #endif
	SecOC_TxConfirmation( TxPduId,  result );
}


void PduR_CanIfRxIndication(PduIdType RxPduId, const PduInfoType* PduInfoPtr)
{
	#ifdef PDUR_DEBUG
        printf("######## in PduR_CanIfRxIndication\n");
    #endif
	SecOC_RxIndication(RxPduId, PduInfoPtr);
}