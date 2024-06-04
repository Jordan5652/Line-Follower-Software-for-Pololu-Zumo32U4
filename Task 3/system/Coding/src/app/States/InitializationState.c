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
    /** Display team name */
    Char buffer[20] = TEAM_NAME;
    Display_clear();
    Display_write(buffer, sizeof(buffer));

    /** Register all timers for future usage */
    SoftTimerHandler_register(pTimer1);
    SoftTimerHandler_register(pTimer2);
    SoftTimerHandler_register(pTimer3);

    /** Start timer to transition into next state */
    SoftTimer_start(pTimer1, 2000u);

    Parameters_initParameterSets();
}

extern void InitializationState_exitStopTimer1(void)
{
    Display_clear();
    SoftTimer_Stop(pTimer1);
}

extern Bool InitializationState_checkTransitionTriggerTimer1Exceeds2s(void)
{
    if (SOFTTIMER_IS_EXPIRED(pTimer1))
    {
        return TRUE;
    }
    return FALSE;
}

/* INTERNAL FUNCTIONS *****************************************************************************/