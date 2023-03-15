#include "Com.h"
#include "PduR_Com.h"
#include "Std_Types.h"

#include "SecOC_Debug.h"

 void Com_TxConfirmation(PduIdType TxPduId, Std_ReturnType result)
 {
	#ifdef COM_DEBUG
        printf("######## in Com_TxConfirmation \n");
    #endif
	if( result == E_OK )
	{
		#ifdef COM_DEBUG
		printf("Returned confirmation 'E_OK' \n");
		#endif
	}
	else
	{
		#ifdef COM_DEBUG
		printf("Returned confirmation 'E_NOT_OK' \n");
		#endif
	}
}


void Com_RxIndication(PduIdType RxPduId, const PduInfoType* PduInfoPtr)
{
	#ifdef COM_DEBUG
    printf("######## in Com_RxIndication\n");
	printf("Data Recieve in Com : ");
	for(uint8 i = 0; i < PduInfoPtr->SduLength; i++)
	{
		printf("%d ",PduInfoPtr->SduDataPtr[i]);
	}
	printf("\n");
    #endif
	
}