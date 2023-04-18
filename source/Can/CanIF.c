/********************************************************************************************************/
/************************************************INCULDES************************************************/
/********************************************************************************************************/

#include "CanIF.h"
// #include "OSconfig.h"
#include "SecOC.h"
#include "SecOC_Debug.h"

#ifdef LINUX
#include "ethernet.h"
#endif
#include "PduR_CanIf.h"


/********************************************************************************************************/
/******************************************GlobalVaribles************************************************/
/********************************************************************************************************/

extern const SecOC_TxPduProcessingType     *SecOCTxPduProcessing;
extern communicate_Types TxComTypes[SECOC_NUM_OF_RX_PDU_PROCESSING];


/********************************************************************************************************/
/********************************************Functions***************************************************/
/********************************************************************************************************/

/****************************************************
 *          * Function Info *                       *
 *                                                  *
 * Function_Name        : CanIf_Transmit            *
 * Function_Index       : 8.3.6 [SWS_CANIF_00005]   *
 * Function_File        : SWS of CAN Interface      *
 * Function_Descripton  : Requests transmission     *
 *              of a PDU                            *
 ***************************************************/

Std_ReturnType CanIf_Transmit(PduIdType TxPduId,const PduInfoType* PduInfoPtr)
{
    #ifdef CANIF_DEBUG
        printf("######## in CanIf_Transmit \n");
    #endif

    Std_ReturnType result = E_OK;

    #ifdef CANIF_DEBUG
        printf("Secure PDU -->\n");
            for(int i = 0; i < PduInfoPtr->SduLength; i++)
                printf("%d ", PduInfoPtr->SduDataPtr[i]);
        printf("\n");
    #endif

    #ifdef LINUX
    result = ethernet_send(TxPduId, PduInfoPtr->SduDataPtr , PduInfoPtr->SduLength);
    #endif


    if (TxComTypes[TxPduId] == CANTP)
    {
        CanTp_TxConfirmation(TxPduId, result);
    }
    else if (TxComTypes[TxPduId] == CANIF)
    {
        PduR_CanIfTxConfirmation(TxPduId , result);
    }


    return result;
}