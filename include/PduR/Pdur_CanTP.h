#ifndef INCLUDE_PDUR_CANTP_H_
#define INCLUDE_PDUR_CANTP_H_

/********************************************************************************************************/
/************************************************INCULDES************************************************/
/********************************************************************************************************/

#include"Std_Types.h"
#include"ComStack_Types.h"


/********************************************************************************************************/
/*****************************************FunctionPrototype**********************************************/
/********************************************************************************************************/

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

/****************************************************
 *          * Function Info *                       *
 *                                                  *
 * Function_Name        : PduR_CanTpTxConfirmation  *
 * Function_Index       : 8.3.4.5 [SWS_PduR_00381]  *
 * Function_File        : SWS of Pdur               *
 * Function_Descripton  : This function is called   *
 * after the I-PDU has been transmitted on its      *
 * network, the result indicates whether the        *
 * transmission was successful or not               *
 ***************************************************/
void PduR_CanTpTxConfirmation(PduIdType TxPduId, Std_ReturnType result);

/****************************************************
 *          * Function Info *                       *
 *                                                  *
 * Function_Name        : PduR_CanTpCopyTxData      *
 * Function_Index       : 8.3.4.1 [SWS_PduR_00512]  *
 * Function_File        : SWS of Pdur               *
 * Function_Descripton  : This function is called   *
 * to provide the received data of an I-PDU segment *
 * (N-PDU) to the upper layer. Each call to this    *
 * function provides the next part of the I-PDU     *
 * data. The size of the remaining buffer is written*
 *  to the position indicated by bufferSizePtr.     *
 ***************************************************/
BufReq_ReturnType PduR_CanTpCopyRxData (PduIdType id,const PduInfoType* info,PduLengthType* bufferSizePtr);

/****************************************************
 *          * Function Info *                       *
 *                                                  *
 * Function_Name        : PduR_CanTpStartOfReception*
 * Function_Index       : 8.3.4.3 [SWS_PduR_00507]  *
 * Function_File        : SWS of Pdur               *
 * Function_Descripton  : This function is called   * 
 * at the start of receiving an N-SDU. The N-SDU    *
 * might be fragmented intomultiple N-PDUs          *
 * (FF with one or more following CFs) or might     *
 * consist of a single N-PDU (SF).The service shall *
 * provide the currently available maximum buffer   *
 * size when invoked with TpSduLength equal to 0    *
 ***************************************************/
BufReq_ReturnType PduR_CanTpStartOfReception(PduIdType id, const PduInfoType* info, PduLengthType TpSduLength, PduLengthType* bufferSizePtr);

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