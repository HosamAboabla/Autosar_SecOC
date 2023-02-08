#include "FVM.h"

/* This is Stub for Freshness Value Manger that have the global counter */

/* Freshness Counter */
static SecOC_FreshnessArrayType Freshness_Counter[ID_MAX] = {0};
static uint32 Freshness_Counter_length[ID_MAX] = {0};

/* Shitf Right by 1 to divide by 2
        untill there is no number
        Can be replaced by --> uint8 len = ceil(log2(counterTemp.counter))*/
uint8 countBits(uint8 n)
{
    uint8 count = 0;
    uint8 n_ = n;
    while (n_ > 0)
    {
        count++;
        n_ >>= 1;
    }
    return count;
}

Std_ReturnType FVM_IncreaseCounter(uint16 SecOCFreshnessValueID, uint32 *SecOCFreshnessValueLength)
{

    /* increase the counter by 1 */
    uint8 INDEX = 0;
    for (; INDEX < SECOC_MAX_FRESHNESS_SIZE; INDEX++)
    {
        Freshness_Counter[SecOCFreshnessValueID][INDEX]++;
        if (Freshness_Counter[SecOCFreshnessValueID][INDEX] != 0)
        {
            break;
        }
    }

    /* Calculate the Number of bits in the Counter */
    for (INDEX = SECOC_MAX_FRESHNESS_SIZE - 1; INDEX >= 0; INDEX--)
    {
        if (Freshness_Counter[SecOCFreshnessValueID][INDEX] != 0)
        {
            Freshness_Counter_length[SecOCFreshnessValueID] = countBits(Freshness_Counter[SecOCFreshnessValueID][INDEX]) + (INDEX * 8);
            break;
        }
    }

    *SecOCFreshnessValueLength = Freshness_Counter_length[SecOCFreshnessValueID];

    return E_OK;
}

Std_ReturnType FVM_GetTxFreshness(uint16 SecOCFreshnessValueID, uint8 *SecOCFreshnessValue,
                                  uint32 *SecOCFreshnessValueLength)
{

    Std_ReturnType result = E_OK;
    uint32 FreshnessValueLengthBytes = (BIT_TO_BYTES(*SecOCFreshnessValueLength));
    if (SecOCFreshnessValueID > ID_MAX)
    {
        result = E_NOT_OK;
    }
    else if (FreshnessValueLengthBytes > SECOC_MAX_FRESHNESS_SIZE)
    {
        result = E_NOT_OK;
    }
    else
    {

        /*  Acctual Freshness Value length --> for the minimu length of buffer
            Freshnes index and counter Index --> index to copy the value from counter to pointer
            last index t
         */
        uint32 AcctualFreshnessVallength = (FreshnessValueLengthBytes <= Freshness_Counter_length[SecOCFreshnessValueID]) ? (FreshnessValueLengthBytes) : (Freshness_Counter_length[SecOCFreshnessValueID]);
        uint32 FreshnessIndex = FreshnessValueLengthBytes - 1;
        uint8 FreshnessCounterIndex;
        for (FreshnessCounterIndex = 0; (FreshnessCounterIndex < AcctualFreshnessVallength); FreshnessCounterIndex++)
        {
            SecOCFreshnessValue[FreshnessIndex] = Freshness_Counter[SecOCFreshnessValueID][FreshnessCounterIndex];
            FreshnessIndex--;
        }
        /* Update Length */
        *SecOCFreshnessValueLength = AcctualFreshnessVallength;
    }
    return result;
}

