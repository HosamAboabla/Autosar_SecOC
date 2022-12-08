#include "SecOC_PBcfg.h"
#include "SecOC_Lcfg.h"
#include "SecOC_Cbk.h"
#include "ComStack_Types.h"
#include "Det.h"
#include "Rte_SecOC.h"
#include "SecOC.h"

#include "PduR_SecOC.h"



#include "Rte_SecOC_Type.h"
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

/********************************************************
 *          * Function Info *                           *
 *                                                      *
 * Function_Name        : SecOC_TxConfirmation          *
 * Function_Index       : 8.4.3 [SWS_SecOC_00126]       *
 * Function_File        : SWS of secOC                  *
 * Function_Descripton  : The lower layer communication * 
 * interface module confirms  the transmission of a PDU *
 *        or the failure to transmit a PDU              *
 *******************************************************/
void SecOC_TxConfirmation (PduIdType TxPduId,Std_ReturnType result)
{
    if(result==E_OK)
    {
        //SecOC_Buffer[TxPduId] = NULL;
        // clear buffer
    }
    PduR_SecOCIfTxConfirmation(TxPduId,result);


}

/* So confess about ID- Value
i asume that a freshnessvlaue in global counter this global counter access by id
i want to put the data in which is in counter to the array of fresshness values so it made it  
how it will return busy or not okay */
Std_ReturnType SecOC_GetTxFreshness(uint16 SecOCFreshnessValueID, uint8* SecOCFreshnessValue,
uint32* SecOCFreshnessValueLength) {
    /*
    if (SecOCFreshnessValueID > 7)
        return E_NOT_OK;
    else if (SecOCFreshnessValueLength > SECOC_MAX_FRESHNESS_SIZE)
        return E_NOT_OK;
    */
    SecOC_FreshnessArrayType counter[8] = {0};
    uint32 Datalength = SECOC_MAX_FRESHNESS_SIZE - (*SecOCFreshnessValueLength);
    for (int DataIndex = SECOC_MAX_FRESHNESS_SIZE - 1; DataIndex >= Datalength; DataIndex--) {
        SecOCFreshnessValue[DataIndex] = counter[SecOCFreshnessValueID][DataIndex];
    }
    return E_OK;

}
