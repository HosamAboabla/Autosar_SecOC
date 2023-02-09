#include "PduR_SecOC.h"
#include "Com.h"
#include "CanIF.h"



/****************************************************
 *          * Function Info *                       *
 *                                                  *
 * Function_Name        : PduR_SecOCTransmit        *
 * Function_Index       : 8.3.2.1 [SWS_PduR_00406]  *
 * Function_File        : SWS of Pdur Interface     *
 * Function_Descripton  : Requests transmission     *
 *              of a PDU                            *
 ***************************************************/

/*FROM ROUTING TABLE WE KNOW PAGE 129*/
#define DIRECT_TRANSMISSION_MODE 0  /*e.g. CanIf*/
#define TRANSPORT_PROTOCOL_MODE 1   /*e.g. CanTp*/
#define TRIGGERED_TRANSMISSION_MODE 2  /*e.g. FlIf*/

Std_ReturnType PduR_SecOCTransmit(PduIdType TxPduId, const PduInfoType* PduInfoPtr)
{
   if(*(PduInfoPtr->MetaDataPtr) == DIRECT_TRANSMISSION_MODE)
   {
      return CanIf_Transmit(TxPduId,PduInfoPtr);
   }
   else if (*(PduInfoPtr->MetaDataPtr) == TRIGGERED_TRANSMISSION_MODE)
   {
      // return FrIf_Transmit(TxPduId, PduInfoPtr);
   }   
   else if(*(PduInfoPtr->MetaDataPtr) == TRANSPORT_PROTOCOL_MODE)
   {
      return CanTp_Transmit(TxPduId, PduInfoPtr);
   }
    return E_NOT_OK;
}


void PduR_SecOCIfTxConfirmation(PduIdType TxPduId, Std_ReturnType result)
{
	Com_TxConfirmation(TxPduId, result);
}
