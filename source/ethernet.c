#include "ethernet.h"
#include "SecOC_Debug.h"

Std_ReturnType ethernet_send(unsigned short id, unsigned char* data , unsigned char dataLen) {
    // create a socket
    int network_sockect;
    network_sockect = socket(AF_INET , SOCK_STREAM , 0);

    // specify an address for the socket
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT_NUMBER);
    server_address.sin_addr.s_addr = INADDR_ANY; //inet_addr("192.168.1.2");

    int connection_status = connect(network_sockect , (struct sockaddr* ) &server_address , sizeof(server_address) );

    if (connection_status != 0) {
        return E_NOT_OK;
    }

    /* Prepare For Send */
    uint8 sendData[dataLen + sizeof(id)];
    (void)memcpy(sendData, data, dataLen);
    for(unsigned char indx = 0; indx < sizeof(id); indx++)
    {
        sendData[dataLen+indx] = (id >> (8 * indx));
    }


    #ifdef SECOC_DEBUG
        printf("### in Ethernet Send ###");
        for(int j = 0; j < (dataLen + sizeof(id)) ; j++)
            printf("%d\t",sendData[j]);
        printf("\n");
    #endif
    

    
    send(network_sockect , sendData , (dataLen + sizeof(id)) , 0);

    // close the connection
    close(network_sockect);
    return E_OK;

}

Std_ReturnType ethernet_receive(unsigned char* data , unsigned char dataLen, unsigned short* id)
{
    // create a socket
    int server_socket, client_socket;
    server_socket = socket(AF_INET , SOCK_STREAM , 0);

    // specify an address for the socket
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT_NUMBER);
    server_address.sin_addr.s_addr = INADDR_ANY; // inet_addr("192.168.1.2");


    // bind the socket to our specified IP and Port
    bind(server_socket , (struct sockaddr* ) &server_address , sizeof(server_address) );
    
    listen(server_socket , 5);

    client_socket = accept(server_socket , NULL , NULL);

    // Receive data
    unsigned char recData [dataLen + sizeof(unsigned short)];
    recv( client_socket , recData , (dataLen + sizeof(unsigned short)) , 0);
    #ifdef SECOC_DEBUG
        printf("######## in Recieve Ethernet ########\n");
        printf("Info Received: \n");
        for(int j  = 0 ; j < (dataLen+sizeof(unsigned short)) ; j++)
        {
            printf("%d ",recData[j]);
        }
        printf("\n\n\n");
    #endif
    


    (void)memcpy(id, recData+dataLen, sizeof(unsigned short));
    (void)memcpy(data, recData, dataLen);
    #ifdef SECOC_DEBUG
        printf("id = %d ###########################################\n\n",*id);
    #endif
    // close the socket
    close(server_socket);
    return E_OK;

}