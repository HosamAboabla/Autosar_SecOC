#ifndef SECOC_DEBUG_H
#define SECOC_DEBUG_H

/********************************************************************************************************/
/************************************************INCULDES************************************************/
/********************************************************************************************************/

#include <stdio.h>        /*in order to use printf statements for debugging*/

/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/

#define RELEASE                    

#define DEBUG_ALL                   /*Comment this line if you want to Release your code*/

#ifdef DEBUG_ALL
#undef RELEASE
#define SECOC_DEBUG                 /* Debug for SecOC */
#define FV_DEBUG                    /* Debug for FreshnessValueManger */
#define CANIF_DEBUG                 /* Debug for CanIF */
#define CANTP_DEBUG                 /* Debug for CanTP */
#define COM_DEBUG                   /* Debug for COM */
#define DCM_DEBUG                   /* Debug for DCM */ 
#define SOAD_DEBUG                  /* Debug for SoAd */ 
#define ETHERNET_DEBUG              /* Debug for Ethernet */ 
#define PDUR_DEBUG                  /* Debug for PduR */ 
#define COUNTERS_DEBUG              /* Debug for Auth && verify Counters */  
#define MAC_DEBUG                   /* Debug for MAC gerenration */  
#define PDU_COLLECTION_DEBUG        /* Debug for PDU Collection */  
#define SCHEDULER_DEBUG             /* Debug for Schedular */  
#endif

/*#define SCHEDULER_ON*/

#endif