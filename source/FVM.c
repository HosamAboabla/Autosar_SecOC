#include "FVM.h"
#include <string.h>
#include "SecOC_Debug.h"

/* This is Stub for Freshness Value Manger that have the global counter */



/* Freshness Counter */
static SecOC_FreshnessArrayType Freshness_Counter[SecOC_FreshnessValue_ID_MAX] = {0};
static uint32 Freshness_Counter_length [SecOC_FreshnessValue_ID_MAX] = {0};

/* Shitf Right by 1 to divide by 2
        untill there is no number
        Can be replaced by --> uint8 len = ceil(log2(counterTemp.counter))*/
uint8 countBits(uint8 n) {
    uint8 count = 0;
    uint8 n_ = n;
    while (n_ > 0)
    {
        count++;
        n_ >>= 1;
    }
    return count;
}

/*
Count the Number of bit in array of bytes */
uint8 countSizeBits(const uint8* arrayBytes, uint8 maxSize)
{
    sint8 INDEX;
    uint8 length = 0;
    for (INDEX = maxSize - 1; INDEX >= 0; INDEX--) {
        if(arrayBytes[INDEX] != 0)
        {
            length = countBits(arrayBytes[INDEX]) + (INDEX * 8);
            break;
        }
    }
    return length;
}


Std_ReturnType FVM_IncreaseCounter(uint16 SecOCFreshnessValueID) {  
    #ifdef FV_DEBUG
        printf("######## FVM_IncreaseCounter for id %d\n", SecOCFreshnessValueID);
    #endif
    /* increase the counter by 1 */
    uint8 INDEX = 0;
    uint8 maxIndex = BIT_TO_BYTES(SECOC_MAX_FRESHNESS_SIZE);
    for (; INDEX < maxIndex; INDEX ++)
    {
        Freshness_Counter[SecOCFreshnessValueID][INDEX] ++;
        if(Freshness_Counter[SecOCFreshnessValueID][INDEX] != 0)
        {
            break;
        }
    }
    
    /* Calculate the Number of bits in the Counter */
    Freshness_Counter_length[SecOCFreshnessValueID] = countSizeBits(Freshness_Counter[SecOCFreshnessValueID], maxIndex);
    return E_OK;
}

/* Set the Counter Value to new Value */
Std_ReturnType FVM_UpdateCounter(uint16 SecOCFreshnessValueID, uint8* SecOCFreshnessValue,
uint32 SecOCFreshnessValueLength)
{
    uint32 freshnessCounterIndex; 
    uint32 SecOCFreshnessValueLengthBytes = BIT_TO_BYTES(SecOCFreshnessValueLength);
    (void)memcpy(Freshness_Counter[SecOCFreshnessValueID], SecOCFreshnessValue, SecOCFreshnessValueLengthBytes);
    /* Calculate the Number of bits in the Counter */
    Freshness_Counter_length[SecOCFreshnessValueID] = countSizeBits(Freshness_Counter[SecOCFreshnessValueID], SecOCFreshnessValueLengthBytes);
}


Std_ReturnType FVM_GetTxFreshness(uint16 SecOCFreshnessValueID, uint8* SecOCFreshnessValue,
uint32* SecOCFreshnessValueLength) {
    #ifdef FV_DEBUG
        printf("######## in FVM_GetTxFreshness\n");
    #endif
    Std_ReturnType result = E_OK;
    
    if (SecOCFreshnessValueID > SecOC_FreshnessValue_ID_MAX) {
        result =  E_NOT_OK;
    } else if ( *SecOCFreshnessValueLength > SECOC_MAX_FRESHNESS_SIZE ) {
        result = E_NOT_OK;
    } else {
        
        /*  Acctual Freshness Value length --> for the minimu length of buffer
            Freshnes index and counter Index --> index to copy the value from counter to pointer
            last index t
         */
        uint32 acctualFreshnessVallength = (*SecOCFreshnessValueLength <= Freshness_Counter_length[SecOCFreshnessValueID]) ? (*SecOCFreshnessValueLength ) :  (Freshness_Counter_length[SecOCFreshnessValueID]);
        uint32 acctualFreshnessVallengthBytes = BIT_TO_BYTES(acctualFreshnessVallength);
        (void)memcpy(SecOCFreshnessValue, Freshness_Counter[SecOCFreshnessValueID], acctualFreshnessVallengthBytes);

        /* Update Length */
        *SecOCFreshnessValueLength = acctualFreshnessVallength;
        #ifdef FV_DEBUG
        printf("return  : %d .. \n", result);
        for(int i = 0; i < acctualFreshnessVallengthBytes; i++)
        {
            printf("Byte %d : %d ", i, SecOCFreshnessValue[i]);
        }
        printf("\n");

        #endif
    }
    return result;
}

