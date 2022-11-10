#ifndef INCLUDE_SECOC_LCFG_H_
#define INCLUDE_SECOC_LCFG_H_

#include "Std_Types.h"
#include "SecOC_Types.h"

extern EcuC_PduType EcuC_Pdu; // Reference to the global Pdu.

/**************************************************************
 *          * Container Info *                                *
 *                                                            *
 * Container_Name        : SecOC_TxAuthenticPduLayer          *
 * Parent_Container_Name : SecOC_TxPduProcessing              *
 * Container_Index       : 10.1.14                            *
 **************************************************************/
typedef struct
{
    SecOC_PduType_Type      SecOCPduType;
    uint16                  SecOCTxAuthenticLayerPduId;
    EcuC_PduType*           SecOCTxAuthenticLayerPduRef;
} SecOC_TxAuthenticPduLayerType;






























































































/****************************************************
 *          * Container Info *                      *
 *                                                  *
 * Container_Name        : SecOC_TxPduSecuredArea   *
 * Parent_Container_Name : SecOC_TxPduProcessing    *
 * Container_Index       : 10.1.21                  *
 ***************************************************/
     typedef struct
{
    uint32                  SecOCSecuredTxPduLength;
    uint32                  SecOCSecuredTxPduOffset;
} SecOC_TxPduSecuredAreaType;





/****************************************************
 *          * Container Info *                      *
 *                                                  *
 * Container_Name        : SecOC_TxPduProcessing    *
 * Parent_Container_Name :                          *
 * Container_Index       : 10.1.11                  *
 ***************************************************/
typedef struct
{
    uint16                                              SecOCAuthenticationBuildAttempts;
    uint16                                              SecOCAuthInfoTruncLength;
    uint16                                              SecOCDataId;
    uint16                                              SecOCFreshnessValueId;
    uint8                                               SecOCFreshnessValueLength;
    uint8                                               SecOCFreshnessValueTruncLength;
    boolean                                             SecOCProvideTxTruncatedFreshnessValue;
    boolean                                             SecOCReAuthenticateAfterTriggerTransmit;
    uint8                                               SecOCTxPduUnusedAreasDefault;
    boolean                                             SecOCUseTxConfirmation;
    //                                                  SecOCSameBufferPduRef;
    //                                                  SecOCTxAuthServiceConfigRef
    //                                                  SecOCTxPduMainFunctionRef;
    //                                                  SecOCTxAuthenticationPduLayer;
    const SecOC_TxPduSecuredAreaType                    *SecOCTxPduSecuredArea;
//                                                      SecOCTxSecuredPduLayer
}SecOC_TxPduProcessingType;





#endif