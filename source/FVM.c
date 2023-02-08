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

Std_ReturnType FVM_GetTxFreshnessTruncData (uint16 SecOCFreshnessValueID, uint8* SecOCFreshnessValue,
uint32* SecOCFreshnessValueLength, uint8* SecOCTruncatedFreshnessValue, uint32* SecOCTruncatedFreshnessValueLength)
{
    Std_ReturnType result = E_OK; 
    if (SecOCFreshnessValueID > ID_MAX) 
    {
        result = E_NOT_OK;
    }
    else if (*SecOCTruncatedFreshnessValueLength > SECOC_MAX_FRESHNESS_SIZE) 
    {
        result = E_NOT_OK;
    }
    else
    {
        /* get the current Value and convert it into Big india format*/
        SecOC_FreshnessArrayType currentFreshnessVal = {0};
        uint32 freshnessVallengthBytes = BIT_TO_BYTES(*SecOCFreshnessValueLength);
        uint32 acctualFreshnessVallength = (freshnessVallengthBytes <= BIT_TO_BYTES(Freshness_Counter_length[SecOCFreshnessValueID])) ? (freshnessVallengthBytes ) :  (BIT_TO_BYTES(Freshness_Counter_length[SecOCFreshnessValueID]));
        uint32 freshnessIndex = acctualFreshnessVallength - 1;
        uint32 counterIndex;
        uint32 truncFreshnessVallengthBytes = BIT_TO_BYTES(*SecOCTruncatedFreshnessValueLength);
        uint32 acctualFreshnessTruncVallength = (truncFreshnessVallengthBytes <= acctualFreshnessVallength) ? (truncFreshnessVallengthBytes ) :  (acctualFreshnessVallength);
        /* get freshness from counter and its length */
        for(counterIndex = 0; counterIndex < acctualFreshnessVallength; counterIndex++)
        {
            SecOCFreshnessValue[freshnessIndex] = Freshness_Counter[SecOCFreshnessValueID][counterIndex];
            freshnessIndex--;
        }
        *SecOCFreshnessValueLength = Freshness_Counter_length[SecOCFreshnessValueID];
        /* Trunc the LSBs from freshness and store in the Freshness and update it length*/
        memcpy(SecOCTruncatedFreshnessValue, SecOCFreshnessValue, acctualFreshnessTruncVallength - 1);
        uint8 bitTrunc = 8 - ((acctualFreshnessTruncVallength * 8) - *SecOCTruncatedFreshnessValueLength);
        SecOCTruncatedFreshnessValue[acctualFreshnessTruncVallength - 1] = (SecOCFreshnessValue[acctualFreshnessTruncVallength - 1] & (~(0xFF << bitTrunc)));
        *SecOCTruncatedFreshnessValueLength = acctualFreshnessTruncVallength * 8;
    }
    return result;
}