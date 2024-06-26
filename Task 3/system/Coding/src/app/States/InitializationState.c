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
    /* Display team name */
    Display_clear();
    Display_write(TEAM_NAME, sizeof(TEAM_NAME));

    /* Register all timers for future usage */
    SoftTimerHandler_register(GlobalTimers_getTimer(TIMER1));
    SoftTimerHandler_register(GlobalTimers_getTimer(TIMER2));
    SoftTimerHandler_register(GlobalTimers_getTimer(TIMER3));

    /* Start timer to transition into next state */
    SoftTimer_start(GlobalTimers_getTimer(TIMER1), TWO_SECONDS);

    Parameters_initParameterSets();
}

extern void InitializationState_exitStopTimer1(void)
{
    Display_clear();
    SoftTimer_Stop(GlobalTimers_getTimer(TIMER1));
}

extern Bool InitializationState_checkTransitionTriggerTimer1Exceeds2s(void)
{
    if (SOFTTIMER_IS_EXPIRED(GlobalTimers_getTimer(TIMER1)))
    {
        return TRUE;
    }
    return FALSE;
}

/* INTERNAL FUNCTIONS *****************************************************************************/