#ifndef  SCHM_SECOC_H_
#define SCHM_SECOC_H_


/********************************************************************************************************/
/*****************************************FunctionPrototype**********************************************/
/********************************************************************************************************/

/****************************************************
 *          * Function Info *                           *
 *                                                      *
 * Function_Name        : SecOC_MainFunctionTx          *
 * Function_Index       : 8.6.2 [SWS_SecOC_00176]       *
 * Function_File        : SWS of secOC                  *
 * Function_Descripton  : This function performs the    *
 * processing of the SecOC module's authentication and  *
 * verification processing for the Tx path              *
 ********************************************************/
void SecOC_MainFunctionTx(void);


/****************************************************
 *          * Function Info *                           *
 *                                                      *
 * Function_Name        : SecOCMainFunctionRx           *
 * Function_Index       : 8.6.1 [SWS_SecOC_00171]       *
 * Function_File        : SWS of secOC                  *
 * Function_Descripton  : This function performs the    *
 *  processing of the SecOC module's authentication and * 
 * verification processing for the Rx path              *
 ********************************************************/
void SecOC_MainFunctionRx(void);

#endif