#include "Com.h"
#include "PduR_Com.h"
#include "Std_Types.h"
#include<stdio.h>
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
		printf("%c ",PduInfoPtr->SduDataPtr[i]);
	}
	printf("\n");
    #endif
	
}

void Com_MainTx(void)
{
	#ifdef COM_DEBUG
	printf("######## in Com_MainTx\n");
	#endif
	PduIdType id;
	uint8 buff[20] = {0};
	PduInfoType SPDU;
	PduLengthType len = 16;
	printf("Enter data : ");
	fgets(buff, 20, stdin);
	len = strlen(buff) - 1;
	for(int i = 0; i < len; i++)
	{
		printf("%d ", buff[i]);

	}
	printf("\n");
	if (len <= 2)
	{
		printf("############### Send Direct ###############\n");
		PduInfoType SPDU;
		uint8 test_meta_data = 0;
		SPDU.MetaDataPtr = &test_meta_data;
    	SPDU.SduDataPtr = buff;
    	SPDU.SduLength = len;
		PduR_ComTransmit(0,&SPDU);
	}
	else
	{
		#ifdef COM_DEBUG
    		printf("############### Send tp ###############\n");
    	#endif
		uint8 test_meta_data = 2;
		SPDU.MetaDataPtr = &test_meta_data;
    	SPDU.SduDataPtr = buff;
    	SPDU.SduLength = len;
		PduR_ComTransmit(1,&SPDU);
	}

}