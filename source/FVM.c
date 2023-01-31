#include "FVM.h"

/* This is Stub for Freshness Value Manger that have the global counter */



/* Freshness Counter */
static SecOC_FreshnessArrayType Freshness_Counter[ID_MAX] = {0};
static uint32 Freshness_Counter_length [ID_MAX] = {0};

/* Shitf Right by 1 to divide by 2
        untill there is no number
        Can be replaced by --> uint8 len = ceil(log2(counterTemp.counter))*/
uint8 countBits(uint8 n) {
    uint8 count = 0;
    while (n > 0)
    {
        count++;
        n >>= 1;
    }
    return count;
}


Std_ReturnType FVM_IncreaseCounter(uint16 SecOCFreshnessValueID, uint32* SecOCFreshnessValueLength) {  

    /* increase the counter by 1 */
    uint8 INDEX = 0;
    for (; INDEX < SECOC_MAX_FRESHNESS_SIZE; INDEX ++)
    {
        Freshness_Counter[SecOCFreshnessValueID][INDEX] ++;
        if(Freshness_Counter[SecOCFreshnessValueID][INDEX] != 0)
        {
            break;
        }
    }
    
     /* Calculate the Number of bits in the Counter */
    for (INDEX = SECOC_MAX_FRESHNESS_SIZE - 1; INDEX >= 0; INDEX--) {
        if(Freshness_Counter[SecOCFreshnessValueID][INDEX] != 0)
        {
            Freshness_Counter_length[SecOCFreshnessValueID] = countBits(Freshness_Counter[SecOCFreshnessValueID][INDEX]) + INDEX * 8;
            break;
        }
    }
   
    *SecOCFreshnessValueLength = Freshness_Counter_length[SecOCFreshnessValueID];

    return E_OK;
}


Std_ReturnType FVM_GetTxFreshness(uint16 SecOCFreshnessValueID, uint8* SecOCFreshnessValue,
uint32* SecOCFreshnessValueLength) {

    Std_ReturnType result = E_OK;
    uint32 FreshnessValueLengthBytes = (BIT_TO_BYTES(*SecOCFreshnessValueLength));
    if (SecOCFreshnessValueID > ID_MAX) {
        result =  E_NOT_OK;
    } else if ( FreshnessValueLengthBytes > SECOC_MAX_FRESHNESS_SIZE ) {
        result = E_NOT_OK;
    } else {
        
        /*  Acctual Freshness Value length --> for the minimu length of buffer
            Freshnes index and counter Index --> index to copy the value from counter to pointer
            last index t
         */
        uint32 AcctualFreshnessVallength = (FreshnessValueLengthBytes <= Freshness_Counter_length[SecOCFreshnessValueID]) ? (FreshnessValueLengthBytes ) :  (Freshness_Counter_length[SecOCFreshnessValueID]);
        uint32 FreshnessIndex = FreshnessValueLengthBytes- 1, FreshnessCounterIndex; 
        for (FreshnessCounterIndex = 0; (FreshnessCounterIndex < AcctualFreshnessVallength);FreshnessCounterIndex++) 
        {
            SecOCFreshnessValue[FreshnessIndex] = Freshness_Counter[SecOCFreshnessValueID][FreshnessCounterIndex];
            FreshnessIndex--;
        }
        /* Update Length */
        *SecOCFreshnessValueLength = AcctualFreshnessVallength; 
    }
    return result;
}


Std_ReturnType FVM_GetRxFreshness(uint16 SecOCFreshnessValueID,const uint8* SecOCTruncatedFreshnessValue,uint32 SecOCTruncatedFreshnessValueLength,
    uint16 SecOCAuthVerifyAttempts,uint8* SecOCFreshnessValue,uint32* SecOCFreshnessValueLength)
{
    Std_ReturnType result = E_OK;
    uint32 FreshnessValueLengthBytes = (BIT_TO_BYTES(*SecOCFreshnessValueLength));
    if (SecOCFreshnessValueID > ID_MAX) 
    {
        result =  E_NOT_OK;
    } else if ( FreshnessValueLengthBytes > SECOC_MAX_FRESHNESS_SIZE ) 
    {
        result = E_NOT_OK;
    } else 
    {

        uint32 AcctualFreshnessVallength = (FreshnessValueLengthBytes <= Freshness_Counter_length[SecOCFreshnessValueID])?(FreshnessValueLengthBytes):(Freshness_Counter_length[SecOCFreshnessValueID]);
        uint32 FreshnessIndex = FreshnessValueLengthBytes- 1, FreshnessCounterIndex, TrancatedCounter = 0;
        uint32 counterTruncMax =  BIT_TO_BYTES(Freshness_Counter_length[SecOCFreshnessValueID]) - BIT_TO_BYTES(SecOCTruncatedFreshnessValueLength); 
        /* Assume that the buffer of truncated is its truncated length 
        and the SecOCFreshnessValueLength is buffer of freshness */
        /* Valid the Truncated Freshness Value */
        // for (FreshnessCounterIndex = BIT_TO_BYTES(Freshness_Counter_length[SecOCFreshnessValueID]) - 1 ; (FreshnessCounterIndex > counterTruncMax) && (TrancatedCounter < BIT_TO_BYTES(SecOCTruncatedFreshnessValueLength)); FreshnessCounterIndex --)
        // {
        //     if(SecOCTruncatedFreshnessValue[TrancatedCounter] != Freshness_Counter[SecOCFreshnessValueID][FreshnessCounterIndex])
        //     {
        //         /* Not Sure */
        //         SecOCAuthVerifyAttempts++;
        //         result =  E_NOT_OK;
        //         break;
        //     }
        //     TrancatedCounter++;
        // }

        /* Get the Current Value from Freshness counter */
        
        for (FreshnessCounterIndex = 0; (FreshnessCounterIndex < AcctualFreshnessVallength);FreshnessCounterIndex++) 
        {
            SecOCFreshnessValue[FreshnessIndex] = Freshness_Counter[SecOCFreshnessValueID][FreshnessCounterIndex];
            FreshnessIndex--;
        }
        /* Update Length */
        *SecOCFreshnessValueLength = AcctualFreshnessVallength; 
    }
    return result;
}