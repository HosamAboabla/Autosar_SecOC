#ifndef INCLUDE_SECOC_LCFG_H_
#define INCLUDE_SECOC_LCFG_H_





































































































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