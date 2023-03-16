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

void ComMainTx(void)
{
	PduIdType id;
	uint8 buff[20];
	PduInfoType SPDU;
	printf("enter   0:Direct    1:TP    --> \n");
	scanf("%d", &id);
 	if(id == 1)
	{
		#ifdef COM_DEBUG
    	printf("############### Send tp ###############\n");
    	#endif
		PduLengthType len = 16;
		printf("data to send must be %d : ", len);
		for(int i = 0; i < len; i++)
		{
			scanf("%d", &buff[i]);
		}
		uint8 test_meta_data = 2;
		SPDU.MetaDataPtr = &test_meta_data;
    	SPDU.SduDataPtr = buff;
    	SPDU.SduLength = len;
		PduR_ComTransmit(id,&SPDU);
	}
	else if(id == 0)
	{
		printf("############### Send Direct ###############\n");
		PduLengthType len = 2;
		printf("data to send must be %d : ", len);
		for(int i = 0; i < len; i++)
		{
			scanf("%d", &buff[i]);
		}
		PduInfoType SPDU;
		uint8 test_meta_data = 0;
		SPDU.MetaDataPtr = &test_meta_data;
    	SPDU.SduDataPtr = buff;
    	SPDU.SduLength = len;
		PduR_ComTransmit(id,&SPDU);
	}

}