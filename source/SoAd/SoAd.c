/********************************************************************************************************/
/************************************************INCULDES************************************************/
/********************************************************************************************************/

#include "SoAd.h"
#include "PduR_SoAd.h"
#include "SecOC.h"
#include "Std_Types.h"
#include "SecOC_Debug.h"
#include "SecOC_Cfg.h"


#ifdef LINUX
#include "ethernet.h"
#endif

/********************************************************************************************************/
/******************************************GlobalVaribles************************************************/
/********************************************************************************************************/

static PduInfoType SoAdTp_Buffer[SOAD_BUFFERLENGTH];
static PduInfoType SoAdTp_Buffer_Rx[SECOC_NUM_OF_RX_PDU_PROCESSING];
static uint8 SoAdTp_Recieve_Counter[SECOC_NUM_OF_RX_PDU_PROCESSING] = {0};
static PduLengthType SoAdTp_secureLength_Recieve[SECOC_NUM_OF_RX_PDU_PROCESSING] = {0};


extern const SecOC_RxPduProcessingType     *SecOCRxPduProcessing;

extern SecOC_PduCollection PdusCollections[];


/********************************************************************************************************/
/********************************************Functions***************************************************/
/********************************************************************************************************/

/****************************************************
 *          * Function Info *                       *
 *                                                  *
 * Function_Name        : SoAd_IfTransmit           *
 * Function_Index       :                           *
 * Function_File        : SWS of SoAd Interface     *
 * Function_Descripton  : Requests transmission     *
 *              of a PDU                            *
 ***************************************************/
Std_ReturnType SoAd_IfTransmit(PduIdType TxPduId,const PduInfoType* PduInfoPtr)
{
    #ifdef SOAD_DEBUG
        printf("######## in SoAd_IfTransmit \n");
    #endif

    Std_ReturnType result = E_OK;

    #ifdef SOAD_DEBUG
        printf("Secure PDU -->\n");
            for(int i = 0; i < PduInfoPtr->SduLength; i++)
                printf("%d ", PduInfoPtr->SduDataPtr[i]);
        printf("\n");
    #endif

    #ifdef __linux__
    result = ethernet_send(TxPduId, PduInfoPtr->SduDataPtr , PduInfoPtr->SduLength);
    #endif
    int delay = 50000000;
    while (delay--);

    if (PdusCollections[TxPduId].Type== SECOC_SECURED_PDU_SOADTP)
    {
        SoAdTp_TxConfirmation(TxPduId, result);
    }
    else if (PdusCollections[TxPduId].Type == SECOC_SECURED_PDU_SOADIF)
    {
        PduR_SoAdIfTxConfirmation(TxPduId , result);
    }


    return result;
}







Std_ReturnType SoAd_TpTransmit(PduIdType SoAdTxSduId, const PduInfoType* SoAdTxInfoPtr)
{
    #ifdef SOAD_DEBUG
        printf("######## in SoAd_TpTransmit\n");
    #endif
    SoAdTp_Buffer[SoAdTxSduId] = *SoAdTxInfoPtr;
}

void SoAdTp_RxIndication (PduIdType RxPduId, const PduInfoType* PduInfoPtr)
{
    #ifdef SOAD_DEBUG
        printf("######## in SoAdTp_RxIndication\n");
    #endif
    /* copy to SoAdTp buffer */
    SoAdTp_Buffer_Rx[RxPduId] = *PduInfoPtr;
    
    /* Check if it first frame :
        Check if there are a header of no 
            if there are a header 
                get the auth length from the frame
            else 
                get the config length of data
        then add the Freshness , Mac and Header length 
        to the the whole Secure Frame Length to recieve
    */
    if(SoAdTp_Recieve_Counter[RxPduId] == 0)
    {
        uint8 AuthHeadlen = SecOCRxPduProcessing[RxPduId].SecOCRxSecuredPduLayer->SecOCRxSecuredPdu->SecOCAuthPduHeaderLength;
        PduLengthType SecureDataframe = AuthHeadlen + BIT_TO_BYTES(SecOCRxPduProcessing[RxPduId].SecOCFreshnessValueTruncLength) + BIT_TO_BYTES(SecOCRxPduProcessing[RxPduId].SecOCAuthInfoTruncLength);
        if(AuthHeadlen > 0)
        {
            (void)memcpy((uint8*)&SoAdTp_secureLength_Recieve[RxPduId], PduInfoPtr->SduDataPtr, AuthHeadlen );
        }
        else
        {
            SoAdTp_secureLength_Recieve[RxPduId] = SecOCRxPduProcessing[RxPduId].SecOCRxAuthenticPduLayer->SecOCRxAuthenticLayerPduRef.SduLength;
        }
        SoAdTp_secureLength_Recieve[RxPduId] += SecureDataframe;
    }
    SoAdTp_Recieve_Counter[RxPduId] ++;
}

