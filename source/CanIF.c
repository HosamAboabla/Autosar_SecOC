#include "CanIF.h"
// #include "OSconfig.h"
#include "SecOC.h"
#include "SecOC_Debug.h"

#ifdef LINUX
#include "ethernet.h"
#endif
#include "PduR_CanIf.h"



extern const SecOC_TxPduProcessingType     *SecOCTxPduProcessing;



/****************************************************
 *          * Function Info *                       *
 *                                                  *
 * Function_Name        : CanIf_Transmit            *
 * Function_Index       : 8.3.6 [SWS_CANIF_00005]   *
 * Function_File        : SWS of CAN Interface      *
 * Function_Descripton  : Requests transmission     *
 *              of a PDU                            *
 ***************************************************/
PduInfoType* CanIF_Buffer[CANIF_BUFFERLENGTH];
Std_ReturnType CanIf_Transmit(PduIdType TxPduId,const PduInfoType* PduInfoPtr)
{
    #ifdef SECOC_DEBUG
        printf("######## in CanIf_Transmit ########\n");
    #endif
    // CanIF_Buffer[TxPduId] = PduInfoPtr; //copy_buffer
    Std_ReturnType result = E_OK;

    #ifdef SECOC_DEBUG
        printf("Secure PDU -->\n");
            for(int i = 0; i < PduInfoPtr->SduLength; i++)
                printf("%d ", PduInfoPtr->SduDataPtr[i]);
        printf("\n");
    #endif

    #ifdef LINUX
    result = ethernet_send(TxPduId, PduInfoPtr->SduDataPtr , PduInfoPtr->SduLength);
    #endif


    if (SecOCTxPduProcessing[TxPduId].SecOCTxAuthenticPduLayer->SecOCPduType == SECOC_TPPDU)
    {
        CanTp_TxConfirmation(TxPduId, result);
    }
    else if (SecOCTxPduProcessing[TxPduId].SecOCTxAuthenticPduLayer->SecOCPduType == SECOC_IFPDU)
    {
        PduR_CanIfTxConfirmation(TxPduId , result);
    }


    return result;
}