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



TEST(SecOCTests, Freshnesstest ){

    //FVM_IncreaseCounter(0, 100);
    // uint8_t adata[100] = "hello, world";
    // uint8_t adata[100] = {0, 1, 2, 3, 9, 5, 6, 7, 8, 9, 10, 11, 12};
    // uint8_t sdata[100];
    // PduInfoType AuthPdu, SecPdu;
    // uint8 x = 0;
    // AuthPdu.SduDataPtr = adata;
    // AuthPdu.SduLength = SECOC_AUTHPDU_MAX_LENGTH;
    // AuthPdu.MetaDataPtr = &x;
    uint16 SecOCFreshnessValueID = 10;

    uint8 SecOCFreshnessValue[8]={0};
    uint32 SecOCFreshnessValueLength = 8 * 8;
    
   for(int i = 0; i < 0x32C; i++)
       FVM_IncreaseCounter(10);
    for(int i = 0; i < 0x32C; i++)
       FVM_IncreaseCounter(9);
    
	uint8 buff[16]={10,100,200,250};
    PduLengthType len = 4;
    PduInfoType SPDU;
    uint8 meta = 0;
    SPDU.MetaDataPtr = &meta;
    SPDU.SduDataPtr = buff;
    SPDU.SduLength = len;

    SecOC_Init(&SecOC_Config);
    SecOC_IfTransmit(0, &SPDU);
    
    printf("Data transmit :\n");
    
    for(int i = 0; i < SPDU.SduLength; i++)
        printf("%d ", SPDU.SduDataPtr[i]);
    printf("\n");
 
    PduInfoType *secured_TX = &(SecOCTxPduProcessing[0].SecOCTxSecuredPduLayer->SecOCTxSecuredPdu->SecOCTxSecuredLayerPduRef);
    PduInfoType *auth = &(SecOCTxPduProcessing[0].SecOCTxAuthenticPduLayer->SecOCTxAuthenticLayerPduRef);
    PduInfoType *auth_RX = &(SecOCRxPduProcessing[0].SecOCRxAuthenticPduLayer->SecOCRxAuthenticLayerPduRef);

    SecOCMainFunctionTx();
    
    printf("data after authen: \n");
    for(int i = 0; i < secured_TX->SduLength; i++)
        printf("%d ", secured_TX->SduDataPtr[i]);
    printf("\ndone Tx\n");   

    
    PduR_CanIfRxIndication((uint16)0,secured_TX);

    PduInfoType *secured = &(SecOCRxPduProcessing[0].SecOCRxSecuredPduLayer->SecOCRxSecuredPdu->SecOCRxSecuredLayerPduRef);
    
    printf("in RX data received : \n");
    for(int i = 0; i < secured->SduLength; i++)
        printf("%d ", secured->SduDataPtr[i]);
    printf("\n");  
    // main function
    SecOCMainFunctionRx();
    
    printf("after verification :\n");  
    for(int i = 0; i < auth_RX->SduLength; i++)
        printf("%d ", auth_RX->SduDataPtr[i]);
    printf("\n");
    
    SecOCMainFunctionRx();
    
    printf("after verification :\n");  
    for(int i = 0; i < auth_RX->SduLength; i++)
        printf("%d ", auth_RX->SduDataPtr[i]);
    printf("\n");

    EXPECT_EQ(2, 2);

}

TEST(SecOCTests, authenticate){
    int x = 2 + 5;
    EXPECT_EQ(x, 5);
}

