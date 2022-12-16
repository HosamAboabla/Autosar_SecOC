#include "ethernet.h"


Std_ReturnType ethernet_send(unsigned char* data , unsigned char dataLen) {
    // create a socket
    int network_sockect;
    network_sockect = socket(AF_INET , SOCK_STREAM , 0);

    // specify an address for the socket
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT_NUMBER);
    server_address.sin_addr.s_addr = inet_addr("192.168.1.2");  //INADDR_ANY;

    int connection_status = connect(network_sockect , (struct sockaddr* ) &server_address , sizeof(server_address) );

    if (connection_status != 0) {
        return E_NOT_OK;
    }


    send(network_sockect , data , dataLen , 0);

    // close the connection
    close(network_sockect);
    return E_OK;
}