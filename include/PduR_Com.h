/******************************************************************************
 * Module      : PduR                                                         *
 * File Name   : PduR_Com.h                                                   *
 * Description : Header file of APIs provided by PduR to Com                  *
 * Created on  : December 1, 2022                                             *
 ******************************************************************************/

#ifndef INCLUDE_PDUR_COM_H_
#define INCLUDE_PDUR_COM_H_

#include "Std_Types.h"
#include "ComStack_Types.h"


/****************************************************
 *          * Function Info *                       *
 *                                                  *
 * Function_Name        : CanIf_Transmit            *
 * Function_Index       : 8.3.6 [SWS_CANIF_00005]   *
 * Function_File        : SWS of COM                *
 * Function_Descripton  : Transmits message to PDuR *
 *                                                  *
 ***************************************************/
Std_ReturnType PduR_ComTransmit(PduIdType PduID, const PduInfoType *PduInfo);


#endif