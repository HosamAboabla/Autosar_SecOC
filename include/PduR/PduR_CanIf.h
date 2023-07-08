
#ifndef INCLUDE_PDUR_CANIF_H_
#define INCLUDE_PDUR_CANIF_H_

/********************************************************************************************************/
/************************************************INCULDES************************************************/
/********************************************************************************************************/

#include"Std_Types.h"
#include"ComStack_Types.h"


/********************************************************************************************************/
/*****************************************FunctionPrototype**********************************************/
/********************************************************************************************************/

/*******************************************************
 *          * Function Info *                           *
 *                                                      *
 * Function_Name        : PduR_<User:Lo>TxConfirmation  *
 * Function_Index       : 8.3.3.2                       *
 * Function_File        : SWS of PduR                   *
 * Function_Descripton  : The lower layer communication *
 * interface module confirms the transmission of a PDU, *
 * or the failure to transmit a PDU                     *
 *******************************************************/
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