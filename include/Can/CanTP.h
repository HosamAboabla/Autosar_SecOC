#ifndef INCLUDE_CANT_TP_H_
#define INCLUDE_CANT_TP_H_

#include "Std_Types.h"
#include "ComStack_Types.h"

#define SUCCESS     (1u)
#define FAILED      (0u)
#define TP_TRANSMISSION_STATUS SUCCESS

#define CANTP_BUFFER_SIZE       255
#define BUS_LENGTH              8

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


/*******************************************************\
 *          * Function Info *                           *
 *                                                      *
 * Function_Name        : CanTp_RxIndication            *
 * Function_Index       : 8.4.1  [SWS_CanTp_00214]      *
 * Function_File        : SWS of CanTp                  *
 * Function_Descripton  : ndication of a received PDU   *
 * from a lower layer communication interface module.   *
 *******************************************************/
void CanTp_RxIndication (PduIdType RxPduId, const PduInfoType* PduInfoPtr);


void CanTp_TxConfirmation(PduIdType TxPduId, Std_ReturnType result);

void CanTP_MainFunctionRx(void);

#endif /*INCLUDE_CANTP_H_*/
