#ifndef INCLUDE_PDUR_SOAD_H_
#define INCLUDE_PDUR_SOAD_H_


/********************************************************************************************************/
/************************************************INCULDES************************************************/
/********************************************************************************************************/

#include"Std_Types.h"
#include"ComStack_Types.h"



/********************************************************************************************************/
/*****************************************FunctionPrototype**********************************************/
/********************************************************************************************************/

void PduR_SoAdIfTxConfirmation(PduIdType TxPduId, Std_ReturnType result);
void PduR_SoAdIfRxIndication(PduIdType RxPduId, const PduInfoType* PduInfoPtr);

BufReq_ReturnType PduR_SoAdTpCopyTxData(
    PduIdType id,
    const PduInfoType* info,
    const RetryInfoType* retry,
    PduLengthType* availableDataPtr
     );

void PduR_SoAdTpTxConfirmation(PduIdType TxPduId, Std_ReturnType result);

#endif  // INCLUDE_SOAD_H_