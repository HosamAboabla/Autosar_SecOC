
#include "SecOC.h"
#include "SecOC_Debug.h"
#include "GUIInterface.h"

int main(void)
{
    printf("GUI: started\n");

    GUIInterface_init();

    uint8_t data[] = {9, 9};
    uint8_t dataLen = sizeof(data);

    printf("GUI: Our data is: %d %d\n", data[0], data[1]);

    //Generate Frame
    GUIInterface_authenticate(0, data, dataLen);

    uint8_t securedLen = 0;
    uint8_t* secPdu = GUIInterface_getSecuredPDU(0, &securedLen);

    printf("GUI: Print secured PDU\n");
    for(int i = 0; i < securedLen; i++)
    {
        printf("%d ", secPdu[i]);
    }
    printf("\n");

    GUIInterface_alterFreshness(0);

    printf("GUI: Print secured PDU with altered freshness\n");
    for(int i = 0; i < securedLen; i++)
    {
        printf("%d ", secPdu[i]);
    }
    printf("\n");

    GUIInterface_alterAuthenticator(0);

    printf("GUI: Print secured PDU with altered authenticator\n");
    for(int i = 0; i < securedLen; i++)
    {
        printf("%d ", secPdu[i]);
    }
    printf("\n");

    printf("C Program ran successfully\n");
    return 0;
}