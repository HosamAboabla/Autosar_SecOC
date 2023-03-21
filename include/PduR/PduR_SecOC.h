#ifndef INCLUDE_PDUR_SECOC_H_
#define INCLUDE_PDUR_SECOC_H_

#include "Std_Types.h"
#include "ComStack_Types.h"


/****************************************************
 *          * Function Info *                       *
 *                                                  *
 * Function_Name        : PduR_SecOCTransmit        *
 * Function_Index       : 8.3.2.1 [SWS_PduR_00406]  *
 * Function_File        : SWS of Pdur Interface     *
 * Function_Descripton  : Requests transmission     *
 *              of a PDU                            *
 ***************************************************/
Std_ReturnType PduR_SecOCTransmit(PduIdType PduId, const PduInfoType* PduInfo);



void PduR_SecOCIfTxConfirmation(PduIdType TxPduId, Std_ReturnType result);

void PduR_SecOCIfRxIndication(PduIdType RxPduId, const PduInfoType* PduInfoPtr);

void PduR_SecOCTpTxConfirmation(PduIdType TxPduId, Std_ReturnType result);


#endif