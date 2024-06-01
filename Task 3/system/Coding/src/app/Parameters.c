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

void Parameters_setParameterSet(UInt8 index)
{
    gSelectedParameterSetIndex = index;
}

ParameterSet Parameters_getParameterSet(void)
{
    return gParameterSets[gSelectedParameterSetIndex];
}

/* INTERNAL FUNCTIONS *****************************************************************************/