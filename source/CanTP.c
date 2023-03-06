#include "CanTP.h"
#include "SecOC_Cfg.h"

#ifdef LINUX
#include "ethernet.h"
#endif
#include "Pdur_CanTP.h"

Std_ReturnType CanTp_Transmit(PduIdType TxPduId,const PduInfoType* PduInfoPtr)
{
    Std_ReturnType result = E_OK;
    
    #ifdef LINUX
    result = ethernet_send(TxPduId, PduInfoPtr->SduDataPtr , PduInfoPtr->SduLength);
    #endif

    return result;
}