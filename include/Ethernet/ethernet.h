#ifndef SENDER_H__
#define SENDER_H__

/********************************************************************************************************/
/************************************************INCULDES************************************************/
/********************************************************************************************************/

#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "Std_Types.h"
#include <string.h>


/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/

#define PORT_NUMBER 12345
#define BUS_LENGTH_RECEIVE 8


/********************************************************************************************************/
/*****************************************FunctionPrototype**********************************************/
/********************************************************************************************************/

/*******************************************************
 *          * Function Info *                           *
 *                                                      *
 * Function_Name        : ethernet_send                 *
 * Function_Index       :                               *
 * Function_File        :                               *
 * Function_Descripton  : Used to send the data using   *
 * Sockets                                              *
 *******************************************************/
Std_ReturnType ethernet_send(unsigned short id, unsigned char* data , unsigned char dataLen);


/*******************************************************
 *          * Function Info *                           *
 *                                                      *
 * Function_Name        : ethernet_send                 *
 * Function_Index       :                               *
 * Function_File        :                               *
 * Function_Descripton  : Used to Receive the data using*
 * Sockets                                              *
 *******************************************************/
Std_ReturnType ethernet_receive(unsigned char* data , unsigned char dataLen, unsigned short* id);


/*******************************************************
 *          * Function Info *                           *
 *                                                      *
 * Function_Name        : ethernet_RecieveMainFunction  *
 * Function_Index       :                               *
 * Function_File        :                               *
 * Function_Descripton  : Used to route the data        *
 * Received to protocol                                 *
 *******************************************************/
void ethernet_RecieveMainFunction(void);

#endif
