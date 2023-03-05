#include "SecOC.h"
#include "SecOC_Cfg.h"
#include "Pdur_CanTP.h"
#include "CanTP.h"

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
    
    PduInfoType TP_PDU;
    uint8 Meta_data = 0;
    /* Here i recieve data */
    uint8 ReciveDATA[TP_LENGTH];
    TP_PDU.SduDataPtr = ReciveDATA;
    TP_PDU.MetaDataPtr = &Meta_data;
    TP_PDU.SduLength = TP_LENGTH;
    PduLengthType TP_length = 20;
    PduLengthType bufferSizePtr;
    
    BufReq_ReturnType Result;
    for(idx = 0; idx < SECOC_NUM_OF_RX_PDU_PROCESSING; idx++)
    {  
        ethernet_receive(ReciveDATA, TP_LENGTH);
        /* Check if can Receive  */
        if (PduR_CanTpStartOfReception(idx, &TP_PDU,TP_length, &bufferSizePtr) == BUFREQ_OK)
        {
            /* send Data */
           for(int i = 0; i < TP_length/TP_LENGTH; i++)
           {
                Result = PduR_CanTpCopyRxData(idx, &TP_PDU, &bufferSizePtr);
                if( Result == BUFREQ_OK)
                {
                    TP_PDU.SduDataPtr += TP_LENGTH;
                    ethernet_receive(ReciveDATA, TP_LENGTH);
                }
                else
                {
                    break;
                }
           }

           if(Result != BUFREQ_OK)
               continue;

           if(TP_length % TP_LENGTH != 0)
           {
                TP_PDU.SduLength = TP_length % TP_LENGTH;
                Result = PduR_CanTpCopyRxData(idx, &TP_PDU, &bufferSizePtr);
           }
           /* Send Confirm to last of data */
           PduR_CanTpRxIndication(idx,Result);
        }
        
    }
}