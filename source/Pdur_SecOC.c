#include "PduR_SecOC.h"




/****************************************************
 *          * Function Info *                       *
 *                                                  *
 * Function_Name        : PduR_SecOCTransmit        *
 * Function_Index       : 8.3.2.1 [SWS_PduR_00406]  *
 * Function_File        : SWS of Pdur Interface     *
 * Function_Descripton  : Requests transmission     *
 *              of a PDU                            *
 ***************************************************/

/*FROM ROUTING TABLE WE KNOW PAGE 129*/
#define CANIF 0
#define FRIF 1
#define CANTP 2

Std_ReturnType PduR_SecOCTransmit(PduIdType TxPduId, const PduInfoType* PduInfoPtr)
{
    if(*(PduInfoPtr->MetaDataPtr) == CANIF)
    {
        return CanIf_Transmit(TxPduId,PduInfoPtr);
    }
    else if (*(PduInfoPtr->MetaDataPtr) == FRIF)
    {
        return FrIf_Transmit(TxPduId, PduInfoPtr);
    }   
    else if(*(PduInfoPtr->MetaDataPtr) == CANTP)
    {
        return CanTp_Transmit(TxPduId, PduInfoPtr);
    }
    return E_NOT_OK;
}