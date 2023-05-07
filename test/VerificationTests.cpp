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
extern Std_ReturnType verify(PduIdType RxPduId, PduInfoType* SecPdu, SecOC_VerificationResultType *verification_result);

}

/* This Function Use to made authenticate 
        1- Parse the Secure PDU
        2- Construct Data to authenticate
        3- generate the MAC
        4- Verfy MAC
        5- Update Freshness if Secuess
    --- to check its working need to see the Auth PDU is modified
*/


TEST(VerificationTests, verify1)
{
    SecOC_Init(&SecOC_Config);
    /* Secuss for id 0
        direct with header
    */
    PduIdType RxPduId = 0;
    
    PduInfoType *authPdu = &(SecOCRxPduProcessing[RxPduId].SecOCRxAuthenticPduLayer->SecOCRxAuthenticLayerPduRef);
    PduLengthType lengthbefore = authPdu->SduLength;
    

    /* Header + Authdata + Freshness + MAC
        2       100/200        1        196,200,222,153*/
    PduInfoType SecPdu;
    uint8 buffSec [100] = {2,100, 200, 1, 196,200,222,153};
    SecPdu.MetaDataPtr = 0;
    SecPdu.SduDataPtr = buffSec;
    SecPdu.SduLength = 8;

    SecOC_VerificationResultType verification_result;

    Std_ReturnType Result = verify(RxPduId, &SecPdu, &verification_result);

    EXPECT_EQ(Result, E_OK);

    PduLengthType lengthafter = authPdu->SduLength;

    EXPECT_NE(lengthbefore, lengthafter);

    uint8 buffVerfyAuth [100] = {100, 200};

    for(int i = 0; i < authPdu->SduLength; i++)
    {
        printf("%d ",authPdu->SduDataPtr[i]);
    }
    printf("\n");
    EXPECT_EQ(memcmp(buffVerfyAuth,authPdu->SduDataPtr, authPdu->SduLength), 0);
}


TEST(VerificationTests, verify2)
{
    /* Failed for id 0
     comapare with wrong data
        direct with header
    */
    SecOC_DeInit();
    SecOC_Init(&SecOC_Config);
    PduIdType RxPduId = 0;
    
    PduInfoType *authPdu = &(SecOCRxPduProcessing[RxPduId].SecOCRxAuthenticPduLayer->SecOCRxAuthenticLayerPduRef);
    authPdu->SduLength = 0;
    PduLengthType lengthbefore = authPdu->SduLength;
    

    /* Header + Authdata + Freshness + MAC
        2       100/200        2        196,200,222,153*/
    PduInfoType SecPdu;
    uint8 buffSec [100] = {2,100, 200, 2, 196,200,222,153};
    SecPdu.MetaDataPtr = 0;
    SecPdu.SduDataPtr = buffSec;
    SecPdu.SduLength = 8;

    SecOC_VerificationResultType verification_result;

    Std_ReturnType Result = verify(RxPduId, &SecPdu, &verification_result);

    EXPECT_NE(Result, E_OK);

    PduLengthType lengthafter = authPdu->SduLength;

    EXPECT_EQ(lengthbefore, lengthafter);

    uint8 buffVerfyAuth [100] = {10, 200};

    for(int i = 0; i < authPdu->SduLength; i++)
    {
        printf("%d ",authPdu->SduDataPtr[i]);
    }
    printf("\n");
    EXPECT_EQ(memcmp(buffVerfyAuth,authPdu->SduDataPtr, authPdu->SduLength), 0);
}
