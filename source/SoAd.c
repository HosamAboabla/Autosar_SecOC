#include "SoAd.h"

#ifdef LINUX
#include "ethernet.h"
#endif
#include "PduR_SoAd.h"


PduInfoType* SoAd_Buffer[SOAD_BUFFERLENGTH];
Std_ReturnType SoAd_IfTransmit(PduIdType TxPduId,const PduInfoType* PduInfoPtr)
{
    // SoAd_Buffer[TxPduId] = PduInfoPtr; //copy_buffer
    Std_ReturnType result;

    
    #ifdef LINUX
    result = ethernet_send(PduInfoPtr->SduDataPtr , PduInfoPtr->SduLength);
    #endif

    PduR_SoAdIfTxConfirmation(TxPduId , result);
  
     return E_OK;

}

Std_ReturnType SoAd_TpTransmit(PduIdType TxPduId,const PduInfoType* PduInfoPtr)
{
    Std_ReturnType result;
    
    #ifdef LINUX
    result = ethernet_send(PduInfoPtr->SduDataPtr , PduInfoPtr->SduLength);
    #endif

    return result;
}