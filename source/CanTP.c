#include "SecOC.h"
#include "Pdur_CanTP.h"
#include "CanTP.h"

PduInfoType CanTP_Buffer[BUFFER_SIZE];


void CanTP_MainFunctionRx(void)
{
    PduIdType idx = 0;
    
    PduInfoType TP_PDU;
    uint8 Meta_data = 0;
    TP_PDU.MetaDataPtr = &Meta_data;
    TP_PDU.SduLength = 4;
    PduLengthType TP_length = 100;
    PduLengthType bufferSizePtr;

    BufReq_ReturnType Result;
    
    PduR_CanTpStartOfReception(idx, &TP_PDU,TP_length, &bufferSizePtr);

    for( idx = 0; idx < BUFFER_SIZE; idx++)
    {
        for(int i=0; i < TP_length/TP_LENGTH; i++)
        {
            Result = PduR_CanTpCopyRxData(idx, &TP_PDU, &bufferSizePtr);
            if( Result != BUFREQ_OK)
                break;
        }

        if( Result != BUFREQ_OK)
            continue;
        
        if(CanTP_Buffer[idx].SduLength % TP_LENGTH !=0)
        {
            Result = PduR_CanTpCopyRxData(idx, &TP_PDU, &bufferSizePtr);
        }
    }
    //PduR_CanTpRxIndication(idx,Result);
}