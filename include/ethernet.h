#ifndef SENDER_H__
#define SENDER_H__

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT_NUMBER 12345

void ethernet_send(unsigned char* data , unsigned char dataLen);


#endif
