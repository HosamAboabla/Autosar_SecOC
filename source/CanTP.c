#include "CanTp.h"
#include "Pdur_CanTP.h"
#include "SecOC.h"
#include <stdio.h>
#include "CanIF.h"
#include "Std_Types.h"
#include "SecOC_Debug.h"

#define CANTP_BUFFER_SIZE       255
#define BUS_LENGTH              8

Std_ReturnType last_pdu;



PduInfoType CanTp_Buffer[CANTP_BUFFER_SIZE];




Std_ReturnType CanTp_Transmit(PduIdType CanTpTxSduId, const PduInfoType* CanTpTxInfoPtr)
{
    CanTp_Buffer[CanTpTxSduId] = *CanTpTxInfoPtr;
}



void CanTp_MainFunction(void)
{
    PduIdType idx;
    uint8 result;
    uint8 sdata[BUS_LENGTH] = {0};
    uint8 mdata[BUS_LENGTH] = {0};
    PduLengthType length = BUS_LENGTH;
    PduInfoType info = {sdata,mdata,length};

    TpDataStateType retrystate = TP_DATACONF;
    PduLengthType retrycout = BUS_LENGTH;
    RetryInfoType retry = {retrystate,retrycout};
    PduLengthType availableDataPtr = 0;
    #ifdef SECOC_DEBUG
        printf("###### In tp main Function Strat ######\n");
        printf("\n");
    #endif
    for(idx = 0 ; idx < CANTP_BUFFER_SIZE ; idx++)
    {
        if( CanTp_Buffer[idx].SduLength > 0)
        {
            #ifdef SECOC_DEBUG
            printf("Start sending id = %d\n" , idx);
            printf("PDU length = %d\n" , CanTp_Buffer[idx].SduLength);
            
            
            printf("All Data to be Sent: \n");
            for(int i = 0 ; i < CanTp_Buffer[idx].SduLength; i++)
            {
                printf("%d  " , CanTp_Buffer[idx].SduDataPtr[i]);
            }
            printf("\n\n\n");
            #endif

            for(int i = 0; i < (CanTp_Buffer[idx].SduLength / BUS_LENGTH) ; i++)
            {
                // Request CopyTxData
                result = SecOC_CopyTxData(idx, &info, &retry, &availableDataPtr);

                CanIf_Transmit(idx , &info);


                // Send data using CanIf
                // printf("CopyTX Result %d\n", result);
                // printf("Sending %d part with length %d \n" , i, info.SduLength);

                // for(int j = 0; j < info.SduLength; j++)
                //     printf("%d\t",info.SduDataPtr[j]);
                
                // printf("\n");
                
                
                
                if(last_pdu == E_NOT_OK)
                {
                    retry.TpDataState = TP_DATARETRY;
                    i--;
                }
                else if(last_pdu == E_OK)
                {
                    retry.TpDataState = TP_DATACONF;
                }
                #ifdef SECOC_DEBUG
                    printf("Transmit Result = %d\n" , last_pdu);
                #endif
            }

            if( (CanTp_Buffer[idx].SduLength % BUS_LENGTH) != 0)
            {
                // Request CopyTxData with length (CanTp_Buffer[idx].SduLength % BUS_LENGTH) 
                info.SduLength = (CanTp_Buffer[idx].SduLength % BUS_LENGTH);
                SecOC_CopyTxData(idx, &info, NULL, &availableDataPtr);

                #ifdef SECOC_DEBUG
                    printf("Sending remaider part with length %d \n", info.SduLength);
                    for(int j = 0; j < info.SduLength; j++)
                        printf("%d\t",info.SduDataPtr[j]);
                    printf("\n");
                #endif
                

                // Send data using CanIf
                CanIf_Transmit(idx , &info);

                while(last_pdu == E_NOT_OK)
                {
                    retry.TxTpDataCnt = (CanTp_Buffer[idx].SduLength % BUS_LENGTH);
                    retry.TpDataState = TP_DATARETRY;
                    SecOC_CopyTxData(idx, &info, NULL, &availableDataPtr);
                    CanIf_Transmit(idx , &info);
                }
                retry.TpDataState = TP_DATACONF;
                #ifdef SECOC_DEBUG
                    printf("Transmit Result = %d\n" , last_pdu);
                #endif
            }

            PduR_CanTpTxConfirmation(idx , E_OK);

        }
    }
}



void CanTp_TxConfirmation(PduIdType TxPduId, Std_ReturnType result)
{
    last_pdu = result;
}