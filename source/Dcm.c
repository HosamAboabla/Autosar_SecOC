#include "Dcm.h"
#include "SecOC_Debug.h"
void Dcm_TpTxConfirmation(PduIdType TxPduId, Std_ReturnType result)
{
	#ifdef DCM_DEBUG
        printf("######## in Dcm_TpTxConfirmation\n");
    #endif
    if( result == E_OK )
	{
		#ifdef DCM_DEBUG
		printf("DCM recevied data with status E_OK\n");
		#endif
	}
	else
	{
		#ifdef DCM_DEBUG
		printf("DCM recevied data with status E_NOT_OK\n");
		#endif
	}
}