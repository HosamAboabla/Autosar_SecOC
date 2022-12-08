#include "Std_Types.h"

// Stub enumeration
typedef enum
{    
    Crypto_stub
}Crypto_OperationModeType;

Std_ReturnType Csm_MacGenerate ( 
    uint32 jobId, 
    Crypto_OperationModeType mode,
    const uint8* dataPtr,
    uint32 dataLength,
    uint8* macPtr,
    uint32* macLengthPtr );