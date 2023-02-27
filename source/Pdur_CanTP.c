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
    /* SWS_PduR_00301 */
    SecOC_TpTxConfirmation(TxPduId, result);
}

BufReq_ReturnType PduR_CanTpCopyRxData (PduIdType id,const PduInfoType* info,PduLengthType* bufferSizePtr)
{
    /* SWS_PduR_00428 */
    SecOC_CopyRxData(id, info, bufferSizePtr);
}

BufReq_ReturnType PduR_CanTpStartOfReception(PduIdType id, const PduInfoType* info, PduLengthType TpSduLength, PduLengthType* bufferSizePtr)
{
    /* SWS_PduR_00549 */
    //SecOC_StartOfReception(id, info, TpSduLength, bufferSizePtr);
}