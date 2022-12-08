#include "SecOC_Lcfg.h"
#include "SecOC_Cfg.h"
#include "SecOC_PBcfg.h"
#include "SecOC_Cbk.h"
#include "ComStack_Types.h"
#include "Det.h"
#include "Rte_SecOC.h"
#include "SecOC.h"

#include "PduR_SecOC.h"




PduInfoType SecOC_Buffer[SECOC_BUFFERLENGTH];


extern void SecOC_MainFunctionTx ( void )
{

}

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
        //SecOC_Buffer[TxPduId] = NULL;
        // clear buffer
    }
    PduR_SecOCIfTxConfirmation(TxPduId,result);


}

/****************************************************
 *          * Function Info *                           *
 *                                                      *
 * Function_Name        : SecOC_SPduTxConfirmation          *
 * Function_Index       : 8.5.5 [SWS_SecOC_91005]       *
 * Function_File        : SWS of secOC                  *
 * Function_Descripton  : This interface is used by     *
 * SecOC to indicate that the Secured I-PDU has been    *
 * initiated for transmission                           *
 ***************************************************/
#if (SECOC_USE_TX_CONFIRMATION == 1)
    void SecOc_SPduTxConfirmation (uint16 SecOCFreshnessValueID)
    {
        /* Specific User's Code need to be written here*/
    }
#endif
