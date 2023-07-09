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
extern Std_ReturnType authenticate(const PduIdType TxPduId, PduInfoType* authPdu, PduInfoType* SecPdu);

extern SecOC_TxCountersType         SecOC_TxCounters[SECOC_NUM_OF_TX_PDU_PROCESSING];

}




TEST(AuthenticationTests, directTx)
{
    SecOC_Init(&SecOC_Config);

    #ifdef COM_DEBUG
    printf("############### Send Direct with header ###############\n");
    #endif

    uint8 test_meta_data = 0;
    PduIdType TxPduId = 0;

    PduInfoType sendPdu;
    uint8 authBuffer [100] = {100, 200};
    sendPdu.MetaDataPtr = &test_meta_data;
    sendPdu.SduDataPtr = authBuffer;
    sendPdu.SduLength = 2;

    ASSERT_EQ(PduR_ComTransmit(TxPduId,&sendPdu) , E_OK);

    // check content of authPdu and sentPdu
    PduInfoType *authPduCheck = &(SecOCTxPduProcessing[TxPduId].SecOCTxAuthenticPduLayer->SecOCTxAuthenticLayerPduRef);
    ASSERT_EQ(memcmp(sendPdu.SduDataPtr ,authPduCheck->SduDataPtr, sendPdu.SduLength), 0);



    Std_ReturnType result;

    PduInfoType *authPdu = &(SecOCTxPduProcessing[TxPduId].SecOCTxAuthenticPduLayer->SecOCTxAuthenticLayerPduRef);
    PduInfoType *securedPdu = &(SecOCTxPduProcessing[TxPduId].SecOCTxSecuredPduLayer->SecOCTxSecuredPdu->SecOCTxSecuredLayerPduRef);
    SecOC_TxSecuredPduCollectionType * securePduCollection = (SecOCTxPduProcessing[TxPduId].SecOCTxSecuredPduLayer->SecOCTxSecuredPduCollection);

    /* Check if there is data */
    ASSERT_GT(authPdu->SduLength , 0);

    uint32 AuthPduLen = authPdu->SduLength;

    uint8 securedPduCheck[] = {2, 100, 200, 1, 196, 200, 222, 153};
    result = authenticate(TxPduId , authPdu , securedPdu);
    ASSERT_EQ(authPdu->SduLength , 0);
    ASSERT_EQ(memcmp(securedPdu->SduDataPtr , securedPduCheck, securedPdu->SduLength), 0);


    if(result == E_OK )
    {
        /* Using Freshness Value Based on Single Freshness Counter we need to keep it synchronise 
            increase counter before Broadcast as require */
        /*[SWS_SecOC_00031]*/
        FVM_IncreaseCounter(SecOCTxPduProcessing[TxPduId].SecOCFreshnessValueId);

        /* [SWS_SecOC_00062] */
        ASSERT_EQ(PduR_SecOCTransmit(TxPduId , securedPdu) , E_OK);
        ASSERT_EQ(securedPdu->SduLength , 0);
    }
    else if ((result == E_BUSY) || (result == QUEUE_FULL))
    {
        /* [SWS_SecOC_00227] */
        SecOC_TxCounters[TxPduId].AuthenticationCounter++;


        /* [SWS_SecOC_00228] */
        if( SecOC_TxCounters[TxPduId].AuthenticationCounter >= SecOCTxPduProcessing[TxPduId].SecOCAuthenticationBuildAttempts )
        {
            authPdu->SduLength = 0;
        }
    }
    else /* result == E_NOT_OK */
    {
        authPdu->SduLength = 0;                
    }
}