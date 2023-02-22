#include "CanTp.h"
#include "Pdur_CanTP.h"


#define CANTP_BUFFER_SIZE       255


#define BUS_LENGTH              8

PduInfoType CanTp_Buffer[CANTP_BUFFER_SIZE];




Std_ReturnType CanTp_Transmit(PduIdType CanTpTxSduId, const PduInfoType* CanTpTxInfoPtr)
{
    CanTp_Buffer[CanTpTxSduId] = *CanTpTxInfoPtr;
}



void CanTp_MainFunction(void)
{
    PduIdType idx;

    uint8 sdata[BUS_LENGTH] = {0};
    uint8 mdata[BUS_LENGTH] = {0};
    PduLengthType length = BUS_LENGTH;
    PduInfoType info = {sdata,mdata,length};

    TpDataStateType retrystate = TP_DATACONF;
    PduLengthType retrycout = 0;
    RetryInfoType retry = {retrystate,retrycout};
    PduLengthType availableDataPtr = 0;

    for(idx = 0 ; idx < CANTP_BUFFER_SIZE ; idx++)
    {
        if( CanTp_Buffer[idx].SduLength > 0)
        {
            
            for(int i = 0; i < (CanTp_Buffer[idx].SduLength / BUS_LENGTH) ; i++)
            {
                // Request CopyTxData
                // SecOC_CopyTxData(idx, &info, NULL, &availableDataPtr);
                // Send data using CanIf
                // CanIf_Transmit(idx , &info);
            }

            if( (CanTp_Buffer[idx].SduLength % BUS_LENGTH) != 0)
            {
                // Request CopyTxData with length (CanTp_Buffer[idx].SduLength % BUS_LENGTH) 
                // info.SduLength = (CanTp_Buffer[idx].SduLength % BUS_LENGTH);
                // SecOC_CopyTxData(idx, &info, NULL, &availableDataPtr);
                // Send data using CanIf
                // CanIf_Transmit(idx , &info);
                
            }

            // PduR_CanTpTxConfirmation(idx , result);

        }
    }
}