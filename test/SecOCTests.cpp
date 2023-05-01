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
        TpSduLength = 26
        SecOC_ReceptionOverflowStrategy_Type is SECOC_QUEUE
        the header length (AuthHeadlen) is 1
        bufferSizePtr max is 29
        the current data length in the buffer (securedPdu->SduLength) is 0
        the recieved sdulength is 4
        Max data length is (SECOC_AUTHPDU_MAX_LENGTH) is 20
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
    Test :  SecOC_StartOfReception
    Case : TpSduLength > buffer size
        TpSduLength = 35
        SecOC_ReceptionOverflowStrategy_Type is SECOC_QUEUE
        the header length (AuthHeadlen) is 1
        bufferSizePtr max is 29
        the current data length in the buffer (securedPdu->SduLength) is 0
        the recieved sdulength is 4
        Max data length is (SECOC_AUTHPDU_MAX_LENGTH) is 20
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
    Test :  SecOC_StartOfReception
    Case : TpSduLength = 0 
        TpSduLength = 0
        SecOC_ReceptionOverflowStrategy_Type is SECOC_QUEUE
        the header length (AuthHeadlen) is 1
        bufferSizePtr max is 29
        the current data length in the buffer (securedPdu->SduLength) is 0
        the recieved sdulength is 4
        Max data length is (SECOC_AUTHPDU_MAX_LENGTH) is 20
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
        TpSduLength = 0
        SecOC_ReceptionOverflowStrategy_Type is SECOC_QUEUE
        the header length (AuthHeadlen) is 1
        bufferSizePtr max is 29
        the current data length in the buffer (securedPdu->SduLength) is 0
        the recieved sdulength is 4
        Max data length is (SECOC_AUTHPDU_MAX_LENGTH) is 20
    */
    SecOC_Init(&SecOC_Config);

    /* Input Data */
    PduIdType id = 0;

    PduInfoType info;
    uint8 dataRec[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35};

    PduLengthType TpSduLength = 20;
    PduLengthType bufferSizePtr = 0;
    

    BufReq_ReturnType Result  = SecOC_StartOfReception (id, NULL, TpSduLength, &bufferSizePtr);


    EXPECT_EQ(Result , BUFREQ_OK);
    
    EXPECT_NE(0, bufferSizePtr);

}