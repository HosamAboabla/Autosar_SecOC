/********************************************************************************************************/
/************************************************INCULDES************************************************/
/********************************************************************************************************/

#include "PduR_SecOC.h"
#include "Com.h"
#include "CanIF.h"
#include "CanTP.h"
#include "Dcm.h"
#include "SoAd.h"
#include "SecOC_Debug.h"
#include "SecOC_Lcfg.h"


/********************************************************************************************************/
/******************************************GlobalVaribles************************************************/
/********************************************************************************************************/

extern SecOC_PduCollection PdusCollections[];


/********************************************************************************************************/
/********************************************Functions***************************************************/
/********************************************************************************************************/

/****************************************************
 *          * Function Info *                       *
 *                                                  *
 * Function_Name        : PduR_SecOCTransmit        *
 * Function_Index       : 8.3.2.1 [SWS_PduR_00406]  *
 * Function_File        : SWS of Pdur Interface     *
 * Function_Descripton  : Requests transmission     *
 *              of a PDU                            *
 ***************************************************/


Std_ReturnType PduR_SecOCTransmit(PduIdType TxPduId, const PduInfoType* PduInfoPtr)
{
   #ifdef PDUR_DEBUG
        printf("######## in PduR_SecOCTransmit for id %d \n", TxPduId);
    #endif


   switch (PdusCollections[TxPduId].Type)
    {
    case SECOC_SECURED_PDU_CANIF:
         #ifdef PDUR_DEBUG
            printf("sending CANIF \n");
         #endif
         return CanIf_Transmit(TxPduId,PduInfoPtr);
         break;
    case SECOC_SECURED_PDU_CANTP:
         #ifdef PDUR_DEBUG
            printf("sending CANTP \n");
         #endif
         return CanTp_Transmit(TxPduId, PduInfoPtr);
        break;
    case SECOC_SECURED_PDU_SOADTP:
        #ifdef PDUR_DEBUG
            printf("sending SOADTP \n");
        #endif
        return SoAd_TpTransmit(TxPduId, PduInfoPtr); 
        break;
    case SECOC_SECURED_PDU_SOADIF:
        #ifdef PDUR_DEBUG
            printf("sending SOADIF \n");
        #endif
        return SoAd_IfTransmit(TxPduId, PduInfoPtr);
        break;
    case SECOC_AUTH_COLLECTON_PDU:
        #ifdef PDUR_DEBUG
            printf("sending CANIF - Pdu collection - Auth \n");
        #endif
         return CanIf_Transmit(TxPduId,PduInfoPtr);
        break;
    case SECOC_CRYPTO_COLLECTON_PDU:
        #ifdef PDUR_DEBUG
            printf("sending CANIF - Pdu collection - Crypto \n");
        #endif
         return CanIf_Transmit(TxPduId,PduInfoPtr);
        break;
    
    default:
        #ifdef PDUR_DEBUG
            printf("This is no type like it for ID : %d  type : %d \n", TxPduId, PdusCollections[TxPduId].Type);
        #endif
        return E_NOT_OK;
        break;
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