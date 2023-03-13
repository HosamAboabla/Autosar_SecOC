
#include "SecOC.h"
#include "SecOC_Debug.h"

int main(void)
{
    #ifdef SECOC_DEBUG
        SecOC_test();
    #endif

    printf("Program ran successfully\n");
    return 0;
}