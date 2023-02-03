#include "Dcm.h"
#include <stdio.h>

void Dcm_TpTxConfirmation(PduIdType TxPduId, Std_ReturnType result)
{
    if( result == E_OK )
	{
		printf("Result for %d is E_OK\n" , TxPduId);
	}
	else
	{
		printf("Result for %d is E_NOT_OK\n" , TxPduId);
	}
}