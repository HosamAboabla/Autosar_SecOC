#include "FVM.h"

/* This is Stub for Freshness Value Manger that have the global counter */



/* Freshness Counter */
static SecOC_FreshnessArrayType Freshness_Counter[ID_MAX] = {255};
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
    if (SecOCFreshnessValueID > ID_MAX) {
        result =  E_NOT_OK;
    } else if ( (BIT_TO_BYTES(*SecOCFreshnessValueLength)) > SECOC_MAX_FRESHNESS_SIZE ) {
        result = E_NOT_OK;
    } else {
        
        /* Get data length in bytes */
        /* copy the counter to FreshnessValue in Big india */
        uint32 FreshnessIndex = SECOC_MAX_FRESHNESS_SIZE - 1;
        uint32 CounterIndex = 0;
        for (; (SECOC_MAX_FRESHNESS_SIZE > CounterIndex); FreshnessIndex--, CounterIndex++) {
            SecOCFreshnessValue[FreshnessIndex] = Freshness_Counter[SecOCFreshnessValueID][CounterIndex];
        }
        /* Update Length */
        *SecOCFreshnessValueLength = Freshness_Counter_length[SecOCFreshnessValueID]; 
    }
    return result;
}
