#include "Com.h"
#include "PduR_Com.h"
#include "Std_Types.h"
#include <stdio.h>

Std_ReturnType success_flag =0;//check if the message reached the distination or not

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

	if(success_flag)
    {
		result = E_OK;	
	}else{
		result = E_NOT_OK;
	}
}


void Com_RxIndication(PduIdType RxPduId, const PduInfoType* PduInfoPtr)
{
	printf("Data Recieve in Com : ");
	for(uint8 i = 0; i < PduInfoPtr->SduLength; i++)
	{
		printf("%d ",PduInfoPtr->SduDataPtr[i]);
	}
	printf("\n");
}