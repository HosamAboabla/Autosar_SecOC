#include "SecOC_Lcfg.h"
#include "SecOC_PBcfg.h"
#include "SecOC_Cbk.h"
#include "Det.h"
#include "Rte_SecOC.h"
#include "SecOC.h"

Pdu_InfoType SecOC_Buffer[SECOC_BUFFERLENGTH];

Std_ReturnType SecOC_IfTransmit( Pdu_IdType TxPduId, const Pdu_InfoType* PduInfoPtr)
{
    Std_ReturnType result = E_OK; 
    if( TxPduId < SECOC_BUFFERLENGTH )
    {
        SecOC_Buffer[TxPduId] = *PduInfoPtr;
    }
    else
    {
        result = E_NOT_OK;
    }

    return result;
}