#ifndef INCLUDE_SECOC_CFG_H_
#define INCLUDE_SECOC_CFG_H_

/*****************************************
 *          * Container Info *           *
 *                                       *
 * Container_Name        : SecOCRxAuthenticPduLayer *
 * Parent_Container_Name : SecOCRxPduProcessing           *
 * Container_Index       : 10.1.9        *
 *****************************************/
typedef struct 
{
   SecOCPdu_type              SecOCPduType;
   uint16                     SecOCRxAuthenticLayerPduId;
   //rf to pdu               *SecOCRxAuthenticLayerPduRef;
}SecOCRxAuthenticPduLayerType;

/*****************************************
 *          * Container Info *           *
 *                                       *
 * Container_Name        : SecOCRxAuthenticPdu *
 * Parent_Container_Name : SecOCRxSecuredPduCollection           *
 * Container_Index       : 10.1.12        *
 *****************************************/
typedef struct
{
   uint8          SecOCAuthPduHeaderLength;
   uint16         SecOCRxAuthenticPduId;
   //rf           SecOCRxAuthenticPduRef;
}SecOCRxAuthenticPduType;

/*****************************************
 *          * Container Info *           *
 *                                       *
 * Container_Name        : SecOCRxCryptographicPdu *
 * Parent_Container_Name : SecOCRxSecuredPduCollection           *
 * Container_Index       : 10.1.11        *
 *****************************************/
typedef struct
{
   uint16            SecOCRxCryptographicPduId;
   //rf to pdu       SecOCRxCryptographicPduRef;
}SecOCRxCryptographicPduType;
/*****************************************
 *          * Container Info *           *
 *                                       *
 * Container_Name        : SecOCRxSecuredPduCollection *
 * Parent_Container_Name : SecOCRxSecuredPduLayer           *
 * Container_Index       : 10.1.10        *
 *****************************************/
typedef struct 
{
   boolean                                 SecOCSecuredRxPduVerification;
   SecOCRxAuthenticPduType                *SecOCRxAuthenticPdu;
   SecOCRxCryptographicPduType            *SecOCRxCryptographicPdu;
   SecOCUseMessageLinkType                *SecOCUseMessageLink;
}SecOCRxSecuredPduCollectionType;

/*****************************************
 *          * Container Info *           *
 *                                       *
 * Container_Name        : SecOCRxSecuredPdu *
 * Parent_Container_Name : SecOCRxSecuredPduLayer           *
 * Container_Index       : 10.1.8        *
 *****************************************/
typedef struct
{
   uint8          SecOCAuthPduHeaderLength;
   uint16         SecOCRxSecuredLayerPduId;
   boolean        SecOCSecuredRxPduVerification;
   //rf to pdu     SecOCRxSecuredLayerPduRef;
}SecOCRxSecuredPduType;

/*****************************************
 *          * Container Info *           *
 *                                       *
 * Container_Name        : SecOCRxSecuredPduLayer *
 * Parent_Container_Name : SecOCRxPduProcessing           *
 * Container_Index       : 10.1.7        *
 *****************************************/

typedef struct {
{
   SecOCRxSecuredPduType   *SecOCRxSecuredPdu;

}SecOCRxSecuredPduLayerType;

/***************************************** not certain
 *          * Container Info *           *
 *                                       *
 * Container_Name        : SecOCRxAuthServiceConfigRef *
 * Parent_Container_Name : SecOCRxPduProcessing           *
 * Container_Index       : ECUC_SecOC_00048        *
 *****************************************/
ECUC_SecOC_00048
typedef struct
{

}SecOCRxAuthServiceConfigRefType;
/*****************************************
 *          * Container Info *           *
 *                                       *
 * Container_Name        : SecOCRxPduProcessing *
 * Parent_Container_Name : SecOC           *
 * Container_Index       : 10.1.6        *
 *****************************************/
typedef struct
{
   uint16                                                         SecOCAuthDataFreshnessLen;
   uint16                                                         SecOCAuthDataFreshnessStartPosition;
   unit16                                                         SecOCAuthenticationBuildAttempts;
   uint16                                                         SecOCAuthenticationVerifyAttempts;
   uint16                                                         SecOCAuthInfoTruncLength;
   SecOCClientServerVerificationStatusPropagationModeType         SecOCClientServerVerificationStatusPropagationMode;
   uint16                                                         SecOCDataId;
   uint16                                                         SecOCFreshnessValueId;
   uint16                                                         SecOCFreshnessValueLength;
   uint16                                                         SecOCFreshnessValueTruncLength;
   SecOCReceptionOverflowStrategyType                             SecOCReceptionOverflowStrategy;
   uint16                                                         SecOCReceptionQueueSize;
   boolean                                                        SecOCUseAuthDataFreshness;
   SecOCVerificationStatusPropagationModeType                     SecOCVerificationStatusPropagationMode;
   //SecOCRxAuthServiceConfigRefType                               *SecOCRxAuthServiceConfigRef;
   //SecOCMainFunctionRxType                                       *SecOCRxPduMainFunctionRef;
   //SecOCSameBufferPduCollectionType                              *SecOCSameBufferPduRef;
   SecOCRxSecuredPduLayerType                                    *SecOCRxSecuredPduLayer;
   SecOCRxAuthenticPduLayerType                                  *SecOCRxAuthenticPduLayer;
   SecOCRxPduSecuredAreaType                                     *SecOCRxPduSecuredArea;
}SecOCRxPduProcessingType;

#endif