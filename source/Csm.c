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
        return E_OK
    }
