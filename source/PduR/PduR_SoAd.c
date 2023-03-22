#include "PduR_SoAd.h"
#include "SecOC.h"

BufReq_ReturnType PduR_SoAdTpCopyTxData (PduIdType id,const PduInfoType* info,const RetryInfoType* retry,
PduLengthType* availableDataPtr)
{
   /* SWS_CanTp_00086 */
   return SecOC_CopyTxData(id, info, retry, availableDataPtr);
}



void PduR_SoAdTpTxConfirmation(PduIdType TxPduId, Std_ReturnType result)
{
    // forward result to SecOC
    SecOC_TpTxConfirmation(TxPduId, result);
}


void PduR_SoAdIfTxConfirmation(PduIdType TxPduId, Std_ReturnType result)
{
	SecOC_TxConfirmation( TxPduId,  result );
}


void PduR_SoAdIfRxIndication(PduIdType RxPduId, const PduInfoType* PduInfoPtr)
{
	SecOC_RxIndication(RxPduId, PduInfoPtr);
}
