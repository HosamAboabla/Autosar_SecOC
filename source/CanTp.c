#include "CanTP.h"
#include "SecOC_Cfg.h"

#ifdef LINUX
#include "ethernet.h"
#endif
#include "Pdur_CanTP.h"

Std_ReturnType CanTp_Transmit(PduIdType TxPduId,const PduInfoType* PduInfoPtr)
{
    Std_ReturnType result;
    
    #ifdef LINUX
    result = ethernet_send(PduInfoPtr->SduDataPtr , PduInfoPtr->SduLength);
    #endif

    return result;
}