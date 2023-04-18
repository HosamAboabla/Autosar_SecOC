#ifndef  SCHM_SECOC_H_
#define SCHM_SECOC_H_


/********************************************************************************************************/
/*****************************************FunctionPrototype**********************************************/
/********************************************************************************************************/

/****************************************************
 *          * Function Info *                           *
 *                                                      *
 * Function_Name        : SecOC_MainFunctionTx          *
 * Function_Index       : 8.6.2                         *
 * Function_File        : SWS of secOC                  *
 * Function_Descripton  : The lower layer communication * 
 * interface module confirms  the transmission of a PDU *
 *        or the failure to transmit a PDU              *
 ***************************************************/
void SecOCMainFunctionTx(void);

void SecOCMainFunctionRx(void);

#endif