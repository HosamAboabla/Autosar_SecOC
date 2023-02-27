#ifndef INCLUDE_PDUR_CANTP_H_
#define INCLUDE_PDUR_CANTP_H_

#include"Std_Types.h"
#include"ComStack_Types.h"

/****************************************************
 *          * Function Info *                       *
 *                                                  *
 * Function_Name        : PduR_CanTpCopyTxData      *
 * Function_Index       : 8.3.4.4 [SWS_PduR_00406]  *
 * Function_File        : SWS of Pdur Interface     *
 * Function_Descripton  : This function is called to*
 *  acquire the transmit data of an I-PDU segment   *
 * (N-PDU). Each call to this function provides the *
 * next part of the I-PDU data unless               *
 * retry->TpDataState is TP_DATARETRY. In this case *
 * the function restarts to copy the data beginning *
 * at the offset from the current position indicated*
 * by retry->TxTpDataCnt. The size of the remaining *
 * data is written to the position indicated by     *
 * availableDataPtr.                                *
 ***************************************************/
BufReq_ReturnType PduR_CanTpCopyTxData (PduIdType id,const PduInfoType* info,const RetryInfoType* retry,
PduLengthType* availableDataPtr);

void PduR_CanTpTxConfirmation(PduIdType TxPduId, Std_ReturnType result);

/*****************************************************
 *          * Function Info *                        *
 *                                                   *
 * Function_Name        : PduR_CanTpRxIndication     *
 * Function_Index       : 8.3.4.2 [SWS_PduR_00375]   *
 * Function_File        : SWS of Pdur                *
 * Function_Descripton  : Called after an I-PDU has  *
 * been received via the TP API, the result indicates* 
 * whether the transmission was successful or not    *
 ****************************************************/
void PduR_CanTpRxIndication (PduIdType id, Std_ReturnType result);

#endif /* INCLUDE_PDUR_CANTP_H_ */