#include "ethernet.h"
#include "SecOC_Debug.h"
#include "SecOC_Lcfg.h"
#include "CanTP.h"
#include "PduR_CanIf.h"

Std_ReturnType ethernet_send(unsigned short id, unsigned char* data , unsigned char dataLen) {
    #ifdef ETHERNET_DEBUG
        printf("######## in Sent Ethernet\n");
    #endif
    /* create a socket*/
    int network_sockect;
    if ( (    network_sockect = socket(AF_INET , SOCK_STREAM , 0)) < 0)
    {
        #ifdef ETHERNET_DEBUG
            printf("Create Socket Error\n");
        #endif
        return E_NOT_OK;
    }

    /* specify an address for the socket*/
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT_NUMBER);
    server_address.sin_addr.s_addr = INADDR_ANY; /*inet_addr("192.168.1.2");*/  

    int connection_status = connect(network_sockect , (struct sockaddr* ) &server_address , sizeof(server_address) );

    if (connection_status != 0) {
        #ifdef ETHERNET_DEBUG
            printf("Connection Error\n");
        #endif
        return E_NOT_OK;

    }

    /* Prepare For Send */
    uint8 sendData[BUS_LENGTH_RECEIVE + sizeof(id)] = {0};
    (void)memcpy(sendData, data, dataLen);
    for(unsigned char indx = 0; indx < sizeof(id); indx++)
    {
        sendData[BUS_LENGTH_RECEIVE+indx] = (id >> (8 * indx));
    }


    #ifdef ETHERNET_DEBUG
        for(int j = 0; j < 10 ; j++)
            printf("%d\t",sendData[j]);
        printf("\n");
    #endif
    

    
    send(network_sockect , sendData , 10 , 0);

    /* close the connection*/
    close(network_sockect);
    return E_OK;

}

Std_ReturnType ethernet_receive(unsigned char* data , unsigned char dataLen, unsigned short* id)
{
    
    #ifdef ETHERNET_DEBUG
        printf("######## in Recieve Ethernet\n");
    #endif
    /* create a socket*/
    int server_socket, client_socket;
    if ( ( server_socket = socket(AF_INET , SOCK_STREAM , 0)) < 0)
    {
        #ifdef ETHERNET_DEBUG
            printf("Create Socket Error\n");
        #endif
        return E_NOT_OK;

    }

    /* specify an address for the socket*/
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT_NUMBER);
    server_address.sin_addr.s_addr = INADDR_ANY; /* inet_addr("192.168.1.2");*/

    
    int opt = 1; 
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
    { 
        #ifdef ETHERNET_DEBUG
            printf("connect setsockopt Error \n"); 
        #endif
        return E_NOT_OK;

    }
    
    /* bind the socket to our specified IP and Port*/
   
    if ( ( bind(server_socket , (struct sockaddr* ) &server_address , sizeof(server_address) )) < 0)
    {
        #ifdef ETHERNET_DEBUG
            printf("Bind Error\n");
        #endif
        return E_NOT_OK;

    }

    

    if ( (listen(server_socket , 5)) < 0)
    {
        #ifdef ETHERNET_DEBUG
            printf("Listen Error\n");
        #endif
        return E_NOT_OK;

    }
   
    if ( ( client_socket = accept(server_socket , NULL , NULL)) < 0)
    {
        #ifdef ETHERNET_DEBUG
            printf("Accept Error\n");
        #endif
        return E_NOT_OK;
    }
    /* Receive data*/
    unsigned char recData [dataLen + sizeof(unsigned short)];
    recv( client_socket , recData , (dataLen + sizeof(unsigned short)) , 0);
    #ifdef ETHERNET_DEBUG
        printf("in Recieve Ethernet \t");
        printf("Info Received: \n");
        for(int j  = 0 ; j < (dataLen+sizeof(unsigned short)) ; j++)
        {
            printf("%d ",recData[j]);
        }
        printf("\n\n\n");
    #endif
    


    (void)memcpy(id, recData+dataLen, sizeof(unsigned short));
    (void)memcpy(data, recData, dataLen);
    #ifdef ETHERNET_DEBUG
        printf("id = %d \n",*id);
    #endif
    /* close the socket*/
    close(server_socket);
    return E_OK;

}


communicate_Types RxComTypes[SECOC_NUM_OF_RX_PDU_PROCESSING] =
{
    CANIF,
    CANTP,
    SOAD,
    CANIF,
    CANTP
};

void ethernet_RecieveMainFunction(void)
{
    uint8 dataRecieve [BUS_LENGTH_RECEIVE];
    uint16 id;
    ethernet_receive(dataRecieve , BUS_LENGTH_RECEIVE, &id);
    PduInfoType PduInfoPtr = {
        .SduDataPtr = dataRecieve,
        .MetaDataPtr = &RxComTypes[id],
        .SduLength = BUS_LENGTH_RECEIVE,
    };
    if (RxComTypes[id] == CANIF)
    {
        #ifdef ETHERNET_DEBUG
            printf("here in Direct \n");
        #endif
        PduR_CanIfRxIndication(id, &PduInfoPtr);
    }
    else if (RxComTypes[id] == CANTP)
    {
        #ifdef ETHERNET_DEBUG
            printf("here in CANTP \n");
        #endif
        CanTp_RxIndication(id, &PduInfoPtr);
    }
    else if (RxComTypes[id] == SOAD)
    {
        // soAd interface
    }
    else if(RxComTypes[id] == FRIF)
    {
        // FRIF interface
    }
    
}