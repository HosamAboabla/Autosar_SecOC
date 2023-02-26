#include "SecOC.h"
#include "Pdur_CanTP.h"
#include "CanTP.h"

PduInfoType CanTP_Buffer[BUFFER_SIZE];


void CanTP_MainFunctionRx(void)
{
    PduIdType idx = 0;
    
    PduInfoType TP_PDU;
    uint8 Meta_data = 0;
    /* Here i recieve data */
    uint8 ReciveDATA[] = {11,22,33,44,55,66,77,88,99,111,122,133,144,155,166};
    TP_PDU.SduDataPtr = ReciveDATA;
    TP_PDU.MetaDataPtr = &Meta_data;
    TP_PDU.SduLength = 4;
    PduLengthType TP_length = 15;
    PduLengthType bufferSizePtr;

    BufReq_ReturnType Result;
    for(idx = 0; idx < SECOC_NUM_OF_RX_PDU_PROCESSING; idx++)
    {  
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