#include "SecOC.h"
#include "SecOC_Cfg.h"
#include "Pdur_CanTP.h"
#include "CanTP.h"
#include <math.h>

#ifdef LINUX
#include "ethernet.h"
#endif

PduInfoType CanTP_Buffer[BUFFER_SIZE];

Std_ReturnType CanTp_Transmit(PduIdType TxPduId,const PduInfoType* PduInfoPtr)
{
    Std_ReturnType result = E_OK;
    
    #ifdef LINUX
    result = ethernet_send(PduInfoPtr->SduDataPtr , PduInfoPtr->SduLength);
    #endif

    return result;
}

void CanTP_MainFunctionRx(void)
{
    PduIdType idx = 0;
    
    PduInfoType Tp_Spdu;
    uint8 Meta_data = 0;
    /* Here i recieve data */
    uint8 ReciveDATA[BUS_LENGTH];
    Tp_Spdu.SduDataPtr = ReciveDATA;
    Tp_Spdu.MetaDataPtr = &Meta_data;
    Tp_Spdu.SduLength = BUS_LENGTH;
    PduLengthType TpSduLength = SECOC_SECPDU_MAX_LENGTH;
    PduLengthType bufferSizePtr;
    
    BufReq_ReturnType Result;
    for(idx = 0; idx < SECOC_NUM_OF_RX_PDU_PROCESSING; idx++)
    {  
        ethernet_receive(Tp_Spdu.SduDataPtr, Tp_Spdu.SduLength);
        /* Check if can Receive  */
        if (PduR_CanTpStartOfReception(idx, &Tp_Spdu,TpSduLength, &bufferSizePtr) == BUFREQ_OK)
        {
            uint8 LastFrame = ceil((float32)TpSduLength/BUS_LENGTH);
            /* send Data */
           for(int i = 0; i < LastFrame; i++)
           {
                Result = PduR_CanTpCopyRxData(idx, &Tp_Spdu, &bufferSizePtr);
                if( Result != BUFREQ_OK)
                {
                    break;
                }
                if(((TpSduLength % BUS_LENGTH != 0) && (i == LastFrame - 1)))
                {
                    Tp_Spdu.SduLength = TpSduLength % BUS_LENGTH;
                }
                ethernet_receive(Tp_Spdu.SduDataPtr, Tp_Spdu.SduLength);
           }
           /* Send Confirm to last of data */
           PduR_CanTpRxIndication(idx,Result);
        }  
    }
}