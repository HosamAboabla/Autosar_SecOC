#ifndef INCLUDE_SECOC_CFG_H_
#define INCLUDE_SECOC_CFG_H_

/*
 * Configuration parameter for the Pdu that is received by the SecOC module from the PduR
 */
#define SECOC_PDU_TYPE                      ((SecOC_PduType_Type)SECOC_TPPDU)
#define SECOC_TX_AUTHENTIC_LAYER_PDUID      ((uint16)0)


/*
 * Configuration parameter for the one Pdu that is transmitted by the SecOC module to the PduR after the Mac was generated
 */
#define SECOC_AUTH_PDU_HEADER_LENGTH        ((uint8)0)
#define SECOC_TX_SECURED_LAYER_PDUID        ((uint16)0)


#endif