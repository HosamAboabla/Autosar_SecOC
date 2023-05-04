#include <gtest/gtest.h>
// #include<gmock/gmock.h>
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



// TEST(SecOCTests, example1)
// {  
//     uint8 buff[20]={10,100,200,250};
//     PduLengthType len = 4;
//     PduInfoType SPDU;
//     uint8 meta = 0;
//     SPDU.MetaDataPtr = &meta;
//     SPDU.SduDataPtr = buff;
//     SPDU.SduLength = len;

//     SecOC_Init(&SecOC_Config);
//     SecOC_IfTransmit(0, &SPDU);
    
//     printf("Data transmit :\n");
    
//     for(int i = 0; i < SPDU.SduLength; i++)
//         printf("%d ", SPDU.SduDataPtr[i]);
//     printf("\n");
 
//     PduInfoType *secured_TX = &(SecOCTxPduProcessing[0].SecOCTxSecuredPduLayer->SecOCTxSecuredPdu->SecOCTxSecuredLayerPduRef);
//     PduInfoType *auth = &(SecOCTxPduProcessing[0].SecOCTxAuthenticPduLayer->SecOCTxAuthenticLayerPduRef);
//     PduInfoType *auth_RX = &(SecOCRxPduProcessing[0].SecOCRxAuthenticPduLayer->SecOCRxAuthenticLayerPduRef);

//     SecOCMainFunctionTx();
    
//     printf("data after authen: \n");
//     for(int i = 0; i < secured_TX->SduLength; i++)
//         printf("%d ", secured_TX->SduDataPtr[i]);
//     printf("\ndone Tx\n");   

//     PduR_CanIfRxIndication((uint16)0,secured_TX);

//     PduInfoType *secured = &(SecOCRxPduProcessing[0].SecOCRxSecuredPduLayer->SecOCRxSecuredPdu->SecOCRxSecuredLayerPduRef);
    
//     printf("in RX data received : \n");
//     for(int i = 0; i < secured->SduLength; i++)
//     {
//         ASSERT_NE(SPDU.SduDataPtr[i],secured->SduDataPtr[i]);
//     }

//     printf("\n");  
//     // main function
//     SecOCMainFunctionRx();
// }   

// TEST(SecOCTests,example2)
// {
//         /*
//     the length of the whole data (TpSduLength) is 26
//     SecOC_ReceptionOverflowStrategy_Type is SECOC_QUEUE
//     the header length (AuthHeadlen) is 1
//     bufferSizePtr max is 31
//     the current data length in the buffer (securedPdu->SduLength) is 0
//     the received data length is 19
//     the recieved sdulength is 4
//     Max data length is (SECOC_AUTHPDU_MAX_LENGTH) is 20
//     */
//     SecOC_Init(&SecOC_Config);
//     PduIdType id = 0;
//     uint8 dataRec[] = {19,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,255,1,55,66,77,88};
//     uint8 dataRec2[] = {0};
//     PduInfoType info;
//     info.MetaDataPtr = 0;
//     info.SduDataPtr=dataRec;
//     info.SduLength = 4;
//     PduLengthType bufferlen = SECOC_SECPDU_MAX_LENGTH;
//     PduLengthType TpSduLength=26;
//     PduInfoType *securedPdu = &(SecOCRxPduProcessing[id].SecOCRxSecuredPduLayer->SecOCRxSecuredPdu->SecOCRxSecuredLayerPduRef);
//     securedPdu->MetaDataPtr = 0;
//     securedPdu->SduDataPtr=dataRec2;
//     securedPdu->SduLength = 0;
//     BufReq_ReturnType result;
//     printf("\nTEST1\n");
//     printf("\nbefore  : ");
//     printf("SIZEBIFFER : %d \n", bufferlen);
//     result=SecOC_StartOfReception (id,&info,TpSduLength,&bufferlen);
//     printf("\nafter  : ");

//     printf("SIZEBIFFER : %d \n", bufferlen);
	
// 	EXPECT_EQ(result,BUFREQ_OK);
	
// 	EXPECT_EQ(result,BUFREQ_E_NOT_OK);
	
// 	EXPECT_EQ(result,BUFREQ_E_OVFL);
	
// }

//======================


