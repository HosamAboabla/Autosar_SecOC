#include "CanTp.h"
#include "SecOC_Cfg.h"

#ifdef LINUX
#include "ethernet.h"
#endif
#include "PduR_CanTp.h"

Std_ReturnType CanTp_Transmit(PduIdType TxPduId,const PduInfoType* PduInfoPtr)
{
    Std_ReturnType result;
    
    #ifdef LINUX
    result = ethernet_send(PduInfoPtr->SduDataPtr , PduInfoPtr->SduLength);
    #endif

    // PduR_CanTpTxConfirmation(TxPduId , result); /*should be called at the end of Hussein's Function*/

    // /*Also the code below should be called after Hussein's Function
    // * It may be with every transmission of the segmented data or when the transmission finishes
    // */
    // if(TP_TRANSMISSION_STATUS)
    // {
    //     return E_OK;
    // }
    // else
    // {
    //     return E_NOT_OK;
    // }
}