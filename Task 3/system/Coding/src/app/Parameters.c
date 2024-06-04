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

/* CONSTANTS **************************************************************************************/

#define MAX_NUMBER_OF_PARAMETER_SETS 3u
#define TEXT_SET1 ("A: NAME SET 1")
#define TEXT_SET2 ("B: NAME SET 2")
#define TEXT_SET3 ("C: NAME SET 3")
/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

/* VARIABLES **************************************************************************************/
/** array of the choosable parameter sets */
static ParameterSet gParameterSets[MAX_NUMBER_OF_PARAMETER_SETS];

ParameterSet* pParameters = &gParameterSets[INDEX_SET1];

/* EXTERNAL FUNCTIONS *****************************************************************************/

extern void Parameters_setParameterSet(UInt8 index)
{
    pParameters = &gParameterSets[index];
}

extern void Parameters_displayParameterSets(void)
{
    Display_clear();
    Display_gotoxy(0, 0);
    Display_write(TEXT_SET1, sizeof(TEXT_SET1));
    Display_gotoxy(0, 1);
    Display_write(TEXT_SET2, sizeof(TEXT_SET2));
    Display_gotoxy(0, 2);
    Display_write(TEXT_SET3, sizeof(TEXT_SET3));
}

extern void Parameters_initParameterSets(void)
{
    /** Init of set 1 */
    gParameterSets[0].kp = 0.1;
    gParameterSets[0].ki = 0;
    gParameterSets[0].kd = 0;
    gParameterSets[0].motorspeed = 50;

    /** Init of set 2 */
    gParameterSets[1].kp = 0.03;
    gParameterSets[1].ki = 0;
    gParameterSets[1].kd = 0;
    gParameterSets[1].motorspeed = 50;

    /** Init of set 3 */
    gParameterSets[2].kp = 0.03;
    gParameterSets[2].ki = 0;
    gParameterSets[2].kd = 0;
    gParameterSets[2].motorspeed = 50;
}

/* INTERNAL FUNCTIONS *****************************************************************************/