TEST(SecOCTests,SecOCCopyTXData1)
{
    SecOC_Init(&SecOC_Config);
    PduIdType pduid = 0;
    uint8 sdata[5] = {0};
    uint8 mdata[5] = {0};
    PduLengthType length = 5;
    PduInfoType info = {sdata,mdata,length};
    TpDataStateType retrystate = TP_DATACONF;
    PduLengthType retrycout = 0;
    RetryInfoType retry = {retrystate,retrycout};
    PduLengthType availableDataPtr = 0;
    uint8 buffersdata[10] = {1,2,3,4,5,6,7,8,9,10};
    uint8 buffermdata[0] = {0};
    PduLengthType bufferlength = 10;
    PduInfoType *securedPdu = &(SecOCTxPduProcessing[pduid].SecOCTxSecuredPduLayer->SecOCTxSecuredPdu->SecOCTxSecuredLayerPduRef);
    securedPdu->SduDataPtr = buffersdata;
    securedPdu->MetaDataPtr = buffermdata;
    securedPdu->SduLength = bufferlength;
	

    /* just put data in the info buffer */
    for(int i = 0; i < length; i++)
        printf("before info: %d\t",info.SduDataPtr[i]);
    printf("\n");
    for(int i = 0; i < bufferlength; i++)
        printf("before : %d\t",securedPdu->SduDataPtr[i]);
    printf("\nreturn :%d\n",SecOC_CopyTxData (pduid, &info, NULL, &availableDataPtr));
    
    EXPECT_EQ(BUFREQ_OK,SecOC_CopyTxData (pduid, &info, NULL, &availableDataPtr));
    
    for(int i = 0; i < length; i++)
        printf("after info: %d\t",info.SduDataPtr[i]);
    printf("\n");
    for(int i = 0; i < bufferlength; i++)
        printf("after : %d\t",securedPdu->SduDataPtr[i]);

    printf("\navalible bytes in buffer --> %d\n", availableDataPtr);
    printf("\n#####\n");
    printf("\nreturn : %d\n",SecOC_CopyTxData (pduid, &info, NULL, &availableDataPtr));

    EXPECT_EQ(BUFREQ_OK,SecOC_CopyTxData (pduid, &info, NULL, &availableDataPtr));

    for(int i = 0; i < length; i++)
        printf("after info: %d\t",info.SduDataPtr[i]);
    printf("\n");
    for(int i = 0; i < bufferlength; i++)
        printf("after : %d\t",securedPdu->SduDataPtr[i]);
    
    printf("\navalible bytes in buffer --> %d\n", availableDataPtr);
    printf("\n#####\n");

}

