/* Copyright [2022/2023] <Tanta University> */
#ifndef INCLUDE_FVM_H_
#define INCLUDE_FVM_H_

/********************************************************************************************************/
/************************************************INCULDES************************************************/
/********************************************************************************************************/

#include "Std_Types.h"
#include "Rte_SecOC_Type.h"


/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/

/* SecOCFreshnessValueID MAX NUMBER */
#define SecOC_FreshnessValue_ID_MAX 100


/********************************************************************************************************/
/*****************************************FunctionPrototype**********************************************/
/********************************************************************************************************/

/********************************************************
 *          * Function Info *                           *
 *                                                      *
 * Function_Name        : FVM_IncreaseCounter           *
 * Function_Index       :                               *
 * Function_File        :                               *
 * Function_Descripton  : This API Increase the counter *
 *                                                      *
 *******************************************************/
Std_ReturnType FVM_IncreaseCounter(uint16 SecOCFreshnessValueID);


/********************************************************
 *          * Function Info *                           *
 *                                                      *
 * Function_Name        : FVM_UpdateCounter             *
 * Function_Index       :                               *
 * Function_File        :                               *
 * Function_Descripton  : Set the Counter Value to      *
 * new Value                                            *
 *                                                      *
 *******************************************************/
Std_ReturnType FVM_UpdateCounter(uint16 SecOCFreshnessValueID, uint8* SecOCFreshnessValue,
uint32 SecOCFreshnessValueLength);

/********************************************************
 *          * Function Info *                           *
 *                                                      *
 * Function_Name        : FVM_GetTxFreshness            *
 * Function_Index       : 8.5.3 [SWS_SecOC_00126]       *
 * Function_File        : SWS of SecOC                  *
 * Function_Descripton  : This API returns the freshness*
 * value from the Most Significant Bits in the first    *
 * byte in the array (SecOCFreshnessValue),             *
 * in big endian format.                                *
 *******************************************************/
Std_ReturnType FVM_GetTxFreshness(uint16 SecOCFreshnessValueID, uint8* SecOCFreshnessValue,
uint32* SecOCFreshnessValueLength);



/*******************************************************
 *          * Function Info *                           *
 *                                                      *
 * Function_Name        : SecOC_GetRxFreshness          *
 * Function_Index       : 8.5.1 [SWS_SecOC_91007]       *
 * Function_File        : SWS of SecOC                  *
 * Function_Descripton  : This interface is used by the *
 *  SecOC to obtain the current freshness value.        *
 *******************************************************/
Std_ReturnType FVM_GetRxFreshness(
    uint16 SecOCFreshnessValueID, 
    const uint8* SecOCTruncatedFreshnessValue, 
    uint32 SecOCTruncatedFreshnessValueLength, 
    uint16 SecOCAuthVerifyAttempts,
    uint8* SecOCFreshnessValue,
    uint32* SecOCFreshnessValueLength 

);

/********************************************************
 *          * Function Info *                           *
 *                                                      *
 * Function_Name        : FVM_GetTxFreshnessTruncData   *
 * Function_Index       : 8.5.4 [SWS_SecOC_91003]       *
 * Function_File        : SWS of SecOC                  *
 * Function_Descripton  : This interface is used by the * 
 * SecOC to obtain the current freshness value. The     *
 * interface function provides also the truncated       *
 * freshness transmitted in the secured I-PDU.          *
 *******************************************************/
Std_ReturnType FVM_GetTxFreshnessTruncData (uint16 SecOCFreshnessValueID, uint8* SecOCFreshnessValue,
uint32* SecOCFreshnessValueLength, uint8* SecOCTruncatedFreshnessValue, uint32* SecOCTruncatedFreshnessValueLength);


#endif /* INCLUDE_FVM_H_ */
