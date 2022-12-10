#include "FVM.h"

/* This is Stub for Freshness Value Manger that have the global counter */



/* Freshness Counter */
SecOC_FreshnessArrayType Freshness_Counter[ID_MAX] = {0};


uint8 countBits(uint8 n) {
    uint8 count = 0;
    while (n)
    {
        count++;
        n >>= 1;
    }
    return count;
}


Std_ReturnType FVM_IncreaseCounter(uint16 SecOCFreshnessValueID, uint32* SecOCFreshnessValueLength) {  

    uint8 INDEX = 0;
    uint32 len = 0;
    while (1)
    {
        Freshness_Counter[SecOCFreshnessValueID][INDEX] ++;
        if(Freshness_Counter[SecOCFreshnessValueID][INDEX] != 0)
        {
            break;
        } else {
            INDEX++;
        }
        /* Reset the counter if it full */
        if(INDEX == SECOC_MAX_FRESHNESS_SIZE)
        {
            break;
        }

        /* Calculate the Number of bits in the Counter */
        for (INDEX = SECOC_MAX_FRESHNESS_SIZE - 1; INDEX >= 0; INDEX--) {
            uint8 temp = countBits(Freshness_Counter[SecOCFreshnessValueID][INDEX]);
            if (temp != 0)
            {
                len = temp + INDEX * 8;
                break;
            }
        }
    }

    /* Shitf Right by 1 to divide by 2
        untill there is no number
        Can be replaced by --> uint8 len = ceil(log2(counterTemp.counter))*/

    for (INDEX = 0; INDEX < SECOC_MAX_FRESHNESS_SIZE; INDEX++) {
        len += countBits(Freshness_Counter[SecOCFreshnessValueID][INDEX]);
    }
    *SecOCFreshnessValueLength = len;

    return E_OK;
}

Std_ReturnType FVM_GetTxFreshness(uint16 SecOCFreshnessValueID, uint8* SecOCFreshnessValue,
uint32* SecOCFreshnessValueLength) {

    Std_ReturnType result = E_OK;
    if (SecOCFreshnessValueID > ID_MAX) {
        result =  E_NOT_OK;
    } else if ( ((*SecOCFreshnessValueLength) / 8) > SECOC_MAX_FRESHNESS_SIZE ) {
        result = E_NOT_OK;
    } else {
        
        /* Get data length in bytes */
        uint32 Datalength = SECOC_MAX_FRESHNESS_SIZE - ((*SecOCFreshnessValueLength) / 8);
        uint32 FreshnessIndex = SECOC_MAX_FRESHNESS_SIZE - 1;
        uint32 CounterIndex = 0;
        for (; ((FreshnessIndex >= Datalength) && (SECOC_MAX_FRESHNESS_SIZE > CounterIndex)); FreshnessIndex--, CounterIndex++) {
            SecOCFreshnessValue[FreshnessIndex] = Freshness_Counter[SecOCFreshnessValueID][CounterIndex];
        }
    }
    return result;
}
