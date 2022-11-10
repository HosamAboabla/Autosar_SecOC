#ifndef INCLUDE_SECOC_TYPES_H_
#define INCLUDE_SECOC_TYPES_H_

#include "ComStack_Types.h"

typedef enum
{
	BOTH = 0,
	FAILURE_ONLY,
	NONE
}SecOC_ClientServerVerificationStatusPropagationMode_Type;

typedef enum
{
	QUEUE = 0,
	REJECT,
	REPLACE
}SecOC_ReceptionOverflowStrategy_Type;

typedef enum
{
	BOTH = 0,
	FAILURE_ONLY,
	NONE
}SecOC_VerificationStatusPropagationMode_Type;

typedef enum
{
	SECOC_IFPDU = 0,
	SECOC_TPPDU
}SecOC_Pdu_Type;

#endif
