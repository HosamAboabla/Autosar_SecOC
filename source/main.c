
#include "SecOC.h"
#include <stdio.h>
#include "encrypt.h"
#include "Csm.h"

int main(void)
{
    SecOC_MainFunctionTx();
    uint8 data[5] = {'h','o','s','a' , 'm'};

    uint8 mac[32];
    uint8 mac2[32];
    uint32 macLen = 32;
    uint32 macLen2 = 5;

    Csm_MacGenerate(1 , Crypto_stub , data , sizeof(data) , mac2 , &macLen2);

    printf("CSM Generated MAC:\n");
    for (int i = 0; i < macLen2 ; i++) {
        printf("%x ", mac2[i]);
    }
    printf("\n");

    startEncryption(data , sizeof(data) , mac , &macLen);

    printf("Encrypted message in hex:\n");
    for (int i = 0; i < macLen ; i++) {
        printf("%x ", mac[i]);
    }
    printf("\n");


    printf("Program ran successfully\n");
    return 0;
}