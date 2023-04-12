#ifndef INCLUDE_GUIINTERFACE_H_
#define INCLUDE_GUIINTERFACE_H_

#include <inttypes.h>

void GUIInterface_init();

char* GUIInterface_authenticate(uint8_t configId, uint8_t *data, uint8_t len);

uint8_t* GUIInterface_getSecuredPDU(uint8_t configId, uint8_t *len);


#endif