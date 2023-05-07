/********************************************************************************************************/
/************************************************INCULDES************************************************/
/********************************************************************************************************/

#include "ethernet.h"
#include "SecOC_Debug.h"
#include "SecOC_Lcfg.h"
#include "CanTP.h"
#include "PduR_CanIf.h"
#include "SoAd.h"
#ifdef SCHEDULER_ON
    #include <pthread.h>
#endif 


/********************************************************************************************************/
/******************************************GlobalVaribles************************************************/
/********************************************************************************************************/

extern SecOC_PduCollection PdusCollections[];
#ifdef SCHEDULER_ON
    pthread_mutex_t lock;
#endif 

/********************************************************************************************************/
/********************************************Functions***************************************************/
/********************************************************************************************************/

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
    

    #ifdef SCHEDULER_ON
        pthread_mutex_lock(&lock);
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


void ethernet_RecieveMainFunction(void)
{
    static uint8 dataRecieve [BUS_LENGTH_RECEIVE];
    uint16 id;
    if ( ethernet_receive(dataRecieve , BUS_LENGTH_RECEIVE, &id) != E_OK )
    {
        return;
    }
    PduInfoType PduInfoPtr = {
        .SduDataPtr = dataRecieve,
        .MetaDataPtr = &PdusCollections[id],
        .SduLength = BUS_LENGTH_RECEIVE,
    };
    switch (PdusCollections[id].Type)
    {
    case SECOC_SECURED_PDU_CANIF:
        #ifdef ETHERNET_DEBUG
            printf("here in Direct \n");
        #endif
        PduR_CanIfRxIndication(id, &PduInfoPtr);
        break;
    case SECOC_SECURED_PDU_CANTP:
        #ifdef ETHERNET_DEBUG
            printf("here in CANTP \n");
        #endif
        CanTp_RxIndication(id, &PduInfoPtr);
        break;
    case SECOC_SECURED_PDU_SOADTP:
        #ifdef ETHERNET_DEBUG
            printf("here in Ethernet SOADTP \n");
        #endif
        SoAdTp_RxIndication(id, &PduInfoPtr);
        break;
    case SECOC_SECURED_PDU_SOADIF:
        #ifdef ETHERNET_DEBUG
            printf("here in Ethernet SOADIF \n");
        #endif
        PduR_SoAdIfRxIndication(id, &PduInfoPtr);
        break;
    
    case SECOC_AUTH_COLLECTON_PDU:
        #ifdef ETHERNET_DEBUG
            printf("here in Direct - pdu collection - auth\n");
        #endif
        PduR_CanIfRxIndication(id, &PduInfoPtr);
        break;
    case SECOC_CRYPTO_COLLECTON_PDU:
        #ifdef ETHERNET_DEBUG
            printf("here in Direct- pdu collection - crypto \n");
        #endif
        PduR_CanIfRxIndication(id, &PduInfoPtr);
        break;
    default:
        /* for saftey if id is out of range we must release mutex */
        #ifdef SCHEDULER_ON
            pthread_mutex_unlock(&lock);
        #endif 
        #ifdef ETHERNET_DEBUG
            printf("This is no type like it for ID : %d  type : %d \n", id, PdusCollections[id].Type);
        #endif
        break;
    }
}