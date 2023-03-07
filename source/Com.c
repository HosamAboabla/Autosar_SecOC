#include "Com.h"
#include "PduR_Com.h"
#include "Std_Types.h"
#include <stdio.h>

 void Com_TxConfirmation(PduIdType TxPduId, Std_ReturnType result)
 {
	if( result == E_OK )
	{
		printf("Returned confirmation 'E_OK' \n");
	}
	else
	{
		printf("Returned confirmation 'E_NOT_OK' \n");
	}
}


void Com_RxIndication(PduIdType RxPduId, const PduInfoType* PduInfoPtr)
{
	
}