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
extern Std_ReturnType authenticate(const PduIdType TxPduId, PduInfoType* AuthPdu, PduInfoType* SecPdu);

}



/* This Function Use to made authenticate 
        1- Get Freshness
        2- Construct Data to authenticate
        3- generate the MAC
        4- Construct the Scure PDU to broadCast
    --- to check its working need to see the Secure PDU is changing by length and add a data FV and MAC
*/
TEST(SecOCTests, authenticate1)
{
    SecOC_Init(&SecOC_Config);
    /* Secuss for id 0
        direct with header
    */
    PduIdType TxPduId = 0;

    PduInfoType AuthPdu;
    uint8 buffAuth [100] = {100, 200};
    AuthPdu.MetaDataPtr = 0;
    AuthPdu.SduDataPtr = buffAuth;
    AuthPdu.SduLength = 2;

    PduInfoType SecPdu = {0};
    uint8 buffSec [100] = {0};
    SecPdu.MetaDataPtr = 0;
    SecPdu.SduDataPtr = buffSec;
    SecPdu.SduLength = 0;

    Std_ReturnType Result = authenticate(TxPduId, &AuthPdu, &SecPdu);

    EXPECT_EQ(Result, E_OK);

    /* Header + Authdata + Freshness + MAC
        2       100/200        1          82/0/112/115*/

    uint8 buffVerfySecure [100] = {2,100, 200, 1, 196,200,222,153};

    for(int i = 0; i < SecPdu.SduLength; i++)
    {
        printf("%d ",SecPdu.SduDataPtr[i]);
    }
    printf("\n");
    EXPECT_EQ(memcmp(buffVerfySecure,SecPdu.SduDataPtr, SecPdu.SduLength), 0);
}


TEST(SecOCTests, authenticate2)
{
    SecOC_Init(&SecOC_Config);
    /* Secuss for id 0
        for big data
        direct with header
    */
    PduIdType TxPduId = 0;

    PduInfoType AuthPdu;
    uint8 buffAuth [100] = {100, 200};
    AuthPdu.MetaDataPtr = 0;
    AuthPdu.SduDataPtr = buffAuth;
    AuthPdu.SduLength = 2;

    PduInfoType SecPdu = {0};
    uint8 buffSec [100] = {0};
    SecPdu.MetaDataPtr = 0;
    SecPdu.SduDataPtr = buffSec;
    SecPdu.SduLength = 0;

    Std_ReturnType Result = authenticate(TxPduId, &AuthPdu, &SecPdu);

    EXPECT_EQ(Result, E_OK);

    /* Header + Authdata + Freshness + MAC
        2       100/200        1          82/0/112/115*/

    uint8 buffVerfySecure [100] = {2,100, 200, 2, 196, 100, 222, 153};

    for(int i = 0; i < SecPdu.SduLength; i++)
    {
        printf("%d ",SecPdu.SduDataPtr[i]);
    }
    printf("\n");
    EXPECT_NE(memcmp(buffVerfySecure,SecPdu.SduDataPtr, SecPdu.SduLength), 0);
}

TEST(SecOCTests, authenticate3)
{
    SecOC_Init(&SecOC_Config);
    /* Failed for id 0
        changing the MAC
        direct with header
    */
    PduIdType TxPduId = 0;

    PduInfoType AuthPdu;
    uint8 buffAuth [100] = {'H', 'S', 'h', 's'};
    AuthPdu.MetaDataPtr = 0;
    AuthPdu.SduDataPtr = buffAuth;
    AuthPdu.SduLength = 4;

    PduInfoType SecPdu = {0};
    uint8 buffSec [100] = {0};
    SecPdu.MetaDataPtr = 0;
    SecPdu.SduDataPtr = buffSec;
    SecPdu.SduLength = 0;

    Std_ReturnType Result = authenticate(TxPduId, &AuthPdu, &SecPdu);

    EXPECT_EQ(Result, E_OK);

    /* Header + Authdata + Freshness + MAC
        2       100/200        1          82/0/112/115*/

    uint8 buffVerfySecure [100] = {4, 'H', 'S', 'h', 's', 3, 209, 20, 205, 172};

    for(int i = 0; i < SecPdu.SduLength; i++)
    {
        printf("%c ",SecPdu.SduDataPtr[i]);
    }
    printf("\n");
    EXPECT_EQ(memcmp(buffVerfySecure,SecPdu.SduDataPtr, SecPdu.SduLength), 0);
}