#include "CanTp.h"
#include "SecOC_Cfg.h"

#ifdef LINUX
#include "ethernet.h"
#endif
#include "PduR_CanIf.h"

static PduInfoType* CanTp_Buffer[CANTP_BUFFERLENGTH];
Std_ReturnType CanTp_Transmit(PduIdType TxPduId,const PduInfoType* PduInfoPtr)
{
    Std_ReturnType result;

    /*Validate input parameters*/
    if (TxPduId < SECOC_BUFFERLENGTH) 
    {
        /*What we need to do here is segmentation,
         * PduInfoType has the sdu data length as uint8
         * //          haas the metadata length as uint8
         *
         * the SDU data is what we need to make segmentation for
         * 
         * the problem here is that there is no datatype less than uint8 to segmenet to
         * 
         * also the segmentatino process requires first frame, stop frame, data .. how will it be stubbed !!
         * 
         * 
         * */
    } 
    else 
    {
        return E_NOT_OK;
    }
    
    #ifdef LINUX
    result = ethernet_send(PduInfoPtr->SduDataPtr , PduInfoPtr->SduLength);
    #endif

    PduR_CanTpTxConfirmation(TxPduId , result);
}