TEST(SecOCTests,SecOCCopyTXData2)
{
    SecOC_Init(&SecOC_Config);
    PduIdType pduid = 0;
    uint8 sdata[5] = {0};
    uint8 mdata[5] = {0};
    PduLengthType length = 5;
    PduInfoType info = {sdata,mdata,length};
    TpDataStateType retrystate = TP_DATACONF;
    PduLengthType retrycout = 0;
    RetryInfoType retry = {retrystate,retrycout};
    PduLengthType availableDataPtr = 0;
    uint8 buffersdata[10] = {1,2,3,4,5,6,7,8,9,10};
    uint8 buffermdata[0] = {0};
    PduLengthType bufferlength = 10;
    PduInfoType *securedPdu = &(SecOCTxPduProcessing[pduid].SecOCTxSecuredPduLayer->SecOCTxSecuredPdu->SecOCTxSecuredLayerPduRef);
    securedPdu->SduDataPtr = buffersdata;
    securedPdu->MetaDataPtr = buffermdata;
    securedPdu->SduLength = bufferlength;
	
    
    for(int i = 0; i < length; i++)
        printf("before info: %d\t",info.SduDataPtr[i]);
    printf("\n");
    for(int i = 0; i < bufferlength; i++)
        printf("before : %d\t",securedPdu->SduDataPtr[i]);
    printf("\nnreturn :%d\n",SecOC_CopyTxData (pduid, &info, &retrystate, &availableDataPtr));

    EXPECT_EQ(BUFREQ_OK,SecOC_CopyTxData (pduid, &info, NULL, &availableDataPtr));

    for(int i = 0; i < length; i++)
        printf("after info: %d\t",info.SduDataPtr[i]);
    printf("\n");
    for(int i = 0; i < bufferlength; i++)
        printf("after : %d\t",securedPdu->SduDataPtr[i]);

    printf("\navalible bytes in buffer --> %d\n", availableDataPtr);
    printf("\n#####\n");
    printf("\nreturn : %d\n",SecOC_CopyTxData (pduid, &info, &retrystate, &availableDataPtr));

    EXPECT_EQ(BUFREQ_OK,SecOC_CopyTxData (pduid, &info, NULL, &availableDataPtr));

    for(int i = 0; i < length; i++)
        printf("after info: %d\t",info.SduDataPtr[i]);
    printf("\n");
    for(int i = 0; i < bufferlength; i++)
        printf("after : %d\t",securedPdu->SduDataPtr[i]);
    
    printf("\navalible bytes in buffer --> %d\n", availableDataPtr);
    printf("\n#####\n");

}
TEST(SecOCTests,SecOCCopyTXData3)
{
    SecOC_Init(&SecOC_Config);
    PduIdType pduid = 0;
    uint8 sdata[5] = {0};
    uint8 mdata[5] = {0};
    PduLengthType length = 5;
    PduInfoType info = {sdata,mdata,length};
    TpDataStateType retrystate = TP_DATACONF;
    PduLengthType retrycout = 0;
    RetryInfoType retry = {retrystate,retrycout};
    PduLengthType availableDataPtr = 0;
    uint8 buffersdata[10] = {1,2,3,4,5,6,7,8,9,10};
    uint8 buffermdata[0] = {0};
    PduLengthType bufferlength = 10;
    PduInfoType *securedPdu = &(SecOCTxPduProcessing[pduid].SecOCTxSecuredPduLayer->SecOCTxSecuredPdu->SecOCTxSecuredLayerPduRef);
    securedPdu->SduDataPtr = buffersdata;
    securedPdu->MetaDataPtr = buffermdata;
    securedPdu->SduLength = bufferlength;
	
    
        /* use it one time 
        the buffer Index will be 5
        with TP_CONFPENDING it will return the last data
    */
    SecOC_CopyTxData (pduid, &info, &retrystate, &availableDataPtr);
    
    retry.TpDataState = TP_CONFPENDING;
    for(int i = 0; i < length; i++)
        printf("before info: %d\t",info.SduDataPtr[i]);
    printf("\n");
    for(int i = 0; i < bufferlength; i++)
        printf("before : %d\t",securedPdu->SduDataPtr[i]);
    printf("\n%d\n",SecOC_CopyTxData (pduid, &info, &retry, &availableDataPtr));
	
	EXPECT_EQ(BUFREQ_OK,SecOC_CopyTxData (pduid, &info, NULL, &availableDataPtr));
	
    for(int i = 0; i < length; i++)
        printf("after info: %d\t",info.SduDataPtr[i]);
    printf("\n");
    for(int i = 0; i < bufferlength; i++)
        printf("after : %d\t",securedPdu->SduDataPtr[i]);
    printf("\n avalible bytes in buffer --> %d\n", availableDataPtr);
	
	EXPECT_EQ(BUFREQ_OK,SecOC_CopyTxData (pduid, &info, NULL, &availableDataPtr));
	
    printf("\n#####\n");

}
TEST(SecOCTests,SecOCCopyTXData4)
{
    SecOC_Init(&SecOC_Config);
    PduIdType pduid = 0;
    uint8 sdata[5] = {0};
    uint8 mdata[5] = {0};
    PduLengthType length = 5;
    PduInfoType info = {sdata,mdata,length};
    TpDataStateType retrystate = TP_DATACONF;
    PduLengthType retrycout = 0;
    RetryInfoType retry = {retrystate,retrycout};
    PduLengthType availableDataPtr = 0;
    uint8 buffersdata[10] = {1,2,3,4,5,6,7,8,9,10};
    uint8 buffermdata[0] = {0};
    PduLengthType bufferlength = 10;
    PduInfoType *securedPdu = &(SecOCTxPduProcessing[pduid].SecOCTxSecuredPduLayer->SecOCTxSecuredPdu->SecOCTxSecuredLayerPduRef);
    securedPdu->SduDataPtr = buffersdata;
    securedPdu->MetaDataPtr = buffermdata;
    securedPdu->SduLength = bufferlength;
	
    
        /* use it one time 
        the buffer Index will be 5
        with TP_CONFPENDING it will return the last data
    */
    SecOC_CopyTxData (pduid, &info, &retrystate, &availableDataPtr);
    
    retry.TpDataState = TP_CONFPENDING;
    for(int i = 0; i < length; i++)
        printf("before info: %d\t",info.SduDataPtr[i]);
    printf("\n");
    for(int i = 0; i < bufferlength; i++)
        printf("before : %d\t",securedPdu->SduDataPtr[i]);
    printf("\n%d\n",SecOC_CopyTxData (pduid, &info, &retry, &availableDataPtr));
	
	EXPECT_EQ(BUFREQ_OK,SecOC_CopyTxData (pduid, &info, NULL, &availableDataPtr));
	
    for(int i = 0; i < length; i++)
        printf("after info: %d\t",info.SduDataPtr[i]);
    printf("\n");
    for(int i = 0; i < bufferlength; i++)
        printf("after : %d\t",securedPdu->SduDataPtr[i]);
    printf("\n avalible bytes in buffer --> %d\n", availableDataPtr);
	
	EXPECT_EQ(BUFREQ_OK,SecOC_CopyTxData (pduid, &info, NULL, &availableDataPtr));
	
    printf("\n#####\n");

}



TEST(SecOCTests,SecOC_TpTxConfirmation1)
{
    SecOC_Init(&SecOC_Config);

    Std_ReturnType result=E_OK;

    PduIdType TxPduId = 0;
    uint8 dataRec[] = {1,2,3,4,5};
    PduInfoType *securedPdu = &(SecOCTxPduProcessing[TxPduId].SecOCTxSecuredPduLayer->SecOCTxSecuredPdu->SecOCTxSecuredLayerPduRef);
    securedPdu->MetaDataPtr = 0;
    securedPdu->SduDataPtr=dataRec;
    securedPdu->SduLength = 5;

    SecOC_TpTxConfirmation(TxPduId , result);

    EXPECT_EQ(0,securedPdu->SduLength);
}


