
#include "SecOC.h"
#include "SecOC_Debug.h"
#include <pthread.h>
#include <stdlib.h>


void* tx_com()
{
    Com_MainTx();
}

void* tx_secoc()
{
    SecOCMainFunctionTx();
}

void* tx_tp()
{
    CanTp_MainFunction();
}
void* rx_ethernet()
{
    ethernet_RecieveMainFunction();
}

void* rx_tp()
{
    CanTP_MainFunctionRx();
}
void* rx_secoc()
{
    SecOCMainFunctionRx();
}



boolean create_thread (pthread_t *thread, *void fn() )
{
    if(pthread_create(thread , NULL, fn, NULL) != 0)
    {
        printf("error create thread");
        return 1;
    }
    return 0
}

boolean join_thread (pthread_t *thread)
{
    if(pthread_join(*thread,NULL))
    {
        printf("error join thread ");
        return 1;
    }
    return 0;
}


extern SecOC_ConfigType SecOC_Config;
int main(void)
{
    SecOC_Init(&SecOC_Config);
    pthread_t t[6];
    void (*fn_p[6])() = {tx_com, tx_secoc, tx_tp, rx_ethernet, rx_tp, rx_secoc};

    /* Creating Threads */
    for (int i = 0; i < 6; i++)
    {
        if (create_thread(&t[i], fn_p[i]) != 0)
        {
            printf("%d \n", i);
        }
    }   


    for (int i = 0; i < 6; i++)
    {
        if (join_thread(&t[i]) != 0)
        {
            printf("%d \n", i);
        }
    }   
    // #ifdef DEBUG_ALL
    //     SecOC_test();
    // #endif

    (void)printf("Program ran successfully\n");
    return 0;
}