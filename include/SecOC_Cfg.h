#ifndef INCLUDE_SECOC_CFG_H_
#define INCLUDE_SECOC_CFG_H_

/*
 * Configuration parameter for SecOC_TxAuthenticPduLayer
 */
#define SECOC_PDU_TYPE                      ((SecOC_PduType_Type)SECOC_TPPDU)
#define SECOC_TX_AUTHENTIC_LAYER_PDUID      ((uint16)0)


/*
 * Configuration parameter for SecOC_TxSecuredPdu
 */
#define SECOC_AUTH_PDU_HEADER_LENGTH        ((uint8)0)
#define SECOC_TX_SECURED_LAYER_PDUID        ((uint16)0)


























































/*
 * Configuration parameter for SecOC_TxAuthenticPduLayer
 */
//
#define SECOC_TX_AUTHENTIC_LAYER_PDU_ID                         ((uint16) 0)
#define SECOC_PDU_TYPE                                          ((SecOC_PduType_Type) SECOC_IFPDU)




/*
 * Configuration parameter for SecOC_TxPduProcessing
 */
#define SECOC_AUTHENTICATION_BUILD_ATTEMPTS                         ((uint16) 5)
#define SECOC_AUTH_INFO_TRUNC_LENGTH                                ((uint16) 1)
#define SECOC_DATA_ID                                               ((uint16) 0)
#define SECOC_FRESHNESS_VALUE_ID                                    ((uint16) 0)
#define SECOC_FRESHNESS_VALUE_LENGTH                                ((uint8 ) 0)
#define SECOC_FRESHNESS_VALUE_TRUNC_LENGTH                          ((uint8 ) 0)
#define SECOC_PROVIDE_TX_TRUNCATED_FRESHNESS_VALUE                  ((boolean) 0)
#define SECOC_RE_AUTHENTICATE_AFTER_TRIGGER_TRANSMIT                ((boolean) 1)
#define SECOC_TX_PDU_UNUSED_AREAS_DEFAULT                           ((uint8 ) 0)
#define SECOC_USE_TX_CONFIRMATION                                   ((boolean)0)
//                                                  SecOCSameBufferPduRef;
//                                                  SecOCTxAuthServiceConfigRef
//                                                  SecOCTxPduMainFunctionRef;

#endif