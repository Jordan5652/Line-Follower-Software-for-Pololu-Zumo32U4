/***************************************************************************************************
  (c) NewTec GmbH 2024   -   www.newtec.de
***************************************************************************************************/
/**
 * @file       LapFinishedState.c
 *
 * Contains the functions and variables for the LapFinishedState.
 */
/**************************************************************************************************/

/* INCLUDES ***************************************************************************************/
#include "LapFinishedState.h"

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

/* VARIABLES **************************************************************************************/
static UInt16 gLapTimeCounter;
static UInt16 gLapTimeSec;
static UInt16 gLapTimeMilliSec;

static Bool gButtonAPressed = FALSE;

/* EXTERNAL FUNCTIONS *****************************************************************************/

extern void LapFinishedState_enterStopTimer2AndDisplayTimeAndStopDriveAndPlayBeep(void)
{
    gLapTimeCounter = SoftTimer_get(pTimer2);

    DriveControl_drive(DRIVE_CONTROL_MOTOR_LEFT, 0u, DRIVE_CONTROL_FORWARD);
    DriveControl_drive(DRIVE_CONTROL_MOTOR_RIGHT, 0u, DRIVE_CONTROL_FORWARD);

    SoftTimer_Stop(pTimer2);

    Buzzer_beep(BUZZER_NOTIFY);

    gLapTimeSec = gLapTimeCounter / 1000000;
    gLapTimeMilliSec = gLapTimeCounter % 1000000;

    static char gTimeStringSec[4];
    snprintf(gTimeStringSec, sizeof(gTimeStringSec), "%d", gLapTimeSec);
    static char gTimeStringMilliSec[4];
    snprintf(gTimeStringMilliSec, sizeof(gTimeStringSec), "%d", gLapTimeMilliSec);

    Display_write("TIME: ", sizeof("TIME: "));
    Display_write(gTimeStringSec, sizeof(gTimeStringSec));
    Display_write(",", sizeof(","));
    Display_write(gTimeStringMilliSec, sizeof(gTimeStringMilliSec));
    Display_write(" sec", sizeof(" sec"));
}

extern void LapFinishedState_processPollingButtonA(void)
{
    if(BUTTON_STATE_TRIGGERED == Button_getState(BUTTON_ID_A))
    {
        gButtonAPressed = TRUE;
    }
}

extern Bool LapFinishedState_checkTransitionTriggerButtonAPressed(void)
{
    if(TRUE == gButtonAPressed)
    {
        gButtonAPressed = FALSE;
        return TRUE;
    }
    return FALSE;
}

/* INTERNAL FUNCTIONS *****************************************************************************/