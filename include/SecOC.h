#ifndef INCLUDE_SECOC_H_
#define INCLUDE_SECOC_H_

#include "SecOC_Cfg.h"
#include "SecOC_Types.h"

void SecOC_MainFunctionTx ( void );


Std_ReturnType SecOC_IfTransmit(
    PduIdType                  TxPduId,
    const PduInfoType*         PduInfoPtr
);

void SecOC_TxConfirmation (PduIdType TxPduId,Std_ReturnType result);

void SecOC_Init(const SecOC_ConfigType *config);

typedef struct { //Specific Implementation Data Structure Configuration SecOC Module Data Structure
	const SecOC_GeneralType general;
	const SecOC_TxPduProcessingType* secOCTxPduProcessings;
	const SecOC_RxPduProcessingType* secOCRxPduProcessings;
}SecOC_ConfigType;

typedef enum {   //SecOC status
	SECOC_UNINIT,   //SecOC uninitialized
	SECOC_INIT		//SecOC initialized
}SecOC_StateType;


#endif
