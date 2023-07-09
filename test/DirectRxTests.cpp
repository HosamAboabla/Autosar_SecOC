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
#include "ethernet.h"

#include <string.h>
extern SecOC_ConfigType SecOC_Config;
extern const SecOC_TxPduProcessingType     *SecOCTxPduProcessing;
extern const SecOC_RxPduProcessingType     *SecOCRxPduProcessing;
extern const SecOC_GeneralType             *SecOCGeneral;
extern Std_ReturnType authenticate(const PduIdType TxPduId, PduInfoType* authPdu, PduInfoType* SecPdu);
extern Std_ReturnType verify(PduIdType RxPduId, PduInfoType* SecPdu, SecOC_VerificationResultType *verification_result);
extern SecOC_PduCollection PdusCollections[];
extern SecOC_TxCountersType         SecOC_TxCounters[SECOC_NUM_OF_TX_PDU_PROCESSING];
extern SecOC_RxCountersType         SecOC_RxCounters[SECOC_NUM_OF_RX_PDU_PROCESSING];

extern PduLengthType                authRecieveLength[SECOC_NUM_OF_RX_PDU_PROCESSING];

}




TEST(AuthenticationTests, directRx)
{
    SecOC_Init(&SecOC_Config);


    Std_ReturnType result;
    uint8 securedPduCheck[] = {2, 100, 200, 1, 196, 200, 222, 153};
    uint8 authPduCheck[] = {100,200};


    #ifdef __linux__

        #define BUS_LENGTH_RECEIVE 8
        static uint8 dataRecieve [BUS_LENGTH_RECEIVE];
        uint16 id;
        ethernet_receive(dataRecieve , BUS_LENGTH_RECEIVE, &id);
        ASSERT_EQ(memcmp(dataRecieve , securedPduCheck, BUS_LENGTH_RECEIVE), 0);
        ASSERT_EQ(id, 0);
        PduInfoType PduInfoPtr = {
            .SduDataPtr = dataRecieve,
            .MetaDataPtr = (uint8*) &PdusCollections[id],
            .SduLength = BUS_LENGTH_RECEIVE,
        };

        ASSERT_EQ(PdusCollections[id].Type, SECOC_SECURED_PDU_CANIF);


        PduR_CanIfRxIndication(id, &PduInfoPtr);
        

    #endif
    




    PduIdType idx = 0;
    SecOC_VerificationResultType result_ver;

    PduInfoType *authPdu = &(SecOCRxPduProcessing[idx].SecOCRxAuthenticPduLayer->SecOCRxAuthenticLayerPduRef);
    PduInfoType *securedPdu = &(SecOCRxPduProcessing[idx].SecOCRxSecuredPduLayer->SecOCRxSecuredPdu->SecOCRxSecuredLayerPduRef);
    
    uint8 AuthHeadlen = SecOCRxPduProcessing[idx].SecOCRxSecuredPduLayer->SecOCRxSecuredPdu->SecOCAuthPduHeaderLength;
    PduLengthType securePduLength = AuthHeadlen + authRecieveLength[idx] + BIT_TO_BYTES(SecOCRxPduProcessing[idx].SecOCFreshnessValueTruncLength) + BIT_TO_BYTES(SecOCRxPduProcessing[idx].SecOCAuthInfoTruncLength);
    
    ASSERT_GE( securedPdu->SduLength , securePduLength);
    ASSERT_EQ(memcmp(securedPdu->SduDataPtr , securedPduCheck, securedPdu->SduLength), 0);
    

    result = verify(idx, securedPdu, &result_ver);

    ASSERT_EQ(result_ver, E_OK);
    ASSERT_EQ(result, E_OK);
    ASSERT_EQ(securedPdu->SduLength, 0);
    ASSERT_GT(authPdu->SduLength, 0);

    ASSERT_EQ(memcmp(authPdu->SduDataPtr , authPduCheck, authPdu->SduLength), 0);


    PduR_SecOCIfRxIndication(idx,  authPdu);    
}