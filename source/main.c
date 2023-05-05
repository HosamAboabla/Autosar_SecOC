
#include "SecOC.h"
#include "SecOC_Debug.h"
#include "Scheduler.h"


extern SecOC_ConfigType SecOC_Config;
int main(void)
{
    SecOC_Init(&SecOC_Config);
    Scheduler_Start();
    return 0;
}