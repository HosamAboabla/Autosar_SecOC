#include "SecOC.h"
#
#include "SecOC_Lcfg.h"
#include <stdio.h>

extern SecOC_ConfigType SecOC_Config;

const SecOC_TxPduProcessingType     *SecOCTxPduProcessing;
const SecOC_RxPduProcessingType     *SecOCRxPduProcessing;
const SecOC_GeneralType             *SecOCGeneral;

void GUIInterface_init()
{
    SecOC_Init(&SecOC_Config);
}
