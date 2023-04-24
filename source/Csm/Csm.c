
/********************************************************************************************************/
/************************************************INCULDES************************************************/
/********************************************************************************************************/

#include "Csm.h"

#include <string.h>
#include "encrypt.h"

/********************************************************************************************************/
/*********************************************Defines****************************************************/
/********************************************************************************************************/

#define MAC_DATA_LEN ((uint8)100) /* Maximum number of stored MACs*/
#define MAC_LEN      ((uint8)16)      /* Length of MAC*/
#define MAX_MAC_BUFFER  32


/********************************************************************************************************/
/******************************************GlobalVaribles************************************************/
/********************************************************************************************************/

static uint8 MacData[MAC_DATA_LEN][MAC_LEN]; /* An array to store generated macs, uses jobId as an index*/



/********************************************************************************************************/
/********************************************Functions***************************************************/
/********************************************************************************************************/

/* A stub function to generate a MAC for the authentic-PDU*/
extern Std_ReturnType Csm_MacGenerate ( 
    uint32 jobId, 
    Crypto_OperationModeType mode,
    const uint8* dataPtr,
    uint32 dataLength,
    uint8* macPtr,
    uint32* macLengthPtr )
    {
        #ifdef MAC_DEBUG
            printf("######## in Csm_MacGenerate\n");
        #endif
        startEncryption(dataPtr , dataLength , macPtr ,macLengthPtr);
        #ifdef MAC_DEBUG
        printf("\nMac ");
        for(int i = 0; i < *macLengthPtr; i++)
        {
            printf("%d ", macPtr[i]);
        }
        printf("\n");
        #endif
        return E_OK;
    }



Std_ReturnType Csm_MacVerify(uint32 jobId, Crypto_OperationModeType mode, const uint8* dataPtr, uint32 dataLength,
const uint8* macPtr, const uint32 macLength, Crypto_VerifyResultType* verifyPtr)
{
    #ifdef MAC_DEBUG
        printf("######## in Csm_MacVerify\n");
    #endif
    uint32 Maclen = BIT_TO_BYTES(macLength);
    uint8 Mac_from_data[MAX_MAC_BUFFER];

    Std_ReturnType Mac_status;
    Std_ReturnType result;

    Mac_status = Csm_MacGenerate(jobId, mode, dataPtr, dataLength, Mac_from_data, &Maclen);
    #ifdef MAC_DEBUG
        printf("data : ");
        for(int i = 0; i < dataLength; i++)
        {
            printf("%d ", dataPtr[i]);
        }
        printf("\nMac ");
        for(int i = 0; i < Maclen; i++)
        {
            printf("%d  --  %d || ", Mac_from_data[i], macPtr[i]);
        }
        printf("\n");
    #endif
    if ((Mac_status == E_OK) && (Maclen == (BIT_TO_BYTES(macLength)))) 
    {
        if ((memcmp(Mac_from_data, macPtr, Maclen)) == 0) 
        {
            result = E_OK;
            *verifyPtr = CRYPTO_E_VER_OK;
        }
        else 
        {
            result = E_NOT_OK;
            *verifyPtr = CRYPTO_E_VER_NOT_OK;
        }
    } 
    else 
    {
        result = E_NOT_OK;
        *verifyPtr = CRYPTO_E_VER_NOT_OK;
    }
    return result;
}
