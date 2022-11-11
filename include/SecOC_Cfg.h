#ifndef INCLUDE_SECOC_CFG_H_
#define INCLUDE_SECOC_CFG_H_


/**************************************************************
 *          * Container Info *                                *
 *                                                            *
 * Container_Name        : SecOC_TxAuthenticPduLayer          *
 * Parent_Container_Name : SecOC_TxPduProcessing              *
 * Container_Index       : 10.1.14                            *
 **************************************************************/

#define SECOC_PDU_TYPE                      ((SecOC_PduType_Type)SECOC_TPPDU)
#define SECOC_TX_AUTHENTIC_LAYER_PDUID      ((uint16)0)

/**************************************************************
 *          * Container Info *                                *
 *                                                            *
 * Container_Name        : SecOC_TxSecuredPdu                 *
 * Parent_Container_Name : SecOC_TxSecuredPduLayer             *
 * Container_Index       : 10.1.16                            *
 **************************************************************/

#define SECOC_AUTH_PDU_HEADER_LENGTH        ((uint8)0)
#define SECOC_TX_SECURED_LAYER_PDUID        ((uint16)0)

/************************************************************
 *          * Container Info *                              *
 *                                                          *
 * Container_Name        : SecOC_UseMessageLink             *
 * Parent_Container_Name : SecOC_TxSecuredPduCollection     *
 * Container_Index       : 10.1.20                          *
 ***********************************************************/

#define SECOC_MESSAGE_LINKLEN               ((uint16)0)
#define SECOC_MESSAGE_LINKPOS               ((uint16)0)

/************************************************************
 *          * Container Info *                              *
 *                                                          *
 * Container_Name        : SecOC_TxCryptographicPdu         *
 * Parent_Container_Name : SecOC_TxSecuredPduCollection     *
 * Container_Index       : 10.1.19                          *
 ***********************************************************/
#define SECOC_TX_CRYPTOGRAPHIC_PDUID        ((uint16)0)


#endif