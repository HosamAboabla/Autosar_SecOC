#ifndef SECOC_DEBUG_H
#define SECOC_DEBUG_H

#include <stdio.h>        /*in order to use printf statements for debugging*/

#define DEBUG_ALL         /*Comment this line if you want to deploy your code*/

#ifdef DEBUG_ALL
#define SECOC_DEBUG       /* Debug for SecOC */
#define FV_DEBUG          /* Dubeg for FreshnessValueManger */
#define CANIF_DEBUG       /* Dubeg for CanIF */
#define CANTP_DEBUG       /* Dubeg for CanTP */
#define COM_DEBUG         /* Dubeg for COM */
#define DCM_DEBUG         /* Dubeg for DCM */ 
#define SOAD_DEBUG        /* Dubeg for SoAd */ 
#define ETHERNET_DEBUG    /* Dubeg for Ethernet */ 
#define PDUR_DEBUG        /* Dubeg for PduR */ 
#define COUNTERS_DEBUG    /* Debug for Auth && verify Counters */   
#endif


#endif