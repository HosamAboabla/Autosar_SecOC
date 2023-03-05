#ifndef INCLUDE_CANT_TP_H_
#define INCLUDE_CANT_TP_H_

#include "Std_Types.h"
#include "ComStack_Types.h"


/*******************************************************\
 *          * Function Info *                           *
 *                                                      *
 * Function_Name        : CanTp_MainFunction            *
 * Function_Index       : 8.3.9 [CANTP213]              *
 * Function_File        : SWS of CanTp                  *
 * Function_Descripton  : The main function for         *
 * scheduling the CAN TP                                *
 *******************************************************/
void CanTp_MainFunction(void);


/*******************************************************\
 *          * Function Info *                           *
 *                                                      *
 * Function_Name        : CanTp_Transmit                *
 * Function_Index       : 8.3.4 [CANTP212]              *
 * Function_File        : SWS of CanTp                  *
 * Function_Descripton  : This service is used to       * 
 * request the transfer of segmented data               *
 *******************************************************/
Std_ReturnType CanTp_Transmit(PduIdType CanTpTxSduId, const PduInfoType* CanTpTxInfoPtr);



void CanTp_TxConfirmation(PduIdType TxPduId, Std_ReturnType result);

#endif