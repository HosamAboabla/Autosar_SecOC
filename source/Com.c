#include "Com.h"
#include "PduR_Com.h"
#include "Std_Types.h"
#include <stdio.h>
#include "SecOC_Debug.h"

 void Com_TxConfirmation(PduIdType TxPduId, Std_ReturnType result)
 {
	if( result == E_OK )
	{
		#ifdef SECOC_DEBUG
		printf("Returned confirmation 'E_OK' \n");
		#endif
	}
	else
	{
		printf("Returned confirmation 'E_NOT_OK' \n");
	}
}


void Com_RxIndication(PduIdType RxPduId, const PduInfoType* PduInfoPtr)
{
	
}