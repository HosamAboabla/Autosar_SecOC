#ifndef INCLUDE_SECOC_LCFG_H_
#define INCLUDE_SECOC_LCFG_H_

#include "Std_Types.h"
#include "SecOC_Types.h"

extern EcuC_PduType EcuC_Pdu; /* Reference to the global Pdu. */

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


/**************************************************************
 *          * Container Info *                                *
 *                                                            *
 * Container_Name        : SecOC_TxSecuredPdu                 *
 * Parent_Container_Name : SecOC_TxSecuredPduLayer             *
 * Container_Index       : 10.1.16                            *
 **************************************************************/
typedef struct
{
    uint8                   SecOCAuthPduHeaderLength;
    uint16                  SecOCTxSecuredLayerPduId;
    EcuC_PduType*           SecOCTxSecuredLayerPduRef;
} SecOC_TxSecuredPduType;























































/************************************************************
 *          * Container Info *                              *
 *                                                          *
 * Container_Name        : SecOC_UseMessageLink             *
 * Parent_Container_Name : SecOC_TxSecuredPduCollection     *
 * Container_Index       : 10.1.20                          *
 ***********************************************************/
typedef struct
{
   uint16                  SecOCMessageLinkLen;
   uint16                  SecOCMessageLinkPos;
} SecOC_UseMessageLinkType;








/************************************************************
 *          * Container Info *                              *
 *                                                          *
 * Container_Name        : SecOC_TxCryptographicPdu         *
 * Parent_Container_Name : SecOC_TxSecuredPduCollection     *
 * Container_Index       : 10.1.19                          *
 ***********************************************************/
typedef struct
{
   uint16                  SecOCTxCryptographicPduId;
   EcuC_PduType            *SecOCTxCryptographicPduRef;
} SecOC_TxCryptographicPduType;




/************************************************************
 *          * Container Info *                              *
 *                                                          *
 * Container_Name        : SecOC_TxAuthenticPdu             *
 * Parent_Container_Name : SecOC_TxSecuredPduCollection     *
 * Container_Index       : 10.1.18                          *
 ***********************************************************/
typedef struct
{
   uint8                         SecOCAuthPduHeaderLength;
   uint16                        SecOCTxAuthenticPduId;
   EcuC_PduType                  *SecOCTxAuthenticPduRef;
} SecOC_TxAuthenticPduType;








/************************************************************
 *          * Container Info *                              *
 *                                                          *
 * Container_Name        : SecOC_TxSecuredPduCollection     *
 * Parent_Container_Name : SecOC_TxSecuredPduLayer          *
 * Container_Index       : 10.1.17                          *
 ***********************************************************/
typedef struct
{
   SecOC_TxAuthenticPduType                        *SecOCTxAuthenticPdu;
   SecOC_TxCryptographicPduType                    *SecOCTxCryptographicPdu;
   SecOC_UseMessageLinkType                        *SecOCUseMessageLink;
} SecOC_TxSecuredPduCollectionType;
















// SecOCTxSecuredPduLayer

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