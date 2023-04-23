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
extern SecOC_PduCollection PdusCollections[];

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
    int delay = 50000000;
    while (delay--);
    switch (PdusCollections[TxPduId].Type)
    {
    case SECOC_SECURED_PDU_CANIF:
        PduR_CanIfTxConfirmation(TxPduId , result);
        break;
    case SECOC_SECURED_PDU_CANTP:
        CanTp_TxConfirmation(TxPduId, result);
        break;
    case SECOC_AUTH_COLLECTON_PDU:
        PduR_CanIfTxConfirmation(TxPduId , result);
        break;
    case SECOC_CRYPTO_COLLECTON_PDU:
        PduR_CanIfTxConfirmation(TxPduId , result);
        break;
    default:
        result = E_NOT_OK;
        break;
    }


    return result;
}