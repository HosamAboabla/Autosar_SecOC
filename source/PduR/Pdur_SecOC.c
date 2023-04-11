#include "PduR_SecOC.h"
#include "Com.h"
#include "CanIF.h"
#include "CanTP.h"
#include "Dcm.h"
#include "SecOC_Debug.h"
#include "SecOC_Lcfg.h"

/****************************************************
 *          * Function Info *                       *
 *                                                  *
 * Function_Name        : PduR_SecOCTransmit        *
 * Function_Index       : 8.3.2.1 [SWS_PduR_00406]  *
 * Function_File        : SWS of Pdur Interface     *
 * Function_Descripton  : Requests transmission     *
 *              of a PDU                            *
 ***************************************************/


extern communicate_Types TxComTypes[SECOC_NUM_OF_RX_PDU_PROCESSING];

Std_ReturnType PduR_SecOCTransmit(PduIdType TxPduId, const PduInfoType* PduInfoPtr)
{
   #ifdef PDUR_DEBUG
        printf("######## in PduR_SecOCTransmit for id %d \n", TxPduId);
    #endif
   if(TxComTypes[TxPduId] == CANIF)
   {
      #ifdef PDUR_DEBUG
        printf("sending CANIF \n");
      #endif
      return CanIf_Transmit(TxPduId,PduInfoPtr);
   }
   else if (TxComTypes[TxPduId] == FRIF)
   {
      /* return FrIf_Transmit(TxPduId, PduInfoPtr);*/
   }   
   else if(TxComTypes[TxPduId] == CANTP)
   {
      #ifdef PDUR_DEBUG
        printf("sending CANTP \n");
      #endif
      return CanTp_Transmit(TxPduId, PduInfoPtr);
   }
   else
   {

   }
    return E_NOT_OK;
}


void PduR_SecOCIfTxConfirmation(PduIdType TxPduId, Std_ReturnType result)
{
   #ifdef PDUR_DEBUG
        printf("######## in PduR_SecOCIfTxConfirmation \n");
    #endif
	Com_TxConfirmation(TxPduId, result);
}



void PduR_SecOCIfRxIndication(PduIdType RxPduId, const PduInfoType* PduInfoPtr)
{
   #ifdef PDUR_DEBUG
        printf("######## in PduR_SecOCIfRxIndication \n");
    #endif
   Com_RxIndication(RxPduId, PduInfoPtr);
}


void PduR_SecOCTpTxConfirmation(PduIdType TxPduId, Std_ReturnType result)
{
   #ifdef PDUR_DEBUG
        printf("######## in PduR_SecOCTpTxConfirmation \n");
    #endif
	/* Com_TxConfirmation(TxPduId, result);*/
   Dcm_TpTxConfirmation(TxPduId, result);
}