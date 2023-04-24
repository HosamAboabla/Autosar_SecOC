#ifndef INCLUDE_GUIINTERFACE_H_
#define INCLUDE_GUIINTERFACE_H_

/********************************************************************************************************/
/************************************************INCULDES************************************************/
/********************************************************************************************************/

#include <inttypes.h>


/********************************************************************************************************/
/*****************************************FunctionPrototype**********************************************/
/********************************************************************************************************/

void GUIInterface_init();

char* GUIInterface_authenticate(uint8_t configId, uint8_t *data, uint8_t len);
char* GUIInterface_verify(uint8_t configId);

uint8_t* GUIInterface_getSecuredPDU(uint8_t configId, uint8_t *len);

void GUIInterface_alterFreshness(uint8_t configId);
void GUIInterface_alterAuthenticator(uint8_t configId);

char* GUIInterface_transmit(uint8_t configId);
char* GUIInterface_receive(uint8_t configId);


#endif