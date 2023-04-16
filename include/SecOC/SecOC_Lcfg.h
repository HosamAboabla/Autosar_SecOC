#ifndef INCLUDE_SECOC_LCFG_H_
#define INCLUDE_SECOC_LCFG_H_

#include "Std_Types.h"
#include "SecOC_Types.h"
#include "Rte_SecOC.h"
#include "SecOC_Cfg.h"

/* Derived configuration*/
#define SECOC_AUTHPDU_MAX_LENGTH                                    ((uint32) 20)
#define SECOC_TX_DATA_TO_AUTHENTICATOR_LENGTH                       (sizeof(PduIdType) + SECOC_AUTHPDU_MAX_LENGTH + SECOC_TX_FRESHNESS_VALUE_LENGTH)
#define SECOC_AUTHENTICATOR_MAX_LENGTH                              ((uint8)32)

#define SECOC_FRESHNESS_MAX_LENGTH                                  ((uint8)32)

#define SECOC_SECPDU_MAX_LENGTH                                     (SECOC_AUTHPDU_HEADERLENGTH + SECOC_AUTHPDU_MAX_LENGTH + (SECOC_FRESHNESS_MAX_LENGTH/8 + 1) + (SECOC_TX_AUTH_INFO_TRUNC_LENGTH/8 + 1))

#define SECOC_RX_DATA_TO_AUTHENTICATOR_LENGTH                       (sizeof(PduIdType) + SECOC_AUTHPDU_MAX_LENGTH + (SECOC_FRESHNESS_MAX_LENGTH/8 + 1))

#define SECOC_NUM_OF_TX_PDU_PROCESSING                               (6)
#define SECOC_NUM_OF_RX_PDU_PROCESSING                               (5)

/* [SWS_SecOC_00057] The SecOC module shall provide sufficient buffers to store all intermediate data */
typedef struct
{

   uint8                   Freshness[SECOC_FRESHNESS_MAX_LENGTH/8];  /* Complete Freshness Value */
   uint32                  FreshnessLenBits;

   uint8                   FreshnessTrunc[SECOC_FRESHNESS_MAX_LENGTH/8];   /* Truncated freshness value */
   uint32                  FreshnessTruncLenBits;

   uint8                   DataToAuth[SECOC_TX_DATA_TO_AUTHENTICATOR_LENGTH];
   uint32                  DataToAuthLen;

   uint8                   AuthenticatorPtr[SECOC_AUTHENTICATOR_MAX_LENGTH];
   uint32                  AuthenticatorLen;

} SecOC_TxIntermediateType;


typedef struct 
{
   SecOC_PduCollection_Type   Type;
   uint16                     CollectionId;
   uint16                     AuthId;
   uint16                     CryptoId;
   uint8                      status;
} SecOC_PduCollection;


typedef struct
{
   uint16 AuthenticationCounter;
} SecOC_TxCountersType;

typedef struct
{
   uint16 AuthenticationCounter;
   uint16 VerificationCounter;
} SecOC_RxCountersType;

/* [SWS_SecOC_00057] The SecOC module shall provide sufficient buffers to store all intermediate data */
typedef struct
{
   uint8                   authenticPdu[SECOC_AUTHPDU_MAX_LENGTH];
   uint32                  authenticPduLen;

   uint8                   freshness[SECOC_FRESHNESS_MAX_LENGTH / 8];
   uint32                  freshnessLenBits;
   Std_ReturnType          freshnessResult;
   
   uint8                   mac[SECOC_AUTHENTICATOR_MAX_LENGTH / 8];
   uint32                  macLenBits;

   uint8                   DataToAuth[SECOC_RX_DATA_TO_AUTHENTICATOR_LENGTH];
   uint32                  DataToAuthLen;

} SecOC_RxIntermediateType;


typedef SecOC_StatusPropagationMode_Type SecOC_ClientServerVerificationStatusPropagationMode_Type;
typedef SecOC_StatusPropagationMode_Type SecOC_VerificationStatusPropagationMode_Type;

/*
* To be done: EcucFunctionNameDef / SecOC_VerificationStatusCalloutType
* typedef .....?.... SecOC_VerificationStatusCalloutType
*/



/* callout function --> what should i do */
typedef void (SecOC_VerificationStatusCalloutType) (SecOC_VerificationStatusType verificationStatus);


typedef uint16                SecOC_MainFunctionTxPartitionRefType;/* NOT SURE ABOUT THAT TYPE */

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
   PduInfoType             SecOCTxCryptographicPduRef;
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
   PduInfoType                   SecOCTxAuthenticPduRef;
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
    PduInfoType             SecOCTxSecuredLayerPduRef;
} SecOC_TxSecuredPduType;


typedef struct
{
   SecOC_TxSecuredPduType                 *SecOCTxSecuredPdu;
   SecOC_TxSecuredPduCollectionType       *SecOCTxSecuredPduCollection;
}SecOC_TxSecuredPduLayerType;

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
    PduInfoType       SecOCTxAuthenticLayerPduRef;
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
   /*                                                  SecOCSameBufferPduRef;*/
   /*                                                  SecOCTxAuthServiceConfigRef*/
   /*                                                  SecOCTxPduMainFunctionRef;*/
   SecOC_TxAuthenticPduLayerType                      *SecOCTxAuthenticPduLayer;
   /*const SecOC_TxPduSecuredAreaType                  *SecOCTxPduSecuredArea;*/
   const SecOC_TxSecuredPduLayerType                   *SecOCTxSecuredPduLayer;
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
   PduInfoType         *SecOCRxAuthenticPduRef;
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
   PduInfoType     *SecOCRxCryptographicPduRef;
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
   PduInfoType                SecOCRxAuthenticLayerPduRef;
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
   PduInfoType     SecOCRxSecuredLayerPduRef;
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
/*extern Csm_JobType CsmJob;*/
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
   uint8   SecOCMaxAlignScalarType[100];  /* This type can be e.g. uint8, uint16 or uint32.*/
   boolean SecOCOverrideStatusWithDataId;
   boolean SecOCPropagateOnlyFinalVerificationStatus;
   SecOC_QueryFreshnessValue_Type SecOCQueryFreshnessValue;
   /* SecOC_VerificationStatusCalloutType* SecOCVerificationStatusCallout;*/
   boolean SecOCVersionInfoApi;
   /*SecOC_SecurityEventRefsType *SecOCSecurityEventRefs;*/ /* can't have the container of it */

}SecOC_GeneralType;



typedef struct /*Specific Implementation Data Structure Configuration SecOC Module Data Structure*/
{ 
	const SecOC_GeneralType* General;
	const SecOC_TxPduProcessingType* SecOCTxPduProcessings;
	const SecOC_RxPduProcessingType* SecOCRxPduProcessings;
}SecOC_ConfigType;




#endif