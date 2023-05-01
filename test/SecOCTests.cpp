#include <gtest/gtest.h>

extern "C" {    

#include "SecOC_Lcfg.h"
#include "SecOC_Cfg.h"
#include "SecOC_PBcfg.h"
#include "SecOC_Cbk.h"
#include "ComStack_Types.h"
#include "Rte_SecOC.h"
#include "SecOC.h"
#include "PduR_SecOC.h"
#include "Csm.h"
#include "Rte_SecOC_Type.h"
#include "PduR_Com.h"
#include "PduR_SecOC.h"
#include "Pdur_CanTP.h"
#include "PduR_CanIf.h"

#include <string.h>
extern SecOC_ConfigType SecOC_Config;
extern const SecOC_TxPduProcessingType     *SecOCTxPduProcessing;
extern const SecOC_RxPduProcessingType     *SecOCRxPduProcessing;
extern const SecOC_GeneralType             *SecOCGeneral;
}



TEST(SecOCTests, StartOfReception1)
{
    /* 
    Test :  SecOC_StartOfReception
    Case :  TpSduLength < buffer size
    */
    SecOC_Init(&SecOC_Config);

    /* Input Data */
    PduIdType id = 0;

    PduInfoType info;
    uint8 dataRec[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26};
    info.MetaDataPtr = 0;
    info.SduDataPtr = dataRec;
    info.SduLength = 4;

    PduLengthType TpSduLength = 26;
    PduLengthType bufferSizePtr = 0;
    

    BufReq_ReturnType Result  = SecOC_StartOfReception (id, &info, TpSduLength, &bufferSizePtr);


    EXPECT_EQ(Result , BUFREQ_OK);

    EXPECT_NE(0, bufferSizePtr);

}

TEST(SecOCTests, StartOfReception2)
{
    /* 
    Test :  SecOC_StartOfReception [SWS_SecOC_00215]
    Case : TpSduLength > buffer size
    */
    SecOC_Init(&SecOC_Config);

    /* Input Data */
    PduIdType id = 0;

    PduInfoType info;
    uint8 dataRec[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35};
    info.MetaDataPtr = 0;
    info.SduDataPtr = dataRec;
    info.SduLength = 4;

    PduLengthType TpSduLength = 35;
    PduLengthType bufferSizePtr = 0;
    

    BufReq_ReturnType Result  = SecOC_StartOfReception (id, &info, TpSduLength, &bufferSizePtr);


    EXPECT_EQ(Result , BUFREQ_E_OVFL);
    
    EXPECT_NE(0, bufferSizePtr);

}

TEST(SecOCTests, StartOfReception3)
{
    /* 
    Test :  SecOC_StartOfReception [SWS_SecOC_00181]
    Case : TpSduLength = 0 
    */
    SecOC_Init(&SecOC_Config);

    /* Input Data */
    PduIdType id = 0;

    PduInfoType info;
    uint8 dataRec[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35};
    info.MetaDataPtr = 0;
    info.SduDataPtr = dataRec;
    info.SduLength = 4;

    PduLengthType TpSduLength = 0;
    PduLengthType bufferSizePtr = 0;
    

    BufReq_ReturnType Result  = SecOC_StartOfReception (id, &info, TpSduLength, &bufferSizePtr);


    EXPECT_EQ(Result , BUFREQ_E_NOT_OK);
    
    EXPECT_NE(0, bufferSizePtr);

}

TEST(SecOCTests, StartOfReception4)
{
    /* 
    Test :  SecOC_StartOfReception 
    Case : TpSduLength < buffer size and Sdu is NULL 
    */
    SecOC_Init(&SecOC_Config);

    /* Input Data */
    PduIdType id = 0;
    PduInfoType info;
    info.SduDataPtr = NULL;
    PduLengthType TpSduLength = 20;
    PduLengthType bufferSizePtr = 0;
    

    BufReq_ReturnType Result  = SecOC_StartOfReception (id, &info, TpSduLength, &bufferSizePtr);


    EXPECT_EQ(Result , BUFREQ_OK);
    
    EXPECT_NE(0, bufferSizePtr);

}

TEST(SecOCTests, StartOfReception5)
{
    /* 
    Test :  SecOC_StartOfReception [SWS_SecOC_00263]
    Case : the header have that auth biger tha max
    */
    SecOC_Init(&SecOC_Config);

    /* Input Data */
    PduIdType id = 0;

    PduInfoType info;
    uint8 dataRec[] = {21,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25};
    info.MetaDataPtr = 0;
    info.SduDataPtr = dataRec;
    info.SduLength = 4;

    PduLengthType TpSduLength = 28;
    PduLengthType bufferSizePtr = 0;
    

    BufReq_ReturnType Result  = SecOC_StartOfReception (id, &info, TpSduLength, &bufferSizePtr);


    EXPECT_EQ(Result , BUFREQ_E_NOT_OK);
    
    EXPECT_NE(0, bufferSizePtr);

}