
/********************************************************************************************************/
/************************************************INCULDES************************************************/
/********************************************************************************************************/

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


/********************************************************************************************************/
/******************************************GlobalVaribles************************************************/
/********************************************************************************************************/

extern const SecOC_RxPduProcessingType     *SecOCRxPduProcessing;


static PduInfoType CanTp_Buffer[SECOC_NUM_OF_TX_PDU_PROCESSING];
static PduInfoType CanTp_Buffer_Rx[SECOC_NUM_OF_RX_PDU_PROCESSING];
static uint8 CanTp_Recieve_Counter[SECOC_NUM_OF_RX_PDU_PROCESSING] = {0};
static PduLengthType CanTp_secureLength_Recieve[SECOC_NUM_OF_RX_PDU_PROCESSING] = {0};

/********************************************************************************************************/
/********************************************Functions***************************************************/
/********************************************************************************************************/

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



void CanTp_MainFunctionTx(void)
{
    #ifdef CANTP_DEBUG
        printf("######## in CanTp_MainFunction\n");
    #endif


    uint8 sdata[BUS_LENGTH] = {0};
    uint8 mdata[BUS_LENGTH] = {0};
    PduLengthType length = BUS_LENGTH;
    PduInfoType info = {sdata,mdata,length};

    TpDataStateType retrystate = TP_DATACONF;
    PduLengthType retrycout = BUS_LENGTH;
    RetryInfoType retry = {retrystate,retrycout};

    PduLengthType availableDataPtr = 0;
    for(PduIdType TxPduId = 0 ; TxPduId < SECOC_NUM_OF_TX_PDU_PROCESSING ; TxPduId++)
    {
        /*
        if there is a data to send
            loop to send all frames
                copy data from upper layer
                send it to CANIF
                if result = E_OK
                    continue sending 
                else if NOT_E_OK
                    make retrystate = TP_DATARETRY
            send confirmationc
            clear the buffer
        else
            do nothing
        */
        
        if( CanTp_Buffer[TxPduId].SduLength > 0)
        {
            uint8 lastFrameIndex = (CanTp_Buffer[TxPduId].SduLength % BUS_LENGTH == 0)  ? (CanTp_Buffer[TxPduId].SduLength / BUS_LENGTH) : ((CanTp_Buffer[TxPduId].SduLength / BUS_LENGTH) + 1);
            #ifdef CANTP_DEBUG
                printf("Start sending id = %d\n" , TxPduId);
                printf("PDU length = %ld\n" , CanTp_Buffer[TxPduId].SduLength);       
                printf("All Data to be Sent: \n");
                for(int i = 0 ; i < CanTp_Buffer[TxPduId].SduLength; i++)
                {
                    printf("%d  " , CanTp_Buffer[TxPduId].SduDataPtr[i]);
                }
                printf("\n\n\n");
            #endif
            for(int frameIndex = 0; frameIndex < lastFrameIndex ; frameIndex++)
            {
                if(frameIndex == lastFrameIndex - 1)
                {
                    info.SduLength = (CanTp_Buffer[TxPduId].SduLength % BUS_LENGTH == 0)  ? (BUS_LENGTH) : (CanTp_Buffer[TxPduId].SduLength % BUS_LENGTH);
                    #ifdef CANTP_DEBUG
                    printf("last frame PDU length = %ld\n" , CanTp_Buffer[TxPduId].SduLength);       
                    printf("All Data to be Sent: \n");
                    for(int i = 0 ; i < info.SduLength; i++)
                    {
                        printf("%d  " , info.SduDataPtr[i]);
                    }
                    printf("\n");
                    #endif
                }
                BufReq_ReturnType resultCopy = PduR_CanTpCopyTxData(TxPduId, &info, &retry, &availableDataPtr);
                Std_ReturnType resultTrasmit = CanIf_Transmit(TxPduId , &info);
                if(resultTrasmit != E_OK || resultCopy!= BUFREQ_OK)
                {
                    retry.TpDataState = TP_DATARETRY;
                    frameIndex--;
                }
                else if(resultTrasmit == E_OK)
                {
                    retry.TpDataState = TP_DATACONF;
                }

                #ifdef CANTP_DEBUG
                    printf("Transmit Result = %d\n" , resultTrasmit);
                #endif
            }    

            PduR_CanTpTxConfirmation(TxPduId , E_OK);
            
            CanTp_Buffer[TxPduId].SduLength = 0;
        }
    }
}



void CanTp_TxConfirmation(PduIdType TxPduId, Std_ReturnType result)
{
    #ifdef CANTP_DEBUG
        printf("######## in CanTp_TxConfirmation \n");
    #endif
}

void CanTp_MainFunctionRx(void)
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