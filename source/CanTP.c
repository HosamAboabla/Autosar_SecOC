#include "CanTP.h"
#include "Pdur_CanTP.h"
#include "SecOC.h"
#include "CanIF.h"
#include "Std_Types.h"
#include "SecOC_Debug.h"
#include "SecOC_Cfg.h"
#include "SecOC_Lcfg.h"

#ifdef LINUX
#include "ethernet.h"
#endif


Std_ReturnType last_pdu;

extern const SecOC_RxPduProcessingType     *SecOCRxPduProcessing;


PduInfoType CanTp_Buffer[SECOC_NUM_OF_TX_PDU_PROCESSING];
static uint8 CanTp_Buffer_Rx[SECOC_NUM_OF_RX_PDU_PROCESSING][CANTP_BUFFER_SIZE];
static uint8 CanTp_Buffer_Rx_index[SECOC_NUM_OF_RX_PDU_PROCESSING] = {0};
static uint32 CanTp_SduLength_conf[SECOC_NUM_OF_RX_PDU_PROCESSING] = {0};

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
    uint8 AuthHeadlen = SecOCRxPduProcessing[RxPduId].SecOCRxSecuredPduLayer->SecOCRxSecuredPdu->SecOCAuthPduHeaderLength;
    (void)memcpy(CanTp_Buffer_Rx[RxPduId] + CanTp_Buffer_Rx_index[RxPduId], PduInfoPtr->SduDataPtr, PduInfoPtr->SduLength) ;
    
    if(CanTp_Buffer_Rx_index[RxPduId] == 0)
    {
        if(AuthHeadlen > 0)
        {
            printf("header len is %d",AuthHeadlen);
            memcpy((uint8*)&CanTp_SduLength_conf[RxPduId], PduInfoPtr->SduDataPtr, AuthHeadlen );
            printf(" - %d\n",CanTp_SduLength_conf[RxPduId]);
        }
        else
        {
            CanTp_SduLength_conf[RxPduId] = SecOCRxPduProcessing[RxPduId].SecOCRxAuthenticPduLayer->SecOCRxAuthenticLayerPduRef.SduLength;
        }
    }
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
    for(idx = 0 ; idx < SECOC_NUM_OF_TX_PDU_PROCESSING ; idx++)
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
            /* clear buffer */
            CanTp_Buffer[idx].SduLength = 0;
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

    PduInfoType Tp_Spdu;
    uint8 Meta_data = 1;
    /* Here i recieve data */
     // SECOC_SECPDU_MAX_LENGTH;
    PduLengthType bufferSizePtr;
    for(PduIdType RxPduId = 0 ; RxPduId < SECOC_NUM_OF_RX_PDU_PROCESSING ; RxPduId++)
    {
        PduLengthType TpSduLength = CanTp_SduLength_conf[RxPduId] + BIT_TO_BYTES(SecOCRxPduProcessing[RxPduId].SecOCFreshnessValueTruncLength) + 5;
        printf("for id %d that sdulen =  %d ,and in buffer is %d\n", RxPduId,TpSduLength,CanTp_Buffer_Rx_index[RxPduId]);
        if((CanTp_Buffer_Rx_index[RxPduId] >= TpSduLength))
        {
            uint8 LastFrame_idx = (TpSduLength/BUS_LENGTH);
            Tp_Spdu.SduDataPtr = CanTp_Buffer_Rx[RxPduId];
            Tp_Spdu.MetaDataPtr = &Meta_data;
            Tp_Spdu.SduLength = BUS_LENGTH;
            #ifdef CANTP_DEBUG
                printf("######## in main tp Rx  in id : %d\n", RxPduId);
                printf("for id %d :",RxPduId);
                for(int l = 0; l < TpSduLength; l++)
                {
                    printf("%d ", CanTp_Buffer_Rx[RxPduId][l]);
                }
                printf("\n");
            #endif

            BufReq_ReturnType result= PduR_CanTpStartOfReception(RxPduId, &Tp_Spdu,TpSduLength, &bufferSizePtr);
            /* Check if can Receive  */
            if (result == BUFREQ_OK)
            {
                /* send Data */
                for(int i = 0; i < LastFrame_idx; i++)
                {
                    #ifdef CANTP_DEBUG
                    printf("Info Received idx=%d: \n",i);
                    for(int j  = 0 ; j < Tp_Spdu.SduLength ; j++)
                    {
                        printf("%d ",Tp_Spdu.SduDataPtr[j]);
                    }
                    printf("\n\n\n");
                    #endif
                    result = PduR_CanTpCopyRxData(RxPduId, &Tp_Spdu, &bufferSizePtr);
                    if( result != BUFREQ_OK)
                    {
                        break;
                    }
                    Tp_Spdu.SduDataPtr += BUS_LENGTH;
                }
                /* Update length before last frame */
                if( ((TpSduLength % BUS_LENGTH) != 0))
                {
                    Tp_Spdu.SduLength = TpSduLength % BUS_LENGTH;
                    PduR_CanTpCopyRxData(RxPduId, &Tp_Spdu, &bufferSizePtr);
                }

                /* Send Confirm to last of data */
                PduR_CanTpRxIndication(RxPduId,result);
                CanTp_Buffer_Rx_index[RxPduId] = 0;
            }
            else
            {
                CanTp_Buffer_Rx_index[RxPduId] = 0;
            }  
        }
    }

    
}