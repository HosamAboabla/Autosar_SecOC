#ifndef INCLUDE_CSM_H_
#define INCLUDE_CSM_H_

/********************************************************************************************************/
/************************************************INCULDES************************************************/
/********************************************************************************************************/

#include "Std_Types.h"
#include "SecOC_Debug.h"


/********************************************************************************************************/
/*********************************************DefinesAndEnums********************************************/
/********************************************************************************************************/

#define CRYPTO_E_KEY_NOT_VALID      ((Std_ReturnType)0x09)
#define CRYPTO_E_KEY_SIZE_MISMATCH  ((Std_ReturnType)0x0A)
#define CRYPTO_E_KEY_EMPTY          ((Std_ReturnType)0x0D)

/* Stub enumeration*/
typedef enum
{    
    Crypto_stub
}Crypto_OperationModeType;

typedef enum
{
    CRYPTO_E_VER_OK = 0x00,
    CRYPTO_E_VER_NOT_OK = 0x01
}Crypto_VerifyResultType;


/********************************************************************************************************/
/*****************************************FunctionPrototype**********************************************/
/********************************************************************************************************/

Std_ReturnType Csm_MacGenerate ( 
    uint32 jobId, 
    Crypto_OperationModeType mode,
    const uint8* dataPtr,
    uint32 dataLength,
    uint8* macPtr,
    uint32* macLengthPtr );

/*******************************************************
 *          * Function Info *                           *
 *                                                      *
 * Function_Name        : Csm_MacVerify                 *
 * Function_Index       : 8.3.3.2 [SWS_Csm_01050]       *
 * Function_File        : SWS of CSM                    *
 * Function_Descripton  : Verifies the given MAC by     *
 * SecOC to obtain the current freshness value          *
 * comparing if the MAC is generated with the given data*
 *******************************************************/

Std_ReturnType Csm_MacVerify(
uint32 jobId,
Crypto_OperationModeType mode,
const uint8* dataPtr,
uint32 dataLength,
const uint8* macPtr,
const uint32 macLength,
Crypto_VerifyResultType* verifyPtr
);

#endif