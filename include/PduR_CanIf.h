
#ifndef INCLUDE_PDUR_CANIF_H_
#define INCLUDE_PDUR_CANIF_H_

#include"Std_Types.h"
#include"ComStack_Types.h"


void PduR_CanIfTxConfirmation(PduIdType TxPduId, Std_ReturnType result);



/*******************************************************
 *          * Function Info *                           *
 *                                                      *
 * Function_Name        : PduR_<Lo>RxIndication         *
 * Function_Index       : 8.5.4.1                       *
 * Function_File        : SWS of PduR                   *
 * Function_Descripton  : Indication of a received      *
 * I-PDU from a lower layer communication module.       *
 *******************************************************/
void PduR_CanIfRxIndication(PduIdType RxPduId, const PduInfoType* PduInfoPtr);

#endif