void SoAd_MainFunctionTx(void)
{
    #ifdef SOAD_DEBUG
        printf("######## in SoAd_MainFunctionTx\n");
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
                send it to SoAdIF
                if result = E_OK
                    continue sending 
                else if NOT_E_OK
                    make retrystate = TP_DATARETRY
            send confirmationc
            clear the buffer
        else
            do nothing
        */
        
        if( SoAdTp_Buffer[TxPduId].SduLength > 0)
        {
            uint8 lastFrameIndex = (SoAdTp_Buffer[TxPduId].SduLength % BUS_LENGTH == 0)  ? (SoAdTp_Buffer[TxPduId].SduLength / BUS_LENGTH) : ((SoAdTp_Buffer[TxPduId].SduLength / BUS_LENGTH) + 1);
            #ifdef SOAD_DEBUG
                printf("Start sending id = %d\n" , TxPduId);
                printf("PDU length = %d\n" , SoAdTp_Buffer[TxPduId].SduLength);       
                printf("All Data to be Sent: \n");
                for(int i = 0 ; i < SoAdTp_Buffer[TxPduId].SduLength; i++)
                {
                    printf("%d  " , SoAdTp_Buffer[TxPduId].SduDataPtr[i]);
                }
                printf("\n\n\n");
            #endif
            for(int frameIndex = 0; frameIndex < lastFrameIndex ; frameIndex++)
            {
                if(frameIndex == lastFrameIndex - 1)
                {
                    info.SduLength = (SoAdTp_Buffer[TxPduId].SduLength % BUS_LENGTH == 0)  ? (BUS_LENGTH) : (SoAdTp_Buffer[TxPduId].SduLength % BUS_LENGTH);
                    #ifdef SOAD_DEBUG
                    printf("last frame PDU length = %d\n" , SoAdTp_Buffer[TxPduId].SduLength);       
                    printf("All Data to be Sent: \n");
                    for(int i = 0 ; i < info.SduLength; i++)
                    {
                        printf("%d  " , info.SduDataPtr[i]);
                    }
                    printf("\n");
                    #endif
                }
                BufReq_ReturnType resultCopy = PduR_SoAdTpCopyTxData(TxPduId, &info, &retry, &availableDataPtr);
                Std_ReturnType resultTrasmit = SoAd_IfTransmit(TxPduId , &info);
                if(resultTrasmit != E_OK || resultCopy!= BUFREQ_OK)
                {
                    retry.TpDataState = TP_DATARETRY;
                    frameIndex--;
                }
                else if(resultTrasmit == E_OK)
                {
                    retry.TpDataState = TP_DATACONF;
                }

                #ifdef SOAD_DEBUG
                    printf("Transmit Result = %d\n" , resultTrasmit);
                #endif
            }    

            PduR_SoAdTpTxConfirmation(TxPduId , E_OK);
            
            SoAdTp_Buffer[TxPduId].SduLength = 0;
        }
    }
}



void SoAdTp_TxConfirmation(PduIdType TxPduId, Std_ReturnType result)
{
    #ifdef SOAD_DEBUG
        printf("######## in SoAd_TxConfirmation \n");
    #endif
}

void SoAd_MainFunctionRx(void)
{
    #ifdef SOAD_DEBUG
        printf("######## in SoAd_MainFunctionRx\n");
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
        if((SoAdTp_Recieve_Counter[RxPduId] > 0) && (SoAdTp_Buffer_Rx[RxPduId].SduLength > 0))
        {
            uint8 lastFrameIndex = (SoAdTp_secureLength_Recieve[RxPduId] % BUS_LENGTH == 0)  ? (SoAdTp_secureLength_Recieve[RxPduId] / BUS_LENGTH) : ((SoAdTp_secureLength_Recieve[RxPduId] / BUS_LENGTH) + 1);
            PduLengthType bufferSizePtr;
            #ifdef SOAD_DEBUG
                printf("######## in main tp Rx  in id : %d\n", RxPduId);
                printf("for id %d :",RxPduId);
                for(int l = 0; l < SoAdTp_Buffer_Rx[RxPduId].SduLength; l++)
                {
                    printf("%d ", SoAdTp_Buffer_Rx[RxPduId].SduDataPtr[l]);
                }
                printf("\n");
            #endif
            if(SoAdTp_Recieve_Counter[RxPduId] == 1)
            {
                result = PduR_SoAdStartOfReception(RxPduId, &SoAdTp_Buffer_Rx[RxPduId], SoAdTp_secureLength_Recieve[RxPduId], &bufferSizePtr);
                if (result == BUFREQ_OK)
                {
                    result = PduR_SoAdTpCopyRxData(RxPduId, &SoAdTp_Buffer_Rx[RxPduId], &bufferSizePtr);
                }
                else
                {
                    SoAdTp_Recieve_Counter[RxPduId] = 0;
                }
                SoAdTp_Buffer_Rx[RxPduId].SduLength = 0;
            }
            else if (SoAdTp_Recieve_Counter[RxPduId] == lastFrameIndex)
            {
                SoAdTp_Buffer_Rx[RxPduId].SduLength = (SoAdTp_secureLength_Recieve[RxPduId] % BUS_LENGTH == 0) ? (BUS_LENGTH) : (SoAdTp_secureLength_Recieve[RxPduId] % BUS_LENGTH);
                result = PduR_SoAdTpCopyRxData(RxPduId, &SoAdTp_Buffer_Rx[RxPduId], &bufferSizePtr);
                PduR_SoAdTpRxIndication(RxPduId, result);
                SoAdTp_Recieve_Counter[RxPduId] = 0;
            }
            else
            {
                result = PduR_SoAdTpCopyRxData(RxPduId, &SoAdTp_Buffer_Rx[RxPduId], &bufferSizePtr);
            }
        }
    }
}