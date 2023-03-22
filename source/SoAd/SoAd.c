#include "SoAd.h"
#include "Pdur_SoAd.h"
#include "SecOC.h"
#include "Std_Types.h"
#include "SecOC_Debug.h"
#include "SecOC_Cfg.h"


#ifdef LINUX
#include "ethernet.h"
#endif


PduInfoType SoAdTp_Buffer[SOAD_BUFFERLENGTH];

Std_ReturnType last_pdu; /* Hossam*/

extern const SecOC_TxPduProcessingType     *SecOCTxPduProcessing;



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

    #ifdef LINUX
    result = ethernet_send(TxPduId, PduInfoPtr->SduDataPtr , PduInfoPtr->SduLength);
    #endif


    if (SecOCTxPduProcessing[TxPduId].SecOCTxAuthenticPduLayer->SecOCPduType == SECOC_TPPDU)
    {
        SoAd_TxConfirmation(TxPduId, result);
    }
    else if (SecOCTxPduProcessing[TxPduId].SecOCTxAuthenticPduLayer->SecOCPduType == SECOC_IFPDU)
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


void SoAd_MainFunctionTx(void)
{
    #ifdef SOAD_DEBUG
        printf("######## in SoAd_MainFunctionTx\n");
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
    for(idx = 0 ; idx < SOAD_BUFFERLENGTH ; idx++)
    {
        if( SoAdTp_Buffer[idx].SduLength > 0)
        {
            #ifdef SOAD_DEBUG
                printf("Start sending id = %d\n" , idx);
                printf("PDU length = %d\n" , SoAdTp_Buffer[idx].SduLength);       
                printf("All Data to be Sent: \n");
                for(int i = 0 ; i < SoAdTp_Buffer[idx].SduLength; i++)
                {
                    printf("%d  " , SoAdTp_Buffer[idx].SduDataPtr[i]);
                }
                printf("\n\n\n");
            #endif

            for(int i = 0; i < (SoAdTp_Buffer[idx].SduLength / BUS_LENGTH) ; i++)
            {
                // Request CopyTxData
                result = SecOC_CopyTxData(idx, &info, &retry, &availableDataPtr);

                SoAd_IfTransmit(idx , &info);

                #ifdef SOAD_DEBUG
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
                #ifdef SOAD_DEBUG
                    printf("Transmit Result = %d\n" , last_pdu);
                #endif
            }

            if( (SoAdTp_Buffer[idx].SduLength % BUS_LENGTH) != 0)
            {
                // Request CopyTxData with length (SoAdTp_Buffer[idx].SduLength % BUS_LENGTH) 
                info.SduLength = (SoAdTp_Buffer[idx].SduLength % BUS_LENGTH);
                SecOC_CopyTxData(idx, &info, NULL, &availableDataPtr);

                #ifdef SOAD_DEBUG
                    printf("Sending remaider part with length %d \n", info.SduLength);
                    for(int j = 0; j < info.SduLength; j++)
                        printf("%d\t",info.SduDataPtr[j]);
                    printf("\n");
                #endif
                

                // Send data using SoAdIf
                SoAd_IfTransmit(idx , &info);
                printf("Delay...\n");
                long long int delay = 60000000;
                while(delay--);

                while(last_pdu == E_NOT_OK)
                {
                    retry.TxTpDataCnt = (SoAdTp_Buffer[idx].SduLength % BUS_LENGTH);
                    retry.TpDataState = TP_DATARETRY;
                    SecOC_CopyTxData(idx, &info, NULL, &availableDataPtr);
                    SoAd_IfTransmit(idx , &info);
                }
                retry.TpDataState = TP_DATACONF;
                #ifdef SOAD_DEBUG
                    printf("Transmit Result = %d\n" , last_pdu);
                #endif
            }

            PduR_SoAdTpTxConfirmation(idx , E_OK);

        }
    }
}



void SoAd_TxConfirmation(PduIdType TxPduId, Std_ReturnType result)
{
    #ifdef SOAD_DEBUG
        printf("######## in SoAd_TxConfirmation \n");
    #endif
    last_pdu = result;
}

void SoAd_MainFunctionRx(void)
{
    #ifdef SOAD_DEBUG
        printf("######## in SoAd_MainFunctionRx\n");
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

    #ifdef SOAD_DEBUG
        printf("######## in main tp Rx  in id : %d\n", idx);
    #endif
    BufReq_ReturnType Result;

    #ifdef LINUX
    ethernet_receive(Tp_Spdu.SduDataPtr, Tp_Spdu.SduLength,&idx);
    #endif
    /* Check if SoAd Receive  */
    BufReq_ReturnType result= PduR_SoAdStartOfReception(idx, &Tp_Spdu,TpSduLength, &bufferSizePtr);
    if (result == BUFREQ_OK)
    {
        /* send Data */
        for(int i = 0; i <= LastFrame_idx; i++)
        {
            #ifdef SOAD_DEBUG
            printf("Info Received idx=%d: \n",i);
            for(int j  = 0 ; j < Tp_Spdu.SduLength ; j++)
            {
                printf("%d ",Tp_Spdu.SduDataPtr[j]);
            }
            printf("\n\n\n");
            #endif
            Result = PduR_SoAdTpCopyRxData(idx, &Tp_Spdu, &bufferSizePtr);
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
        PduR_SoAdTpRxIndication(idx,Result);
    }  
}