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
static PduInfoType CanTp_Buffer_Rx[SECOC_NUM_OF_RX_PDU_PROCESSING];
static uint8 CanTp_Recieve_Counter[SECOC_NUM_OF_RX_PDU_PROCESSING] = {0};
static PduLengthType CanTp_secureLength_Recieve[SECOC_NUM_OF_RX_PDU_PROCESSING] = {0};

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
    /* copy to CanTp buffer */
    CanTp_Buffer_Rx[RxPduId] = *PduInfoPtr;
    
    /* Check if it first frame :
        Check if there are a header of no 
            if there are a header 
                get the auth length from the frame
            else 
                get the config length of data
        then add the Freshness , Mac and Header length 
        to the the whole Secure Frame Length to recieve
    */
    if(CanTp_Recieve_Counter[RxPduId] == 0)
    {
        uint8 AuthHeadlen = SecOCRxPduProcessing[RxPduId].SecOCRxSecuredPduLayer->SecOCRxSecuredPdu->SecOCAuthPduHeaderLength;
        PduLengthType SecureDataframe = AuthHeadlen + BIT_TO_BYTES(SecOCRxPduProcessing[RxPduId].SecOCFreshnessValueTruncLength) + BIT_TO_BYTES(SecOCRxPduProcessing[RxPduId].SecOCAuthInfoTruncLength);
        if(AuthHeadlen > 0)
        {
            (void)memcpy((uint8*)&CanTp_secureLength_Recieve[RxPduId], PduInfoPtr->SduDataPtr, AuthHeadlen );
        }
        else
        {
            CanTp_secureLength_Recieve[RxPduId] = SecOCRxPduProcessing[RxPduId].SecOCRxAuthenticPduLayer->SecOCRxAuthenticLayerPduRef.SduLength;
        }
        CanTp_secureLength_Recieve[RxPduId] += SecureDataframe;
    }
    CanTp_Recieve_Counter[RxPduId] ++;
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
                #ifdef CANTP_DEBUG
                printf("Delay...\n");
                #endif
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
    
    // SECOC_SECPDU_MAX_LENGTH;
    
    for(PduIdType RxPduId = 0 ; RxPduId < SECOC_NUM_OF_RX_PDU_PROCESSING ; RxPduId++)
    {
        /*
        Check there are a recieved frame for every RxPdu
        if it recieved and there are a data in the buffer
            before the first frame -> Send Start Of reception and wait for thre result
            after the last frame -> send the Rx indication 
            all frames must be send to copyRx
        else
            do nothing
        */
        BufReq_ReturnType result = BUFREQ_OK;
        if((CanTp_Recieve_Counter[RxPduId] > 0) && (CanTp_Buffer_Rx[RxPduId].SduLength > 0))
        {
            uint8 lastFrameIndex = (CanTp_secureLength_Recieve[RxPduId] % BUS_LENGTH == 0)  ? (CanTp_secureLength_Recieve[RxPduId] / BUS_LENGTH) : ((CanTp_secureLength_Recieve[RxPduId] / BUS_LENGTH) + 1);
            PduLengthType bufferSizePtr;
            #ifdef CANTP_DEBUG
                printf("######## in main tp Rx  in id : %d\n", RxPduId);
                printf("for id %d :",RxPduId);
                for(int l = 0; l < CanTp_Buffer_Rx[RxPduId].SduLength; l++)
                {
                    printf("%d ", CanTp_Buffer_Rx[RxPduId].SduDataPtr[l]);
                }
                printf("\n");
            #endif
            if(CanTp_Recieve_Counter[RxPduId] == 1)
            {
                result = PduR_CanTpStartOfReception(RxPduId, &CanTp_Buffer_Rx[RxPduId], CanTp_secureLength_Recieve[RxPduId], &bufferSizePtr);
                if (result == BUFREQ_OK)
                {
                    result = PduR_CanTpCopyRxData(RxPduId, &CanTp_Buffer_Rx[RxPduId], &bufferSizePtr);
                }
                else
                {
                    CanTp_Recieve_Counter[RxPduId] = 0;
                }
                CanTp_Buffer_Rx[RxPduId].SduLength = 0;
            }
            else if (CanTp_Recieve_Counter[RxPduId] == lastFrameIndex)
            {
                CanTp_Buffer_Rx[RxPduId].SduLength = (CanTp_secureLength_Recieve[RxPduId] % BUS_LENGTH == 0) ? (BUS_LENGTH) : (CanTp_secureLength_Recieve[RxPduId] % BUS_LENGTH);
                result = PduR_CanTpCopyRxData(RxPduId, &CanTp_Buffer_Rx[RxPduId], &bufferSizePtr);
                PduR_CanTpRxIndication(RxPduId, result);
                CanTp_Recieve_Counter[RxPduId] = 0;
            }
            else
            {
                result = PduR_CanTpCopyRxData(RxPduId, &CanTp_Buffer_Rx[RxPduId], &bufferSizePtr);
            }
        }
    }

    
}