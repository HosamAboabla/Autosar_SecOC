#include "Pdur_CanTP.h"
#include "SecOC.h"
#include "SecOC_Debug.h"

BufReq_ReturnType PduR_CanTpCopyTxData (PduIdType id,const PduInfoType* info,const RetryInfoType* retry,
PduLengthType* availableDataPtr)
{
    #ifdef SECOC_DEBUG
        printf("######## in PduR_CanTpCopyTxData ########\n");
    #endif
   /* SWS_CanTp_00086 */
   return SecOC_CopyTxData(id, info, retry, availableDataPtr);
}



void PduR_CanTpTxConfirmation(PduIdType TxPduId, Std_ReturnType result)
{
    #ifdef SECOC_DEBUG
        printf("######## in PduR_CanTpTxConfirmation ########\n");
    #endif
    /* SWS_PduR_00301 */
    SecOC_TpTxConfirmation(TxPduId, result);
}

BufReq_ReturnType PduR_CanTpCopyRxData (PduIdType id,const PduInfoType* info,PduLengthType* bufferSizePtr)
{
    #ifdef SECOC_DEBUG
        printf("######## in PduR_CanTpCopyRxData ########\n");
    #endif
    /* SWS_PduR_00428 */
    return SecOC_CopyRxData(id, info, bufferSizePtr);
}

BufReq_ReturnType PduR_CanTpStartOfReception(PduIdType id, const PduInfoType* info, PduLengthType TpSduLength, PduLengthType* bufferSizePtr)
{
    #ifdef SECOC_DEBUG
        printf("######## in PduR_CanTpStartOfReception ########\n");
    #endif
    /* SWS_PduR_00549 */
    return SecOC_StartOfReception(id, info, TpSduLength, bufferSizePtr);
}

void PduR_CanTpRxIndication (PduIdType id, Std_ReturnType result)
{
    #ifdef SECOC_DEBUG
        printf("######## in PduR_CanTpRxIndication ########\n");
    #endif
    /* SWS_PduR_00207 */
    SecOC_TpRxIndication(id, result);
}