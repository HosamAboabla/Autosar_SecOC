#ifndef INCLUDE_SECOC_TYPES_H_
#define INCLUDE_SECOC_TYPES_H_

#include "Std_Types.h"
#include "ComStack_Types.h"





typedef enum {
    SECOC_BOTH = 0,
    SECOC_FAILURE_ONLY,
    SECOC_NONE
}SecOC_StatusPropagationMode_Type;

typedef enum {
    SECOC_AUTH_COLLECTON_PDU = 0,
    SECOC_CRYPTO_COLLECTON_PDU,
    SECOC_SECURED_PDU
}SecOC_PduCollection_Type;


typedef enum {
    SECOC_QUEUE = 0,
    SECOC_REJECT,
    SECOC_REPLACE
}SecOC_ReceptionOverflowStrategy_Type;



typedef struct {
    uint32 CsmJobId;
}Csm_JobType;







typedef enum {
    SECOC_IFPDU,    /* SECOC_IFPDU Interface communication API */
    SECOC_TPPDU,    /* SECOC_TPPDU Transport Protocol communication API */
} SecOC_PduType_Type;


typedef struct 
{
   SecOC_PduCollection_Type   Type;
   uint16                     CollectionId;
   uint16                     AuthId;
   uint16                     CryptoId;
   uint8                      status;
} SecOC_PduCollection;



typedef enum {
    SECOC_CFUNC,
    SECOC_RTE,
} SecOC_QueryFreshnessValue_Type;


typedef enum       /* SecOC status*/
{
    SECOC_UNINIT,   /* SecOC uninitialized*/
    SECOC_INIT      /* SecOC initialized*/
}SecOC_StateType;

typedef struct 
{
	uint16 vendorID;
	uint16 moduleID;
	uint8 sw_major_version;
	uint8 sw_minor_version;
	uint8 sw_patch_version;
}Std_VersionInfoType;

#define STD_ON 0x01u
#define STD_OFF 0x00u

#endif