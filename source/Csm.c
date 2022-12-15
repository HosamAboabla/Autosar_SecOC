#include "Csm.h"

#include <string.h>
#include "encrypt.h"

#define MAC_DATA_LEN ((uint8)100) // Maximum number of stored MACs
#define MAC_LEN      ((uint8)16)      // Length of MAC

static uint8 MacData[MAC_DATA_LEN][MAC_LEN]; // An array to store generated macs, uses jobId as an index




// A stub function to generate a MAC for the authentic-PDU
extern Std_ReturnType Csm_MacGenerate ( 
    uint32 jobId, 
    Crypto_OperationModeType mode,
    const uint8* dataPtr,
    uint32 dataLength,
    uint8* macPtr,
    uint32* macLengthPtr )
    {
        startEncryption(dataPtr , dataLength , macPtr ,macLengthPtr);
        return E_OK;
    }

#define MAC_LENGTH_BYTES 4
#define MAX_MAC_BUFFER  100
Std_ReturnType Csm_MacVerify(uint32 jobId, Crypto_OperationModeType mode, const uint8* dataPtr, uint32 dataLength,
const uint8* macPtr, const uint32 macLength, Crypto_VerifyResultType* verifyPtr)
{
    uint32 datalen = MAC_LENGTH_BYTES;
    uint8 mac[MAX_MAC_BUFFER];
    Std_ReturnType Mac_status, result;
    Mac_status = Csm_MacGenerate(jobId, mode, dataPtr, dataLength, mac, &datalen);
    if ((Mac_status == E_OK) && (datalen == (macLength/8))) 
    {
        if ((memcmp(dataPtr, macPtr, datalen)) == 0) 
        {
            result = E_OK;
            *verifyPtr = CRYPTO_E_VER_OK;
        }
        else 
        {
            result = E_NOT_OK;
            *verifyPtr = E_NOT_OK;
        }
    } 
    else 
    {
        result = E_NOT_OK;
        *verifyPtr = E_NOT_OK;
    }
    return result;
}