Std_ReturnType FVM_GetRxFreshness(uint16 SecOCFreshnessValueID, const uint8 *SecOCTruncatedFreshnessValue, uint32 SecOCTruncatedFreshnessValueLength,
                                  uint16 SecOCAuthVerifyAttempts, uint8 *SecOCFreshnessValue, uint32 *SecOCFreshnessValueLength)
{
    #ifdef FV_DEBUG
        printf("######## in FVM_GetRxFreshness\n");
    #endif
    Std_ReturnType result = E_OK;
    if (SecOCFreshnessValueID > SecOC_FreshnessValue_ID_MAX)
    {
        result = E_NOT_OK;
    }
    else if (*SecOCFreshnessValueLength > SECOC_MAX_FRESHNESS_SIZE)
    {
        result = E_NOT_OK;
    }
    else
    {
        /* The FVM module shall construct Freshness Verify Value (i.e. the Freshness Value to be used for Verification) and
         provide it to SecOC */
        uint32 freshnessVallengthBytes = BIT_TO_BYTES(Freshness_Counter_length[SecOCFreshnessValueID]);

        /* Update Trunc Length  */
        uint32 truncedFreshnessLengthBytes = BIT_TO_BYTES(SecOCTruncatedFreshnessValueLength);
        SecOCTruncatedFreshnessValueLength = countSizeBits(SecOCTruncatedFreshnessValue, truncedFreshnessLengthBytes);
        truncedFreshnessLengthBytes = BIT_TO_BYTES(SecOCTruncatedFreshnessValueLength); 

        uint32 maxTruncedIndex = (truncedFreshnessLengthBytes > 0) ? (truncedFreshnessLengthBytes - 1) : (0);

        if (Freshness_Counter_length[SecOCFreshnessValueID] == SecOCTruncatedFreshnessValueLength)
        {
            #ifdef FV_DEBUG
            printf("length counter = length trunc\n");
            #endif
            (void)memcpy(SecOCFreshnessValue, SecOCTruncatedFreshnessValue, truncedFreshnessLengthBytes);
            *SecOCFreshnessValueLength = SecOCTruncatedFreshnessValueLength;
        }
        else
        {
            SecOCAuthVerifyAttempts = 0;
            /* Put the Current Freshness in the FreshnessValue */
            (void)memcpy(SecOCFreshnessValue, Freshness_Counter[SecOCFreshnessValueID], freshnessVallengthBytes);
            /* construction of Freshness Value */
            sint16 index;
            sint8 equalityFlag = memcmp(SecOCTruncatedFreshnessValue, Freshness_Counter[SecOCFreshnessValueID], truncedFreshnessLengthBytes);
            for(index = maxTruncedIndex; index >= 0; index--)
            {
                if(SecOCTruncatedFreshnessValue[index] > Freshness_Counter[SecOCFreshnessValueID][index])
                {
                    #ifdef FV_DEBUG
                    printf("LSB  counter < LSB trunc\n");
                    #endif
                    /* most significant bits of FreshnessValue corresponding to FreshnessValueID |
                    FreshnessValue parsed from Secured I-PDU */
                    (void)memcpy(SecOCFreshnessValue, SecOCTruncatedFreshnessValue, maxTruncedIndex);
                    uint8 remainingBitsTrunc = 8 - ((truncedFreshnessLengthBytes * 8) - SecOCTruncatedFreshnessValueLength);
                    SecOCFreshnessValue[maxTruncedIndex] = (SecOCTruncatedFreshnessValue[maxTruncedIndex] & (~(0xFF << remainingBitsTrunc))) | (Freshness_Counter[SecOCFreshnessValueID][maxTruncedIndex] & (0xFF << remainingBitsTrunc));
                    uint8 maxLength = (freshnessVallengthBytes > truncedFreshnessLengthBytes) ? (freshnessVallengthBytes) : (truncedFreshnessLengthBytes);
                    *SecOCFreshnessValueLength = countSizeBits(SecOCFreshnessValue,  maxLength);
                }
                else if (SecOCTruncatedFreshnessValue[index] < Freshness_Counter[SecOCFreshnessValueID][index] || equalityFlag == 0)
                {
                    #ifdef FV_DEBUG
                    printf("LSB counter > LSB trunc\n");
                    #endif
                    /*  most significant bits of (FreshnessValue corresponding to SecOCFreshnessValueID + 1) |
                    FreshnessValue parsed from payload */

                    (void)memcpy(SecOCFreshnessValue, SecOCTruncatedFreshnessValue, maxTruncedIndex);
                    uint8 remainingBitsTrunc = 8 - ((truncedFreshnessLengthBytes * 8) - SecOCTruncatedFreshnessValueLength);
                    if(remainingBitsTrunc == 0 || SecOCTruncatedFreshnessValueLength == 0)
                    {
                        SecOCFreshnessValue[maxTruncedIndex] = Freshness_Counter[SecOCFreshnessValueID][maxTruncedIndex] + 1;
                        if(Freshness_Counter[SecOCFreshnessValueID][maxTruncedIndex] > SecOCFreshnessValue[maxTruncedIndex])
                        {
                            for (index = maxTruncedIndex + 1; index < freshnessVallengthBytes+1; index ++)
                            {
                                SecOCFreshnessValue[index] ++;
                                if(SecOCFreshnessValue[index] != 0)
                                {
                                    break;
                                }
                            }
                        }
                    }
                    else if(remainingBitsTrunc == 8)
                    {
                        SecOCFreshnessValue[maxTruncedIndex] = SecOCTruncatedFreshnessValue[maxTruncedIndex];
                        for (index = maxTruncedIndex + 1; index < freshnessVallengthBytes+1; index ++)
                        {
                            SecOCFreshnessValue[index] ++;
                            if(SecOCFreshnessValue[index] != 0)
                            {
                                break;
                            }
                        }
                    }
                    else
                    {
                        uint8 MSBsCounter = (Freshness_Counter[SecOCFreshnessValueID][maxTruncedIndex] >> remainingBitsTrunc) + 1;
                        uint8 MSBsCounterShift = MSBsCounter << remainingBitsTrunc;
                        uint8 index;
                        SecOCFreshnessValue[maxTruncedIndex] = (SecOCTruncatedFreshnessValue[maxTruncedIndex] & (~(0xFF << remainingBitsTrunc))) | (MSBsCounterShift);
                        if((MSBsCounterShift == 0) && (MSBsCounter > 0))
                        {
                            for (index = maxTruncedIndex + 1; index < freshnessVallengthBytes+1; index ++)
                            {
                                SecOCFreshnessValue[index] ++;
                                if(SecOCFreshnessValue[index] != 0)
                                {
                                    break;
                                }
                            }
                        }
                        
                    }
                    *SecOCFreshnessValueLength = countSizeBits(SecOCFreshnessValue, freshnessVallengthBytes + 1);
                }
                else
                {
                    continue;
                }
                break;
            }
        }
        
        /* verified that the constructed FreshnessVerifyValue is larger than the last stored notion of the Freshness Value */
        /* If it is not larger than the last stored notion of the Freshness Value,
         the FVM shall stop the verification and drop the Secured I-PDU */
        sint16 index = BIT_TO_BYTES(*SecOCFreshnessValueLength) - 1;
        #ifdef FV_DEBUG
            printf("constructed FreshnessVerifyValue is  \n");
            for(int i = 0; i <= index; i++)
            {
                printf("byte %d: %d  ", i , SecOCFreshnessValue[i]);
            }
            printf("\n");
        #endif
        sint8 equalityFlag = memcmp(SecOCFreshnessValue, Freshness_Counter[SecOCFreshnessValueID], index + 1);
        for(; index >= 0; index --)
        {
            if (Freshness_Counter[SecOCFreshnessValueID][index] < SecOCFreshnessValue[index])
            {
                result = E_OK;
            }
            else if (Freshness_Counter[SecOCFreshnessValueID][index] > SecOCFreshnessValue[index] || equalityFlag == 0)
            {
                result= E_NOT_OK;
            }
            else
            {
                continue;
            }
            break;
        }

    }
    #ifdef FV_DEBUG
        printf("Result is %d  \n", result);
    #endif
    return result;
}

