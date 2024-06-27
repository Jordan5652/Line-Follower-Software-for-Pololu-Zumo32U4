/***************************************************************************************************
  (c) NewTec GmbH 2024   -   www.newtec.de
***************************************************************************************************/
/**
 * @file       PreDriveState.c
 *
 * Contains the functions and variables for the PreDriveState.
 */
/**************************************************************************************************/

/* INCLUDES ***************************************************************************************/
#include "PreDriveState.h"

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

/* VARIABLES **************************************************************************************/

/* EXTERNAL FUNCTIONS *****************************************************************************/

extern void PreDriveState_enterStartTimer1AndWaitFor3s(void)
{
    SoftTimer_start(GlobalTimers_getTimer(TIMER1), THREE_SECONDS);
    Display_clear();
    Display_gotoxy(0,7);
    Display_write("PreDriveState", sizeof("PreDriveState"));
}

extern void PreDriveState_exitStopTimer1(void)
{
    SoftTimer_Stop(GlobalTimers_getTimer(TIMER1));
    Display_clear();
}

extern Bool PreDriveState_checkTransitionTriggerTimer1Exceeds3s(void)
{
    if (SOFTTIMER_IS_EXPIRED(GlobalTimers_getTimer(TIMER1)))
    {
        return TRUE;
    }
    return FALSE;
}

/* INTERNAL FUNCTIONS *****************************************************************************/