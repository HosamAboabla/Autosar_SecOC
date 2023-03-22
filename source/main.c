
#include "SecOC.h"
#include "SecOC_Debug.h"

int main(void)
{
    #ifdef DEBUG_ALL
        SecOC_test();
    #endif
    (void)printf("Program ran successfully\n");
    return 0;
}