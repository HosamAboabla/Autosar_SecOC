#ifndef INCLUDE_SECOC_LCFG_H_
#define INCLUDE_SECOC_LCFG_H_

#include "Std_Types.h"
#include "SecOC_Types.h"

/*****************************************
 *          * Container Info *           *
 *                                       *
 * Container_Name        : SecOCRxAuthenticPdu *
 * Parent_Container_Name : SecOCRxSecuredPduCollection           *
 * Container_Index       : 10.1.12        *
 *****************************************/
typedef struct
{
   uint8                 SecOCAuthPduHeaderLength;
   uint16                SecOCRxAuthenticPduId;
   //rf to pdu           SecOCRxAuthenticPduRef;
}SecOC_RxAuthenticPduType;

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
}SecOC_RxCryptographicPduType;
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
   SecOC_RxAuthenticPduType               *SecOCRxAuthenticPdu;
   SecOC_RxCryptographicPduType           *SecOCRxCryptographicPdu;
   SecOC_UseMessageLinkType               *SecOCUseMessageLink;
}SecOC_RxSecuredPduCollectionType;

/*****************************************
 *          * Container Info *           *
 *                                       *
 * Container_Name        : SecOCRxAuthenticPduLayer *
 * Parent_Container_Name : SecOCRxPduProcessing           *
 * Container_Index       : 10.1.9        *
 *****************************************/
typedef struct 
{
   SecOC_Pdu_Type             SecOCPduType;
   uint16                     SecOCRxAuthenticLayerPduId;
   //rf to pdu               *SecOCRxAuthenticLayerPduRef;
}SecOC_RxAuthenticPduLayerType;

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
}SecOC_RxSecuredPduType;

/*****************************************
 *          * Container Info *           *
 *                                       *
 * Container_Name        : SecOCRxSecuredPduLayer *
 * Parent_Container_Name : SecOCRxPduProcessing           *
 * Container_Index       : 10.1.7        *
 *****************************************/

typedef struct
{
   SecOC_RxSecuredPduType                 *SecOCRxSecuredPdu;
   SecOC_RxSecuredPduCollectionType       *SecOCRxSecuredPduCollection;
}SecOC_RxSecuredPduLayerType;

/***************************************** not certain
 *          * Container Info *           *
 *                                       *
 * Container_Name        : SecOCRxAuthServiceConfigRef *
 * Parent_Container_Name : SecOCRxPduProcessing           *
 * Container_Index       : ECUC_SecOC_00048        *
 *****************************************/

typedef struct
{

}SecOC_RxAuthServiceConfigRefType;

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
   uint16                                                         SecOCAuthenticationBuildAttempts;
   uint16                                                         SecOCAuthenticationVerifyAttempts;
   uint16                                                         SecOCAuthInfoTruncLength;
   SecOC_ClientServerVerificationStatusPropagationMode_Type       SecOCClientServerVerificationStatusPropagationMode;
   uint16                                                         SecOCDataId;
   uint16                                                         SecOCFreshnessValueId;
   uint8                                                          SecOCFreshnessValueLength;
   uint8                                                          SecOCFreshnessValueTruncLength;
   SecOC_ReceptionOverflowStrategy_Type                           SecOCReceptionOverflowStrategy;
   uint16                                                         SecOCReceptionQueueSize;
   boolean                                                        SecOCUseAuthDataFreshness;
   SecOC_VerificationStatusPropagationMode_Type                   SecOCVerificationStatusPropagationMode;
   //SecOC_RxAuthServiceConfigRefType                            *SecOCRxAuthServiceConfigRef;
   SecOC_MainFunctionRxType                                      *SecOCRxPduMainFunctionRef;
   SecOC_SameBufferPduCollectionType                             *SecOCSameBufferPduRef;
   SecOC_RxSecuredPduLayerType                                   *SecOCRxSecuredPduLayer;
   SecOC_RxAuthenticPduLayerType                                 *SecOCRxAuthenticPduLayer;
   SecOC_RxPduSecuredAreaType                                    *SecOCRxPduSecuredArea;
}SecOC_RxPduProcessingType;

#endif