/***************************************************************************************************
  (c) NewTec GmbH 2024   -   www.newtec.de
***************************************************************************************************/
/**
 * @file       SearchingStartLineState.c
 *
 * Contains the functions and variables for the SearchingStartLineState.
 */
/**************************************************************************************************/

/* INCLUDES ***************************************************************************************/
#include "SearchingStartLineState.h"

/* CONSTANTS **************************************************************************************/
#define STARTING_SPEED 33u

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

/* VARIABLES **************************************************************************************/

/* EXTERNAL FUNCTIONS *****************************************************************************/

extern void SearchingStartLineState_enterStartTimer1AndStartDriving(void)
{
    SoftTimer_start(pTimer1, 8000U);

    DriveControl_drive(DRIVE_CONTROL_MOTOR_LEFT, STARTING_SPEED, DRIVE_CONTROL_FORWARD);
    DriveControl_drive(DRIVE_CONTROL_MOTOR_RIGHT, STARTING_SPEED, DRIVE_CONTROL_FORWARD);
}

extern void SearchingStartLineState_exitStartTimer2AndPlayBeepIfStartlineFound(void)
{

}

extern Bool SearchningStartLineState_checkTransitionTriggerStartlineFound(void)
{

}

extern Bool SearchningStartLineState_checkTransitionTriggerTimer1Exceeds8s(void)
{
    if (SOFTTIMER_IS_EXPIRED(pTimer1))
            {
                return TRUE;
            }
    return FALSE;
}

/* INTERNAL FUNCTIONS *****************************************************************************/