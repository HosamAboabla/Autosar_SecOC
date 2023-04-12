
#include "SecOC.h"
#include "SecOC_Debug.h"
#include "GUIInterface.h"

int main(void)
{
    printf("GUI: started\n");

    GUIInterface_init();

    uint8_t data[] = {9, 9};
    printf("GUI: Our data is: %d %d\n", data[0], data[1]);
    //Generate Frame
    GUIInterface_authenticate(0, data, 2);

    uint8_t securedlen = 0;
    uint8_t* secpdu = GUIInterface_getSecuredPDU(0, &securedlen);

    printf("GUI: Print secured PDU\n");
    for(int i = 0; i < securedlen; i++)
    {
        printf("%d ", secpdu[i]);
    }
    printf("\n");

    GUIInterface_alterFreshness(0);

    printf("GUI: Print secured PDU with altered freshness\n");
    for(int i = 0; i < securedlen; i++)
    {
        printf("%d ", secpdu[i]);
    }
    printf("\n");

    GUIInterface_alterAuthenticator(0);

    printf("GUI: Print secured PDU with altered authenticator\n");
    for(int i = 0; i < securedlen; i++)
    {
        printf("%d ", secpdu[i]);
    }
    printf("\n");

    (void)printf("Program ran successfully\n");
    return 0;
}