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
    
    #ifdef LINUX
    result = ethernet_send(PduInfoPtr->SduDataPtr , PduInfoPtr->SduLength);
    #endif

    PduR_CanTpTxConfirmation(TxPduId , result);
}