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
#define NUMBER_TO_CHAR_OFFSET (48u)

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/
static void convertTimeToText(char* string, UInt16 time);

/* VARIABLES **************************************************************************************/

/** Button trigger state of button A */
static Bool gButtonAPressed = FALSE;

/* EXTERNAL FUNCTIONS *****************************************************************************/

extern void LapFinishedState_enterDisplayTimeAndStopDriveAndPlayBeep(void)
{
    /* Counter value from lap time timer */
    UInt16 lapTimeCounter = SoftTimer_get(GlobalTimers_getTimer(TIMER2));

    DriveControl_drive(DRIVE_CONTROL_MOTOR_LEFT, NO_SPEED, DRIVE_CONTROL_FORWARD);
    DriveControl_drive(DRIVE_CONTROL_MOTOR_RIGHT, NO_SPEED, DRIVE_CONTROL_FORWARD);

    //SoftTimer_Stop(GlobalTimers_getTimer(TIMER2));

    Buzzer_beep(BUZZER_NOTIFY);

    /* Display lap time */
    lapTimeCounter = 20000u - lapTimeCounter;
    char timeString[8u]; 
    convertTimeToText(timeString, lapTimeCounter);
    Display_clear();
    Display_write(TEXT_TIME, sizeof(TEXT_TIME));
    Display_gotoxy(0,1);
    Display_write(timeString, sizeof(timeString));
    Display_gotoxy(0,0);
    
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
static void convertTimeToText(char* string, UInt16 time)
{
    UInt16 LapTimeSec = time / ONE_SECOND;
    UInt16 LapTimeMilliSec = time % ONE_SECOND;

    string[0] = (char)((LapTimeSec - (LapTimeSec % 10)) + NUMBER_TO_CHAR_OFFSET);
    string[1] = (char)((LapTimeSec % 10) + NUMBER_TO_CHAR_OFFSET);
    string[2] = ',';
    string[3] = (char)((LapTimeMilliSec / 100) + NUMBER_TO_CHAR_OFFSET);
    string[4] = (char)(((LapTimeMilliSec / 10) % 10) + NUMBER_TO_CHAR_OFFSET);
    string[5] = (char)((LapTimeMilliSec % 10) + NUMBER_TO_CHAR_OFFSET);
    string[6] = 's';
    string[7] = '\0';     

}