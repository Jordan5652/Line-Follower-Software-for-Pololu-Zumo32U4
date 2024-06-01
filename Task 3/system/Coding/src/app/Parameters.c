/***************************************************************************************************
  (c) NewTec GmbH 2024   -   www.newtec.de
***************************************************************************************************/
/**
 * @file       Parameters.c
 *
 * contains the functions to set, get and display the ParameterSet.
 */
/**************************************************************************************************/

/* INCLUDES ***************************************************************************************/
#include "Parameters.h"
#include "Display.h"

/* CONSTANTS **************************************************************************************/
#define MAX_NUMBER_OF_PARAMETER_SETS 3
/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

/* VARIABLES **************************************************************************************/

static ParameterSet gParameterSets[MAX_NUMBER_OF_PARAMETER_SETS];

static UInt8 gSelectedParameterSetIndex;

/* EXTERNAL FUNCTIONS *****************************************************************************/

extern void Parameters_setParameterSet(UInt8 index)
{
    gSelectedParameterSetIndex = index;
}

extern ParameterSet Parameters_getParameterSet(void)
{
    return gParameterSets[gSelectedParameterSetIndex];
}

extern void Parameters_initParameterSets(void)
{
    gParameterSets[0].kp = 0.03;
    gParameterSets[0].ki = 0;
    gParameterSets[0].kd = 0;
    gParameterSets[0].motorspeed = 50;
}

/* INTERNAL FUNCTIONS *****************************************************************************/