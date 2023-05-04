

#include "SecOC.h"
#include "SecOC_Debug.h"
#include "Scheduler.h"


extern SecOC_ConfigType SecOC_Config;
int main()
 {
    SecOC_Init(&SecOC_Config);
    scheduler_Init();
    return 0;
}