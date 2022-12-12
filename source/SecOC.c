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


static PduInfoType SecOC_Buffer[SECOC_BUFFERLENGTH];

#define SECOC_CAN_DATAFRAME_MAX ((uint8)8)
#define SECOC_CAN_DATA_MAX      ((uint16)(SECOC_CAN_DATAFRAME_MAX - (SECOC_AUTH_INFO_TRUNC_LENGTH / 8)))

#define SECOC_SDATA_MAX         ((uint8)4)
#define SECOC_FRESHNESS_MAX     ((uint8)16)
#define SECOC_MACLEN_MAX        ((uint8)16)

/****************************************************
 *          * Function Info *                           *
 *                                                      *
 * Function_Name        : authenticate                  *
 * Function_Index       : SecOC internal                *
 * Parameter in         : TxPduId                       *
 * Function_Descripton  : The lower layer communication * 
 * interface module confirms  the transmission of a PDU *
 *        or the failure to transmit a PDU              *
 ***************************************************/
static Std_ReturnType authenticate(const PduIdType TxPduId, const PduInfoType* AuthPdu, PduInfoType* SecPdu)

{
    // 1. Prepare Secured I-PDU
    // 2. Construct Data for Authenticator
    uint8 DataToAuth[sizeof(TxPduId) + SECOC_SDATA_MAX + SECOC_FRESHNESS_MAX]; // CAN payload
    uint8 DataToAuthLen = 0;

    // DataToAuthenticator = Data Identifier | secured part of the Authentic I-PDU | Complete Freshness Value
    // Data Identifier
    memcpy(&DataToAuth[DataToAuthLen], &TxPduId, sizeof(TxPduId));
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
    uint8  authenticatorPtr[SECOC_MACLEN_MAX];
    uint32  authenticatorLen = SECOC_AUTH_INFO_TRUNC_LENGTH / 8;
    result = Csm_MacGenerate(TxPduId, 0, DataToAuth, DataToAuthLen, authenticatorPtr, &authenticatorLen);

    if(result == E_NOT_OK)
    {
        return result;
    }

    // Create secured IPDU

    *SecPdu = *AuthPdu;
    SecPdu->SduLength = 8;

    memcpy(SecPdu->SduDataPtr + SECOC_CAN_DATA_MAX, authenticatorPtr, authenticatorLen);
    return result;
}
#include <stdio.h>
void SecOC_MainFunctionTx ( void )
{
    PduInfoType SecPdu, AuthPdu;
    uint8 in[4] = {'a', 'b', 'c', 'd'};
   // memcpy(SecPdu.SduDataPtr, in, 4);
    AuthPdu.SduDataPtr = in;
    AuthPdu.SduLength = 4;
    printf("%.*s\n", AuthPdu.SduLength, AuthPdu.SduDataPtr);
    uint8_t sec[20];
    SecPdu.SduDataPtr = sec;
    authenticate(0, &AuthPdu, &SecPdu);

    printf("%.*s\n", SecPdu.SduLength, SecPdu.SduDataPtr);

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

