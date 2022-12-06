#include "SecOC_Lcfg.h"
#include "SecOC_PBcfg.h"
#include "SecOC_Cbk.h"
#include "ComStack_Types.h"
#include "Det.h"
#include "Rte_SecOC.h"
#include "SecOC.h"
#include "PduR_SecOC.h"




PduInfoType SecOC_Buffer[SECOC_BUFFERLENGTH] = { NULL };

Std_ReturnType SecOC_IfTransmit( PduIdType TxPduId, const PduInfoType* PduInfoPtr)
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
// PduIdType SecOC_Buffer[SECOC_BUFFERLENGTH];  Hossam declared it

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
    if(result==E_OK)
    {
        SecOC_Buffer[TxPduId] = NULL;
        // clear buffer
    }
    PduR_SecOCIfTxConfirmation(TxPduId,result);


}





/****************************************************
 *          * Function Info *                           *
 *                                                      *
 * Function_Name        : SecOC_MainFunctionTx          *
 * Function_Index       : 8.6.2                         *
 * Function_File        : SWS of secOC                  *
 * Function_Descripton  : The lower layer communication * 
 * interface module confirms  the transmission of a PDU *
 *        or the failure to transmit a PDU              *
 ***************************************************/
void SecOC_MainFunctionTx(void)
{
    // check if initialized or not;
    PduIdType idx = 0;
    PduInfoType transmitPduInfo;
    for( ; idx < SECOC_BUFFERLENGTH ; idx++)
    {
        // check if there is data
        if( SecOC_Buffer[idx] != NULL )
        {
            // authenticate SecOC_Buffer[idx];
            // send authenticated data
            // authenticate( SecOC_Buffer[idx] , &transmitPduInfo)
            PduR_SecOCTransmit(idx , &transmitPduInfo);

        }
        else
        {

        }
    }
}