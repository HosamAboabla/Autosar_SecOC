#ifndef INCLUDE_CANT_TP_H_
#define INCLUDE_CANT_TP_H_

/********************************************************************************************************/
/************************************************INCULDES************************************************/
/********************************************************************************************************/

#include "Std_Types.h"
#include "ComStack_Types.h"


/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/

#define SUCCESS     (1u)
#define FAILED      (0u)
#define TP_TRANSMISSION_STATUS SUCCESS

#define CANTP_BUFFER_SIZE       255
#define BUS_LENGTH              8

/********************************************************************************************************/
/*****************************************FunctionPrototype**********************************************/
/********************************************************************************************************/

/*******************************************************\
 *          * Function Info *                           *
 *                                                      *
 * Function_Name        : CanTp_MainFunctionTx          *
 * Function_Index       : 8.3.9 [CANTP213]              *
 * Function_File        : SWS of CanTp                  *
 * Function_Descripton  : The main function for         *
 * scheduling the CAN TP                                *
 *******************************************************/
void CanTp_MainFunctionTx(void);


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


/*******************************************************\
 *          * Function Info *                           *
 *                                                      *
 * Function_Name        : CanTp_TxConfirmation          *
 * Function_Index       : 8.4.2  [SWS_CanTp_00214]      *
 * Function_File        : SWS of CanTp                  *
 * Function_Descripton  : The lower layer communication *
 * interface module confirms the transmission of a PDU, *
 * or the failure to transmit a PDU.                    *
 *******************************************************/
void CanTp_TxConfirmation(PduIdType TxPduId, Std_ReturnType result);


/*******************************************************\
 *          * Function Info *                           *
 *                                                      *
 * Function_Name        : CanTp_MainFunctionRx          *
 * Function_Index       : 8.3.9 [CANTP213]              *
 * Function_File        : SWS of CanTp                  *
 * Function_Descripton  : The main function for         *
 * scheduling the CAN TP                                *
 *******************************************************/
void CanTp_MainFunctionRx(void);

#endif /*INCLUDE_CANTP_H_*/
