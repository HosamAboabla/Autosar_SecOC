#ifndef INCLUDE_SECOC_LCFG_H_
#define INCLUDE_SECOC_LCFG_H_

#include "Std_Types.h"
#include "SecOC_Types.h"
#include "Rte_SecOC.h"





typedef SecOC_StatusPropagationMode_Type SecOC_ClientServerVerificationStatusPropagationMode_Type;
typedef SecOC_StatusPropagationMode_Type SecOC_VerificationStatusPropagationMode_Type;

/*
* To be done: EcucFunctionNameDef / SecOC_VerificationStatusCalloutType
* typedef .....?.... SecOC_VerificationStatusCalloutType
*/



/* callout function --> what should i do */
typedef void (SecOC_VerificationStatusCalloutType) (SecOC_VerificationStatusType verificationStatus);


typedef uint16                SecOC_MainFunctionTxPartitionRefType;/* NOT SURE ABOUT THAT TYPE */
typedef struct EcuC_PduType EcuC_PduType;
extern EcuC_PduType           EcuC_Pdu; /* Reference to the global Pdu. */

/*
* Start of RxPduProcessing
*/




/****************************************************
 *          * Container Info *                      *
 *                                                  *
 * Container_Name        : SecOC_RxPduSecuredArea   *
 * Parent_Container_Name : SecOC_RxPduProcessing    *
 * Container_Index       : 10.1.22                  *
 ***************************************************/
typedef struct
{
    uint32                  SecOCSecuredRxPduLength;
    uint32                  SecOCSecuredRxPduOffset;
} SecOC_RxPduSecuredAreaType;




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
    EcuC_PduType            *SecOCTxSecuredLayerPduRef;
} SecOC_TxSecuredPduType;




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
    EcuC_PduType            *SecOCTxAuthenticLayerPduRef;
} SecOC_TxAuthenticPduLayerType;


/****************************************************
 *          * Container Info *                      *
 *                                                  *
 * Container_Name        : SecOC_TxPduProcessing    *
 * Parent_Container_Name :                          *
 * Container_Index       : 10.1.13                  *
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
    const SecOC_TxAuthenticPduLayerType                 *SecOCTxAuthenticationPduLayer;
    const SecOC_TxPduSecuredAreaType                    *SecOCTxPduSecuredArea;
//                                                      SecOCTxSecuredPduLayer
}SecOC_TxPduProcessingType;




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
   EcuC_PduType         *SecOCRxAuthenticPduRef;
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
   EcuC_PduType     *SecOCRxCryptographicPduRef;
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
   SecOC_PduType_Type             SecOCPduType;
   uint16                     SecOCRxAuthenticLayerPduId;
   EcuC_PduType              *SecOCRxAuthenticLayerPduRef;
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
   uint8           SecOCAuthPduHeaderLength;
   uint16          SecOCRxSecuredLayerPduId;
   boolean         SecOCSecuredRxPduVerification;
   EcuC_PduType   *SecOCRxSecuredLayerPduRef;
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






/*****************************************
 *          * Container Info *           *
 *                                       *
 * Container_Name        : SecOCSameBufferPduCollection *
 * Parent_Container_Name : SecOC           *
 * Container_Index       : 10.1.5        *
 *****************************************/
typedef struct
{
   uint32    SecOCBufferLength;
}SecOC_SameBufferPduCollectionType;





/***************************************** not certain
 *          * Container Info *           *
 *                                       *
 * Container_Name        : SecOCRxAuthServiceConfigRef *
 * Parent_Container_Name : SecOCRxPduProcessing           *
 * Container_Index       : ECUC_SecOC_00048        *
 *****************************************/
//extern Csm_JobType CsmJob;
typedef struct
{
   Csm_JobType    *CsmJob;
}SecOC_RxAuthServiceConfigRefType;

/*************************************************************
*                          Container                         *
* Name : SecOCMainFunctionRx                                 *
* parent : SecOC                                             *
* Index : 10.1.3                                             *
**************************************************************/

typedef uint16              SecOC_MainFunctionRxPartitionRefType; /* NOT SURE ABOUT THAT TYPE */

typedef struct 
{
    float64 SecOCMainFunctionPeriodRx;
    SecOC_MainFunctionRxPartitionRefType *SecOCMainFunctionRxPartitionRef; /* NOT SURE ABOUT THAT TYPE */

}SecOC_MainFunctionRxType;

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
   SecOC_RxAuthServiceConfigRefType                              *SecOCRxAuthServiceConfigRef;
   SecOC_MainFunctionRxType                                      *SecOCRxPduMainFunctionRef;
   SecOC_SameBufferPduCollectionType                             *SecOCSameBufferPduRef;
   SecOC_RxSecuredPduLayerType                                   *SecOCRxSecuredPduLayer;
   SecOC_RxAuthenticPduLayerType                                 *SecOCRxAuthenticPduLayer;
   SecOC_RxPduSecuredAreaType                                    *SecOCRxPduSecuredArea;
}SecOC_RxPduProcessingType;



/*************************************************************
*                          Container                         *
* Name : SecOCMainFunctionTx                                 *
* parent : SecOC                                             *
* Index : 10.1.4                                             *
**************************************************************/




typedef struct 
{
    float64 SecOCMainFunctionPeriodTx;
    SecOC_MainFunctionTxPartitionRefType *SecOCMainFunctionTxPartitionRef; /* NOT SURE ABOUT THAT TYPE */

}SecOC_MainFunctionTxType;




/*************************************************************
*                          Container                         *
* Name : SecOCGeneral                                        *
* parent : SecOC                                             *
* Index : 10.1.2                                             *
**************************************************************/


typedef struct 
{
    uint8   SecOCDefaultAuthenticationInformationPattern;
    boolean SecOCDevErrorDetect;
    boolean SecOCEnableForcedPassOverride;
    boolean SecOCEnableSecurityEventReporting;
    boolean SecOCIgnoreVerificationResult;
    uint8 SecOCMaxAlignScalarType[100];  /* This type can be e.g. uint8, uint16 or uint32.*/
    boolean SecOCOverrideStatusWithDataId;
    boolean SecOCPropagateOnlyFinalVerificationStatus;
    SecOC_QueryFreshnessValue_Type SecOCQueryFreshnessValue;
    // SecOC_VerificationStatusCalloutType* SecOCVerificationStatusCallout;
    boolean SecOCVersionInfoApi;
    //SecOC_SecurityEventRefsType *SecOCSecurityEventRefs; /* can't have the container of it */

}SecOC_GeneralType;



typedef struct //Specific Implementation Data Structure Configuration SecOC Module Data Structure
{ 
	const SecOC_GeneralType* general;
	const SecOC_TxPduProcessingType* secOCTxPduProcessings;
	const SecOC_RxPduProcessingType* secOCRxPduProcessings;
}SecOC_ConfigType;




#endif