Std_ReturnType FVM_GetRxFreshness(uint16 SecOCFreshnessValueID, const uint8 *SecOCTruncatedFreshnessValue, uint32 SecOCTruncatedFreshnessValueLength,
                                  uint16 SecOCAuthVerifyAttempts, uint8 *SecOCFreshnessValue, uint32 *SecOCFreshnessValueLength)
{
    Std_ReturnType result = E_OK;
    uint32 FreshnessValueLengthBytes = (BIT_TO_BYTES(*SecOCFreshnessValueLength));
    if (SecOCFreshnessValueID > ID_MAX)
    {
        result = E_NOT_OK;
    }
    else if (FreshnessValueLengthBytes > SECOC_MAX_FRESHNESS_SIZE)
    {
        result = E_NOT_OK;
    }
    else
    {

        /* The FVM module shall construct Freshness Verify Value (i.e. the Freshness Value to be used for Verification) and
         provide it to SecOC */
        //uint32 ActualFreshnessVallength = (FreshnessValueLengthBytes <= Freshness_Counter_length[SecOCFreshnessValueID]) ? (FreshnessValueLengthBytes) : (Freshness_Counter_length[SecOCFreshnessValueID]);
        uint32 ActualFreshnessVallength = BIT_TO_BYTES(Freshness_Counter_length[SecOCFreshnessValueID]);
        uint32 FreshnessIndex = ActualFreshnessVallength - 1;
        uint32 TrancatedCounterIndex = 0;
        uint32 counterTruncMax = BIT_TO_BYTES(Freshness_Counter_length[SecOCFreshnessValueID]) - BIT_TO_BYTES(SecOCTruncatedFreshnessValueLength) - 1;
        uint32 truncedFreshnessLength = BIT_TO_BYTES(SecOCTruncatedFreshnessValueLength);
        uint32 truncedFreshnessIndex = truncedFreshnessLength - 1;
        uint32 MSBsCounterIndex = truncedFreshnessLength;

        if (ActualFreshnessVallength == truncedFreshnessLength)
        {
            memcpy(SecOCFreshnessValue + ActualFreshnessVallength - truncedFreshnessLength, SecOCTruncatedFreshnessValue, truncedFreshnessLength);
        }
        else
        {
            SecOCAuthVerifyAttempts = 0;
            if (SecOCTruncatedFreshnessValue[TrancatedCounterIndex] > Freshness_Counter[SecOCFreshnessValueID][truncedFreshnessIndex])
            {
                /* most significant bits of FreshnessValue corresponding to reshnessValueID |
                FreshnessValue parsed from Secured I-PDU */
                for (; FreshnessIndex >= (ActualFreshnessVallength - MSBsCounterIndex); FreshnessIndex--)
                {
                    SecOCFreshnessValue[FreshnessIndex] = SecOCTruncatedFreshnessValue[truncedFreshnessIndex];
                    truncedFreshnessIndex--;
                }
                for (; (MSBsCounterIndex < ActualFreshnessVallength) && (FreshnessIndex >= 0); MSBsCounterIndex++)
                {
                    SecOCFreshnessValue[FreshnessIndex] = Freshness_Counter[SecOCFreshnessValueID][MSBsCounterIndex];
                    FreshnessIndex--;
                }
            }
            else
            {
                /*  most significant bits of FreshnessValue corresponding to SecOCFreshnessValueID + 1 |
                FreshnessValue parsed from payload */
                 for (; FreshnessIndex >= (ActualFreshnessVallength - MSBsCounterIndex); FreshnessIndex--)
                {
                    SecOCFreshnessValue[FreshnessIndex] = SecOCTruncatedFreshnessValue[truncedFreshnessIndex];
                    truncedFreshnessIndex--;
                }
                uint8 INDEX = MSBsCounterIndex;
                for (; INDEX < SECOC_MAX_FRESHNESS_SIZE; INDEX++)
                {
                    Freshness_Counter[SecOCFreshnessValueID][INDEX]++;
                    if (Freshness_Counter[SecOCFreshnessValueID][INDEX] != 0)
                    {
                        break;
                    }
                }
                for (; (MSBsCounterIndex < ActualFreshnessVallength) && (FreshnessIndex >= 0); MSBsCounterIndex++)
                {
                    SecOCFreshnessValue[FreshnessIndex] = Freshness_Counter[SecOCFreshnessValueID][MSBsCounterIndex];
                    FreshnessIndex--;
                }
            }
            *SecOCFreshnessValueLength = ActualFreshnessVallength * 8;
        }
        /* verified that the constructed FreshnessVerifyValue is larger than the last stored notion of the Freshness Value */
        /* If it is not larger than the last stored notion of the Freshness Value,
         the FVM shall stop the verification and drop the Secured I-PDU */
        uint32 counterFreshness = 0;
        for(FreshnessIndex = ActualFreshnessVallength - 1; FreshnessIndex >= 0; FreshnessIndex--)
        {
            if(SecOCFreshnessValue[counterFreshness] < Freshness_Counter[SecOCFreshnessValueID][FreshnessIndex])
            {
                result = E_NOT_OK;
                break;
            }
            else if (SecOCFreshnessValue[counterFreshness] > Freshness_Counter[SecOCFreshnessValueID][FreshnessIndex])
            {
                break;
            }
            counterFreshness++;
        }
    }   

     

    return result;
}