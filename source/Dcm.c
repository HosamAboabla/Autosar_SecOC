#include "Dcm.h"
#include <stdio.h>

void Dcm_TpTxConfirmation(PduIdType TxPduId, Std_ReturnType result)
{
    if( result == E_OK )
	{
		printf("DCM recevied data with status E_OK\n");
	}
	else
	{
		printf("DCM recevied data with status E_NOT_OK\n");
		
	}
}