#ifndef INCLUDE_SECOC_TYPES_H_
#define INCLUDE_SECOC_TYPES_H_

#include "ComStack_Types.h"

typedef enum
{
	BOTH,
	FAILURE_ONLY,
	NONE
}SecOCClientServerVerificationStatusPropagationModeType;

typedef enum
{
	QUEUE,
	REJECT,
	REPLACE
}SecOCReceptionOverflowStrategyType;

typedef enum
{
	BOTH,
	FAILURE_ONLY,
	NONE
}SecOCVerificationStatusPropagationModeType;

typedef enum
{
	SECOC_IFPDU,
	SECOC_TPPDU
}SecOCPdu_type;

#endif
