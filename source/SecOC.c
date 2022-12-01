#include "SecOC_Lcfg.h"
#include "SecOC_PBcfg.h"
#include "SecOC_Cbk.h"
#include "ComStack_Types.h"
#include "Det.h"
#include "Rte_SecOC.h"
#include "SecOC.h"



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
    uint8 arr_buffer[256] = *(PduInfoPtr->MetaDataPtr);
    if(STATUS_TRANSMISSION)
    {
        return E_OK;
    }
    else
    {
        return E_NOT_OK;
    }
}


/****************************************************
 *          * Function Info *                           *
 *                                                      *
 * Function_Name        : SecOC_TxConfirmation          *
 * Function_Index       : 8.4.3 [SWS_SecOC_00126]       *
 * Function_File        : SWS of secOC                  *
 * Function_Descripton  : The lower layer communication * 
 * interface module confirms  the transmission of a PDU *
 *        or the failure to transmit a PDU              *
 ***************************************************/
void SecOC_TxConfirmation (PduIdType TxPduId,Std_ReturnType result)
{
    uint8 *buffer;
    if(result==E_OK)
    {
        buffer = NULL;
        // clear buffer
    }
    PduR_SecOCIfTxConfirmation(TxPduId,result);
}