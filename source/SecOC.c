#include "SecOC_Lcfg.h"
#include "SecOC_PBcfg.h"
#include "SecOC_Cbk.h"
#include "ComStack_Types.h"
#include "Det.h"
#include "Rte_SecOC.h"
#include "SecOC.h"

#include "PduR_SecOC.h"
#include "Csm.h"

#include <string.h>


PduInfoType SecOC_Buffer[SECOC_BUFFERLENGTH];


/****************************************************
 *          * Function Info *                           *
 *                                                      *
 * Function_Name        : authenticate                  *
 * Function_Index       : SecOC internal                *
 * Function_File        : SWS of secOC                  *
 * Function_Descripton  : The lower layer communication * 
 * interface module confirms  the transmission of a PDU *
 *        or the failure to transmit a PDU              *
 ***************************************************/
//        authenticate( SecOC_Buffer[idx] , &transmitPduInfo)
authenticate(const PduIdType TxPduId, const PduInfoType* AuthPdu, PduInfoType* SecPdu)
/*Std_ReturnType authenticate(
    const PduIdType TxPduId, 
    const PduInfoType* PduInfoPtr,
    uint8* authPtr,
    uint32* authLengthPtr)*/
{
    // 1. Prepare Secured I-PDU
    // 2. Construct Data for Authenticator
    // DataToAuthenticator = Data Identifier | secured part of the Authentic I-PDU | Complete Freshness Value
    uint8 DataToAuth[100]; // Discuss size later
    uint8 DataToAuthLen = 0;

    // Data Identifier
    memcpy(&DataToAuth[DataToAuthLen], TxPduId, sizeof(TxPduId));
    DataToAuthLen += sizeof(TxPduId);

    // secured part of the Authentic I-PDU
    memcpy(&DataToAuth[DataToAuthLen], AuthPdu->SduDataPtr, AuthPdu->SduLength);
    DataToAuthLen += AuthPdu->SduLength;

    // Complete Freshness Value
    /*
    memcpy(&DataToAuth[DataToAuthLen], PduInfoPtr->SduDataPtr, PduInfoPtr->SduLength);
    DataToAuthLen += PduInfoPtr->SduLength;
    */

    Std_ReturnType result;
    uint8*  authenticatorPtr;
    uint32  authenticatorLen;
    result = Csm_MacGenerate(TxPduId, 0, DataToAuth, DataToAuthLen, authenticatorPtr, &authenticatorLen);

    return result;
}

extern void SecOC_MainFunctionTx ( void )
{

}

Std_ReturnType SecOC_IfTransmit( PduIdType TxPduId, const PduInfoType* PduInfoPtr)
{
    Std_ReturnType result = E_OK; 
    if( TxPduId < SECOC_BUFFERLENGTH )
    {
        SecOC_Buffer[TxPduId] = *PduInfoPtr;
    }
    else
    {
        result = E_NOT_OK;
    }

    return result;

}
// PduIdType SecOC_Buffer[SECOC_BUFFERLENGTH];  Hossam declared it

/****************************************************
 *          * Function Info *                           *
 *                                                      *
 * Function_Name        : SecOC_TxConfirmation          *
 * Function_Index       : 8.4.3 [SWS_SecOC_00126]       *
 * Function_File        : SWS of secOC                  *
 * Function_Descripton  : The lower layer communication * 
 * interface module confirms  the transmission of a PDU *
 *        or the failure to transmit a PDU              *
 ***************************************************/
void SecOC_TxConfirmation (PduIdType TxPduId,Std_ReturnType result)
{
    if(result==E_OK)
    {
        //SecOC_Buffer[TxPduId] = NULL;
        // clear buffer
    }
    PduR_SecOCIfTxConfirmation(TxPduId,result);


}