Std_ReturnType FVM_GetTxFreshnessTruncData(uint16 SecOCFreshnessValueID, uint8* SecOCFreshnessValue,
uint32* SecOCFreshnessValueLength, uint8* SecOCTruncatedFreshnessValue, uint32* SecOCTruncatedFreshnessValueLength)
{
    #ifdef FV_DEBUG
        printf("######## in FVM_GetTxFreshnessTruncData\n");
    #endif
    Std_ReturnType result = E_OK; 
    if (SecOCFreshnessValueID > SecOC_FreshnessValue_ID_MAX) 
    {
        result = E_NOT_OK;
    }
    else if (*SecOCTruncatedFreshnessValueLength > SECOC_MAX_FRESHNESS_SIZE) 
    {
        result = E_NOT_OK;
    }
    else
    {
        uint32 acctualFreshnessVallength = (*SecOCFreshnessValueLength <= Freshness_Counter_length[SecOCFreshnessValueID]) ? (*SecOCFreshnessValueLength) :  (Freshness_Counter_length[SecOCFreshnessValueID]);
        uint32 acctualFreshnessVallengthBytes = BIT_TO_BYTES(acctualFreshnessVallength);
        uint32 truncFreshnessVallengthBytes = BIT_TO_BYTES(*SecOCTruncatedFreshnessValueLength);
        uint32 acctualFreshnessTruncVallength = (truncFreshnessVallengthBytes <= acctualFreshnessVallengthBytes) ? (truncFreshnessVallengthBytes ) :  (acctualFreshnessVallengthBytes);
        /* get freshness from counter and its length */
        (void)memcpy(SecOCFreshnessValue, Freshness_Counter[SecOCFreshnessValueID], acctualFreshnessVallengthBytes);
        *SecOCFreshnessValueLength = acctualFreshnessVallength;
        /* Trunc the LSBs from freshness and store in the Freshness and update it length*/
        if(acctualFreshnessTruncVallength > 0)
        {
            (void)memcpy(SecOCTruncatedFreshnessValue, SecOCFreshnessValue, acctualFreshnessTruncVallength - 1);
            uint8 bitTrunc = 8 - ((acctualFreshnessTruncVallength * 8) - *SecOCTruncatedFreshnessValueLength);
            SecOCTruncatedFreshnessValue[acctualFreshnessTruncVallength - 1] = (SecOCFreshnessValue[acctualFreshnessTruncVallength - 1] & (~(0xFF << bitTrunc)));
        }
        *SecOCTruncatedFreshnessValueLength = countSizeBits(SecOCTruncatedFreshnessValue, truncFreshnessVallengthBytes);
    #ifdef FV_DEBUG
        printf("result is %d\n", result);
        printf("FV is ");
        for (int i = 0; i < acctualFreshnessVallengthBytes; i++)
        {
            printf("%d ",SecOCFreshnessValue[i]);
        }
        printf("\nTrunc FV is ");
        for (int i = 0; i < acctualFreshnessTruncVallength; i++)
        {
            printf("%d ",SecOCTruncatedFreshnessValue[i]);
        }
        printf("\n");
    #endif
    }
    
    return result;
}

