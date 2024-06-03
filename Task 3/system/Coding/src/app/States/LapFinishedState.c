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
#define NO_SPEED (0U)
#define ONE_SECOND (1000U)
#define TEXT_TIME ("TIME: ")
#define TEXT_COMMA (",")
#define TEXT_SEC (" sec")

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

/* VARIABLES **************************************************************************************/
/** Counter value from lap time timer */
static UInt16 gLapTimeCounter;

/** Seconds portion of the lap time */
static UInt16 gLapTimeSec;

/** Milliseconds portion of the lap time */
static UInt16 gLapTimeMilliSec;

/** Button trigger state of button A */
static Bool gButtonAPressed = FALSE;

/* EXTERNAL FUNCTIONS *****************************************************************************/

extern void LapFinishedState_enterStopTimer2AndDisplayTimeAndStopDriveAndPlayBeep(void)
{
    gLapTimeCounter = SoftTimer_get(pTimer2);

    DriveControl_drive(DRIVE_CONTROL_MOTOR_LEFT, NO_SPEED, DRIVE_CONTROL_FORWARD);
    DriveControl_drive(DRIVE_CONTROL_MOTOR_RIGHT, NO_SPEED, DRIVE_CONTROL_FORWARD);

    SoftTimer_Stop(pTimer2);

    Buzzer_beep(BUZZER_NOTIFY);

    gLapTimeSec = gLapTimeCounter / ONE_SECOND;
    gLapTimeMilliSec = gLapTimeCounter % ONE_SECOND;

    static char gTimeStringSec[4];
    snprintf(gTimeStringSec, sizeof(gTimeStringSec), "%d", gLapTimeSec);
    static char gTimeStringMilliSec[4];
    snprintf(gTimeStringMilliSec, sizeof(gTimeStringSec), "%d", gLapTimeMilliSec);

    Display_write(TEXT_TIME, sizeof(TEXT_TIME));
    Display_write(gTimeStringSec, sizeof(gTimeStringSec));
    Display_write(TEXT_COMMA, sizeof(TEXT_COMMA));
    Display_write(gTimeStringMilliSec, sizeof(gTimeStringMilliSec));
    Display_write(TEXT_SEC, sizeof(TEXT_SEC));
}

extern void LapFinishedState_processPollingButtonA(void)
{
    if (BUTTON_STATE_TRIGGERED == Button_getState(BUTTON_ID_A))
    {
        gButtonAPressed = TRUE;
    }
}

extern Bool LapFinishedState_checkTransitionTriggerButtonAPressed(void)
{
    if (TRUE == gButtonAPressed)
    {
        gButtonAPressed = FALSE;
        return TRUE;
    }
    return FALSE;
}

/* INTERNAL FUNCTIONS *****************************************************************************/