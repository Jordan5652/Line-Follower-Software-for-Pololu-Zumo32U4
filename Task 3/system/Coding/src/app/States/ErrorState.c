
/***************************************************************************************************
  (c) NewTec GmbH 2024   -   www.newtec.de
***************************************************************************************************/
/**
 * @file       ErrorState.c
 *
 * Contains the functions and variables for the ErrorState.
 */
/**************************************************************************************************/

/* INCLUDES ***************************************************************************************/
#include "ErrorState.h"

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

/* VARIABLES **************************************************************************************/
static Bool gButtonTriggered = FALSE;

/* EXTERNAL FUNCTIONS *****************************************************************************/

extern void ErrorState_enterStopDriveAndPlayAlarmAndDisplayError(ErrorHandlerErrorCode errorCode)
{
    // TODO  ErrorHandlerErrorCode errorcode rausfinden den richtignen   
    DriveControl_drive(DRIVE_CONTROL_MOTOR_LEFT, 0, DRIVE_CONTROL_FORWARD);
    DriveControl_drive(DRIVE_CONTROL_MOTOR_RIGHT, 0, DRIVE_CONTROL_BACKWARD);
    ErrorHandler_show(errorCode);
    Buzzer_beep(BUZZER_ALARM);
}

extern void ErrorState_processPollingButtonA(void)
{
    if (BUTTON_STATE_TRIGGERED == Button_getState(BUTTON_ID_A))
    {
        gButtonTriggered = TRUE;
        Display_clear();
    }
}

extern Bool ErrorState_checkTransitionTriggerButtonAPressed(void)
{
    if (TRUE == gButtonTriggered)
    {
        gButtonTriggered = FALSE;
        return TRUE;
    } 
    return FALSE;
}

/* INTERNAL FUNCTIONS *****************************************************************************/
