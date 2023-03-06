#ifndef SENDER_H__
#define SENDER_H__

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "Std_Types.h"

#define PORT_NUMBER 12345

Std_ReturnType ethernet_send(unsigned short id, unsigned char* data , unsigned char dataLen);

Std_ReturnType ethernet_receive(unsigned char* data , unsigned char dataLen, unsigned short* id);




#endif
