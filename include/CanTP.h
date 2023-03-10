#ifndef INCLUDE_CANTP_H_
#define INCLUDE_CANTP_H_

#include "Std_Types.h"
#include "ComStack_Types.h"

#define SUCCESS     (1u)
#define FAILED      (0u)
#define TP_TRANSMISSION_STATUS SUCCESS

#define BUS_LENGTH       8
#define BUFFER_SIZE     200

/****************************************************
 *          * Function Info *                       *
 *                                                  *
 * Function_Name        : CanTp_Transmit            *
 * Function_Index       : 8.3.4 [SWS_CANTransportLayer]   *
 * Function_File        : SWS_CanTp_00212      *
 * Function_Descripton  : Requests transmission     *
 *              of a PDU                            *
 ***************************************************/
Std_ReturnType CanTp_Transmit(PduIdType TxPduId,const PduInfoType* PduInfoPtr);

void CanTP_MainFunctionRx(void);

#endif /*INCLUDE_CANTP_H_*/
