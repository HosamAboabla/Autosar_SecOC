#include "CanTP.h"
#include "Pdur_CanTP.h"
#include "SecOC.h"
#include "CanIF.h"
#include "Std_Types.h"
#include "SecOC_Debug.h"
#include "SecOC_Cfg.h"


#ifdef LINUX
#include "ethernet.h"
#endif


Std_ReturnType last_pdu;



PduInfoType CanTp_Buffer[CANTP_BUFFER_SIZE];




Std_ReturnType CanTp_Transmit(PduIdType CanTpTxSduId, const PduInfoType* CanTpTxInfoPtr)
{
    #ifdef CANTP_DEBUG
        printf("######## in CanTp_Transmit\n");
    #endif
    CanTp_Buffer[CanTpTxSduId] = *CanTpTxInfoPtr;
}


void CanTp_RxIndication (PduIdType RxPduId, const PduInfoType* PduInfoPtr)
{
    #ifdef CANTP_DEBUG
        printf("######## in CanTp_RxIndication\n");
    #endif
    (void)memcpy(CanTp_Buffer_Rx[RxPduId] + CanTp_Buffer_Rx_index[RxPduId], PduInfoPtr->SduDataPtr, PduInfoPtr->SduLength) ;
    CanTp_Buffer_Rx_index[RxPduId] += PduInfoPtr->SduLength;
}



void CanTp_MainFunction(void)
{
    #ifdef CANTP_DEBUG
        printf("######## in CanTp_MainFunction\n");
    #endif
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
    for(idx = 0 ; idx < CANTP_BUFFER_SIZE ; idx++)
    {
        if( CanTp_Buffer[idx].SduLength > 0)
        {
            #ifdef CANTP_DEBUG
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

                #ifdef CANTP_DEBUG
                    printf("Delay...\n");
                #endif
                long long int delay = 60000000;
                while(delay--);

                
                if(last_pdu == E_NOT_OK)
                {
                    retry.TpDataState = TP_DATARETRY;
                    i--;
                }
                else if(last_pdu == E_OK)
                {
                    retry.TpDataState = TP_DATACONF;
                }
                #ifdef CANTP_DEBUG
                    printf("Transmit Result = %d\n" , last_pdu);
                #endif
            }

            if( (CanTp_Buffer[idx].SduLength % BUS_LENGTH) != 0)
            {
                // Request CopyTxData with length (CanTp_Buffer[idx].SduLength % BUS_LENGTH) 
                info.SduLength = (CanTp_Buffer[idx].SduLength % BUS_LENGTH);
                SecOC_CopyTxData(idx, &info, NULL, &availableDataPtr);

                #ifdef CANTP_DEBUG
                    printf("Sending remaider part with length %d \n", info.SduLength);
                    for(int j = 0; j < info.SduLength; j++)
                        printf("%d\t",info.SduDataPtr[j]);
                    printf("\n");
                #endif
                

                // Send data using CanIf
                CanIf_Transmit(idx , &info);
                printf("Delay...\n");
                long long int delay = 60000000;
                while(delay--);

                while(last_pdu == E_NOT_OK)
                {
                    retry.TxTpDataCnt = (CanTp_Buffer[idx].SduLength % BUS_LENGTH);
                    retry.TpDataState = TP_DATARETRY;
                    SecOC_CopyTxData(idx, &info, NULL, &availableDataPtr);
                    CanIf_Transmit(idx , &info);
                }
                retry.TpDataState = TP_DATACONF;
                #ifdef CANTP_DEBUG
                    printf("Transmit Result = %d\n" , last_pdu);
                #endif
            }

            PduR_CanTpTxConfirmation(idx , E_OK);

        }
    }
}



void CanTp_TxConfirmation(PduIdType TxPduId, Std_ReturnType result)
{
    #ifdef CANTP_DEBUG
        printf("######## in CanTp_TxConfirmation \n");
    #endif
    last_pdu = result;
}

void CanTP_MainFunctionRx(void)
{
    #ifdef CANTP_DEBUG
        printf("######## in CanTP_MainFunctionRx\n");
    #endif
    PduIdType idx = 0;
    
    PduInfoType Tp_Spdu;
    uint8 Meta_data = 0;
    /* Here i recieve data */
    uint8 ReciveDATA[BUS_LENGTH];
    Tp_Spdu.SduDataPtr = ReciveDATA;
    Tp_Spdu.MetaDataPtr = &Meta_data;
    Tp_Spdu.SduLength = BUS_LENGTH;

    PduLengthType TpSduLength = 24; // SECOC_SECPDU_MAX_LENGTH;
    PduLengthType bufferSizePtr;
    uint8 LastFrame_idx = (TpSduLength/BUS_LENGTH)  - 1;
    if( (TpSduLength % BUS_LENGTH) != 0 )
    {
        LastFrame_idx ++;
    }

    #ifdef CANTP_DEBUG
        printf("######## in main tp Rx  in id : %d\n", idx);
    #endif
    BufReq_ReturnType Result;

    #ifdef LINUX
    ethernet_receive(Tp_Spdu.SduDataPtr, Tp_Spdu.SduLength,&idx);
    #endif
    /* Check if can Receive  */
    BufReq_ReturnType result= PduR_CanTpStartOfReception(idx, &Tp_Spdu,TpSduLength, &bufferSizePtr);
    if (result == BUFREQ_OK)
    {
        /* send Data */
        for(int i = 0; i <= LastFrame_idx; i++)
        {
            #ifdef CANTP_DEBUG
            printf("Info Received idx=%d: \n",i);
            for(int j  = 0 ; j < Tp_Spdu.SduLength ; j++)
            {
                printf("%d ",Tp_Spdu.SduDataPtr[j]);
            }
            printf("\n\n\n");
            #endif
            Result = PduR_CanTpCopyRxData(idx, &Tp_Spdu, &bufferSizePtr);
            if( Result != BUFREQ_OK)
            {
                break;
            }
            
            /* Update length before last frame */
            if( ((TpSduLength % BUS_LENGTH) != 0) && (i == (LastFrame_idx - 1)) )
            {
                Tp_Spdu.SduLength = TpSduLength % BUS_LENGTH;
            }

            if(i != LastFrame_idx)
            {
                #ifdef LINUX
                ethernet_receive(Tp_Spdu.SduDataPtr, Tp_Spdu.SduLength,&idx);
                #endif
            }
        }
        
        /* Send Confirm to last of data */
        PduR_CanTpRxIndication(idx,Result);
    }  
}