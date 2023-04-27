#include <gtest/gtest.h>

extern "C" {    

#include "FVM.h"
}




TEST(FreshnessTests, RXFreshnessEquality1)
{
    /* Freshness Test
    Case # Truncfreshnesslength == counterlength   ---> here verifyFreshness = TruncValue
        verifyFreshness  >  counterValue    ---> return OK
     */
    uint16 SecOCFreshnessValueID = 1;

    /* Value comes from Tx */
    uint8 SecOCTruncatedFreshnessValue[100] = {255,1};
    uint32 SecOCTruncatedFreshnessValueLength = 9;

    /* Value in Rx */
    uint8 SecOCFreshnessValueRX[100] = {254,1};
    uint32 SecOCFreshnessValueLengthRX = 9;
    FVM_UpdateCounter(SecOCFreshnessValueID, SecOCFreshnessValueRX, SecOCFreshnessValueLengthRX);

    uint16 SecOCAuthVerifyAttempts = 0;

    /* Value out from RX */
    uint8 SecOCFreshnessValue[100] = {0};
    uint32 SecOCFreshnessValueLength = 0;

    /*printf("before : length is %d and Values is --> ",SecOCFreshnessValueLength);
    for (int i = 0; i < BIT_TO_BYTES(SecOCFreshnessValueLength); i++)
        printf("%d ", SecOCFreshnessValue[i]);
    printf("\n");*/

    Std_ReturnType returnValue = FVM_GetRxFreshness( SecOCFreshnessValueID, SecOCTruncatedFreshnessValue, SecOCTruncatedFreshnessValueLength,
                                   SecOCAuthVerifyAttempts, SecOCFreshnessValue, &SecOCFreshnessValueLength);

    EXPECT_EQ(returnValue, E_OK);

    /*printf("after : length is %d and Values is --> ",SecOCFreshnessValueLength);
    for (int i = 0; i < BIT_TO_BYTES(SecOCFreshnessValueLength); i++)
    {
        printf("%d ", SecOCFreshnessValue[i]);
        EXPECT_EQ(SecOCTruncatedFreshnessValue[i], SecOCFreshnessValue[i]);
    }
    printf("\n");*/

    for (int i = 0; i < BIT_TO_BYTES(SecOCFreshnessValueLength); i++)
    {
        EXPECT_EQ(SecOCTruncatedFreshnessValue[i], SecOCFreshnessValue[i]);
    }
}

TEST(FreshnessTests, RXFreshnessEquality2)
{
    /* Freshness Test
    Case # Truncfreshnesslength == counterlength   ---> here verifyFreshness = TruncValue
        verifyFreshness  == counterValue    ---> return NOT OK
     */
    uint16 SecOCFreshnessValueID = 2;

    /* Value comes from Tx */
    uint8 SecOCTruncatedFreshnessValue[100] = {255,1};
    uint32 SecOCTruncatedFreshnessValueLength = 9;

    /* Value in Rx */
    uint8 SecOCFreshnessValueRX[100] = {255,1};
    uint32 SecOCFreshnessValueLengthRX = 9;
    FVM_UpdateCounter(SecOCFreshnessValueID, SecOCFreshnessValueRX, SecOCFreshnessValueLengthRX);

    uint16 SecOCAuthVerifyAttempts = 0;

    /* Value out from RX */
    uint8 SecOCFreshnessValue[100] = {0};
    uint32 SecOCFreshnessValueLength = 0;

    /*printf("before : length is %d and Values is --> ",SecOCFreshnessValueLength);
    for (int i = 0; i < BIT_TO_BYTES(SecOCFreshnessValueLength); i++)
        printf("%d ", SecOCFreshnessValue[i]);
    printf("\n");*/

    Std_ReturnType returnValue = FVM_GetRxFreshness( SecOCFreshnessValueID, SecOCTruncatedFreshnessValue, SecOCTruncatedFreshnessValueLength,
                                   SecOCAuthVerifyAttempts, SecOCFreshnessValue, &SecOCFreshnessValueLength);

    EXPECT_EQ(returnValue, E_NOT_OK);

    /*printf("after : length is %d and Values is --> ",SecOCFreshnessValueLength);
    for (int i = 0; i < BIT_TO_BYTES(SecOCFreshnessValueLength); i++)
    {
        printf("%d ", SecOCFreshnessValue[i]);
        EXPECT_EQ(SecOCTruncatedFreshnessValue[i], SecOCFreshnessValue[i]);
    }
    printf("\n");*/

    for (int i = 0; i < BIT_TO_BYTES(SecOCFreshnessValueLength); i++)
    {
        EXPECT_EQ(SecOCTruncatedFreshnessValue[i], SecOCFreshnessValue[i]);
    }
}

