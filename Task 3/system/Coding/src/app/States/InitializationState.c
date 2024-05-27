/***************************************************************************************************
  (c) NewTec GmbH 2024   -   www.newtec.de
***************************************************************************************************/
/**
 * @file       InitializationState.c
 *
 * Contains the functions and variables for the InitializationState.
 */
/**************************************************************************************************/

/* INCLUDES ***************************************************************************************/


#include "InitializationState.h"

/* CONSTANTS **************************************************************************************/
#define TEAM_NAME "Innov8tive Inc.\n" 

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

/* VARIABLES **************************************************************************************/

/* EXTERNAL FUNCTIONS *****************************************************************************/

extern void InitializationState_enterDisplayNameAndStartTimer1(void)
{
    UInt8 buffer[] = TEAM_NAME;
    Display_clear();
    Display_write(buffer, sizeof(buffer));
    SoftTimer_start(pTimer1, 2000u);
}

extern void InitializationState_exitStopTimer1(void)
{
    SoftTimer_Stop(&)
}

extern Bool InitializationState_checkTransitionTriggerTimer1Exceeds2s(void)
{
    if (SOFTTIMER_IS_EXPIRED(pTimer1))
    {
        return true;
    }
    return false;
}

/* INTERNAL FUNCTIONS *****************************************************************************/