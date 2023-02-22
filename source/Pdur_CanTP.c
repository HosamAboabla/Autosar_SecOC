#include "Pdur_CanTP.h"
#include "SecOC.h"

BufReq_ReturnType PduR_CanTpCopyTxData (PduIdType id,const PduInfoType* info,const RetryInfoType* retry,
PduLengthType* availableDataPtr)
{
   /* SWS_CanTp_00086 */
   return SecOC_CopyTxData(id, info, retry, availableDataPtr);
}



void PduR_CanTpTxConfirmation(PduIdType TxPduId, Std_ReturnType result)
{
    // forward result to SecOC
    SecOC_TpTxConfirmation(TxPduId, result);
}

BufReq_ReturnType PduR_CanTpCopyRxData (PduIdType id,const PduInfoType* info,PduLengthType* bufferSizePtr)
{
    // SWS_PduR_00428 
    //SecOC_CopyRxData(id, info, bufferSizePtr);
}