
#include "SecOC.h"
#include <stdio.h>
#include "encrypt.h"

int main(void)
{
    SecOC_MainFunctionTx();
    uint32 data[16] = {'h','o','s','a' , 'm'};
    uint8 mac[16];
    uint32 macLen = 8;
    startEncryption(data , 8 , mac ,&macLen);

    printf("Encrypted message in hex:\n");
    for (int i = 0; i < macLen ; i++) {
        printf("%x ", mac[i]);
    }
    printf("\n");


    printf("Program ran successfully\n");
    return 0;
}