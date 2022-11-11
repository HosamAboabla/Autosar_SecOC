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


#endif