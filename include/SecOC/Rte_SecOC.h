#ifndef INCLUDE_RTE_SECOC_H_
#define INCLUDE_RTE_SECOC_H_

/********************************************************************************************************/
/*********************************************EnumAndStruct**********************************************/
/********************************************************************************************************/

typedef enum 
{
    SECOC_VERIFICATIONSUCCESS = 0x00,
    SECOC_VERIFICATIONFAILURE = 0x01,
    SECOC_FRESHNESSFAILURE = 0x02,
    SECOC_AUTHENTICATIONBUILDFAILURE = 0x03,
    SECOC_NO_VERIFICATION = 0x04,
    SECOC_VERIFICATIONFAILURE_OVERWRITTEN = 0x05

}SecOC_VerificationResultType;


typedef struct 
{
    uint16 freshnessValueID;
    SecOC_VerificationResultType verificationStatus;
    uint16 secOCDataId;
}SecOC_VerificationStatusType;


#endif