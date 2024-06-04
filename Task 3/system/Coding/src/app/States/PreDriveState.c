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
#define THREE_SECONDS (3000U)

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

/* VARIABLES **************************************************************************************/

/* EXTERNAL FUNCTIONS *****************************************************************************/

extern void PreDriveState_enterStartTimer1AndWaitFor3s(void)
{
    Int8 buffer[] = "PreDriveState";
    Display_clear();
    Display_write(buffer, sizeof(buffer));
    
    SoftTimer_start(pTimer1, THREE_SECONDS);
}

extern void PreDriveState_exitStopTimer1(void)
{
    SoftTimer_Stop(pTimer1);
}

extern Bool PreDriveState_checkTransitionTriggerTimer1Exceeds3s(void)
{
    if (SOFTTIMER_IS_EXPIRED(pTimer1))
    {
        return TRUE;
    }
    return FALSE;
}

/* INTERNAL FUNCTIONS *****************************************************************************/