TEST(FreshnessTests, RXFreshnessEquality3)
{
    /* Freshness Test
    Case # Truncfreshnesslength == counterlength   ---> here verifyFreshness = TruncValue
        verifyFreshness  <  counterValue    ---> return NOT OK 
     */
    uint16 SecOCFreshnessValueID = 3;

    /* Value comes from Tx */
    uint8 SecOCTruncatedFreshnessValue[100] = {255,2};
    uint32 SecOCTruncatedFreshnessValueLength = 10;

    /* Value in Rx */
    uint8 SecOCFreshnessValueRX[100] = {255,3};
    uint32 SecOCFreshnessValueLengthRX = 10;
    FVM_UpdateCounter(SecOCFreshnessValueID, SecOCFreshnessValueRX, SecOCFreshnessValueLengthRX);

    uint16 SecOCAuthVerifyAttempts = 0;

    /* Value out from RX */
    uint8 SecOCFreshnessValue[100] = {0};
    uint32 SecOCFreshnessValueLength = 0;

    /*printf("before : length is %d and Values is --> ",SecOCFreshnessValueLength);
    for (int i = 0; i < BIT_TO_BYTES(SecOCFreshnessValueLength); i++)
        printf("%d ", SecOCFreshnessValue[i]);
    printf("\n");*/

    Std_ReturnType returnValue = FVM_GetRxFreshness( SecOCFreshnessValueID, SecOCTruncatedFreshnessValue, SecOCTruncatedFreshnessValueLength,
                                   SecOCAuthVerifyAttempts, SecOCFreshnessValue, &SecOCFreshnessValueLength);

    EXPECT_EQ(returnValue, E_NOT_OK);

    /*printf("after : length is %d and Values is --> ",SecOCFreshnessValueLength);
    for (int i = 0; i < BIT_TO_BYTES(SecOCFreshnessValueLength); i++)
    {
        printf("%d ", SecOCFreshnessValue[i]);
        EXPECT_EQ(SecOCTruncatedFreshnessValue[i], SecOCFreshnessValue[i]);
    }
    printf("\n");*/

    for (int i = 0; i < BIT_TO_BYTES(SecOCFreshnessValueLength); i++)
    {
        EXPECT_EQ(SecOCTruncatedFreshnessValue[i], SecOCFreshnessValue[i]);
    }
}


TEST(FreshnessTests, RXFreshnessGreaterThan)
{
    /* Freshness Test
    Case # Truncfreshnesslength >  counterlength   ---> here verifyFreshness = TruncValue 
        verifyFreshness  >  counterValue    ---> return OK 
     */
    uint16 SecOCFreshnessValueID = 4;

    /* Value comes from Tx */
    uint8 SecOCTruncatedFreshnessValue[100] = {255,31};
    uint32 SecOCTruncatedFreshnessValueLength = 13;

    /* Value in Rx */
    uint8 SecOCFreshnessValueRX[100] = {255,1};
    uint32 SecOCFreshnessValueLengthRX = 9;
    FVM_UpdateCounter(SecOCFreshnessValueID, SecOCFreshnessValueRX, SecOCFreshnessValueLengthRX);

    uint16 SecOCAuthVerifyAttempts = 0;

    /* Value out from RX */
    uint8 SecOCFreshnessValue[100] = {0};
    uint32 SecOCFreshnessValueLength = 0;

    /*printf("before : length is %d and Values is --> ",SecOCFreshnessValueLength);
    for (int i = 0; i < BIT_TO_BYTES(SecOCFreshnessValueLength); i++)
        printf("%d ", SecOCFreshnessValue[i]);
    printf("\n");*/

    Std_ReturnType returnValue = FVM_GetRxFreshness( SecOCFreshnessValueID, SecOCTruncatedFreshnessValue, SecOCTruncatedFreshnessValueLength,
                                   SecOCAuthVerifyAttempts, SecOCFreshnessValue, &SecOCFreshnessValueLength);

    EXPECT_EQ(returnValue, E_OK);

    /*
    printf("after : length is %d and Values is --> ",SecOCFreshnessValueLength);
    for (int i = 0; i < BIT_TO_BYTES(SecOCFreshnessValueLength); i++)
    {
        printf("%d ", SecOCFreshnessValue[i]);
        EXPECT_EQ(SecOCTruncatedFreshnessValue[i], SecOCFreshnessValue[i]);
    }
    printf("\n");*/

    for (int i = 0; i < BIT_TO_BYTES(SecOCFreshnessValueLength); i++)
    {
        EXPECT_EQ(SecOCTruncatedFreshnessValue[i], SecOCFreshnessValue[i]);
    }
}





}