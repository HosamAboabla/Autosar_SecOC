#include "Com.h"
#include "PduR_Com.h"
#include "Std_Types.h"


Std_ReturnType success_flag =0;//check if the message reached the distination or not

 void Com_TxConfirmation(PduIdType TxPduId, Std_ReturnType result)
 {
	if(success_flag)
    {
		result = E_OK;	
	}else{
		result = E_NOT_OK;
	}
}


void Com_RxIndication(PduIdType RxPduId, const PduInfoType* PduInfoPtr)
{
	
}