#ifndef INCLUDE_SECOC_TYPES_H_
#define INCLUDE_SECOC_TYPES_H_

#include "ComStack_Types.h"

typedef struct EcuC_PduType EcuC_PduType;

typedef enum
{
    SECOC_IFPDU,    // SECOC_IFPDU Interface communication API
    SECOC_TPPDU,    // SECOC_TPPDU Transport Protocol communication API
}SecOC_PduType_Type;

#endif
