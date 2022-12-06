#ifndef INCLUDE_SECOC_TYPES_H_
#define INCLUDE_SECOC_TYPES_H_

#include "Std_Types.h"
#include "ComStack_Types.h"





typedef enum
{
	SECOC_BOTH = 0,
	SECOC_FAILURE_ONLY,
	SECOC_NONE
}SecOC_StatusPropagationMode_Type;




typedef enum
{
	SECOC_QUEUE = 0,
	SECOC_REJECT,
	SECOC_REPLACE
}SecOC_ReceptionOverflowStrategy_Type;



typedef struct
{
	uint32 CsmJobId;
}Csm_JobType;







typedef enum
{
    SECOC_IFPDU,    /* SECOC_IFPDU Interface communication API */ 
    SECOC_TPPDU,    /* SECOC_TPPDU Transport Protocol communication API */ 
} SecOC_PduType_Type;



typedef enum {
    SECOC_CFUNC,
    SECOC_RTE,
} SecOC_QueryFreshnessValue_Type;


#endif

