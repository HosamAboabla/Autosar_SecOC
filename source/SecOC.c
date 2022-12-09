#include "SecOC_Lcfg.h"
#include "SecOC_PBcfg.h"
#include "SecOC_Cbk.h"
#include "ComStack_Types.h"
#include "Det.h"
#include "Rte_SecOC.h"
#include "SecOC.h"

#include "PduR_SecOC.h"
#include "Csm.h"



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

#define MAX_COUNTER_FRESHNESS_IDS   10

Std_ReturnType SecOC_GetTxFreshnessTruncData (uint16 SecOCFreshnessValueID,uint8* SecOCFreshnessValue,
uint32* SecOCFreshnessValueLength,uint8* SecOCTruncatedFreshnessValue,uint32* SecOCTruncatedFreshnessValueLength) 
{
    if (SecOCFreshnessValueID > (MAX_COUNTER_FRESHNESS_IDS-1)) 
    {
        return E_NOT_OK;
    }
    else if (SecOCTruncatedFreshnessValueLength > SECOC_MAX_FRESHNESS_SIZE) 
    {
        return E_NOT_OK;
    }
    SecOC_FreshnessArrayType counter[MAX_COUNTER_FRESHNESS_IDS] = {0};
    uint32 Datalength = SECOC_MAX_FRESHNESS_SIZE - (*SecOCTruncatedFreshnessValueLength);
    for (int DataIndex = SECOC_MAX_FRESHNESS_SIZE - 1; DataIndex >= Datalength; DataIndex--) 
    {
        SecOCTruncatedFreshnessValue[DataIndex] = counter[SecOCFreshnessValueID][DataIndex];
    }
    return E_OK;
}

