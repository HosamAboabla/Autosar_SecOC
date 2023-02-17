/* "Copyright [2022/2023] <Tanta University>" */
#ifndef INCLUDE_RTE_SECOC_TYPE_H_
#define INCLUDE_RTE_SECOC_TYPE_H_

#include "Std_Types.h"
#include "FVM.h"

#define SECOC_MAX_FRESHNESS_SIZE 32

typedef uint8                 SecOC_FreshnessArrayType[SECOC_MAX_FRESHNESS_SIZE];

typedef Std_ReturnType(*SecOC_GetTxFreshnessCalloutType)(uint16 , uint8* , uint32*);
#define GET_TXFRESHNESS_CALLBACK_PTR FVM_GetTxFreshness

#endif /* INCLUDE_RTE_SECOC_TYPE_H_ */
