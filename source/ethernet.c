#include "ethernet.h"

void ethernet_send(unsigned char* data , unsigned char dataLen) {
    // create a socket
    int network_sockect;
    network_sockect = socket(AF_INET , SOCK_STREAM , 0);

    // specify an address for the socket
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT_NUMBER);
    server_address.sin_addr.s_addr = INADDR_ANY;

    int connection_status = connect(network_sockect , (struct sockaddr* ) &server_address , sizeof(server_address) );

    if (connection_status != 0) {
        printf("error can't connect : %d\n" , connection_status);
    }


    send(network_sockect , data , dataLen , 0);

    // close the connection
    close(network_sockect);
}