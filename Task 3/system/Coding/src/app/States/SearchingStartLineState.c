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
#define AVERAGE_THRESHHOLD 300u

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

/* VARIABLES **************************************************************************************/

static LineSensorValues gLineSensorValues;
static Bool gStartlineDetected = FALSE;

/* EXTERNAL FUNCTIONS *****************************************************************************/

extern void SearchingStartLineState_enterStartTimer1AndStartDriving(void)
{
    SoftTimer_start(pTimer1, 8000U);

    DriveControl_drive(DRIVE_CONTROL_MOTOR_LEFT, STARTING_SPEED, DRIVE_CONTROL_FORWARD);
    DriveControl_drive(DRIVE_CONTROL_MOTOR_RIGHT, STARTING_SPEED, DRIVE_CONTROL_FORWARD);

    LineSensor_enableEmitter();
}

extern void SearchingStartLineState_processSearchForStartline(void)
{
    LineSensor_read(&gLineSensorValues);

    static UInt16 gLineSenorAverage = 0;
    static UInt8 gCounter;
    for(gCounter = 0; gCounter < LINESENSOR_COUNT; gCounter++)
    {
        gLineSenorAverage += gLineSensorValues.value[gCounter];
    }

    if(AVERAGE_THRESHHOLD < gLineSenorAverage)
    {
        gStartlineDetected = TRUE;
    }
}

extern void SearchingStartLineState_exitStartTimer2AndPlayBeepIfStartlineFound(void)
{
    if(gStartlineDetected)
    {
        /*Start timer for measuring track time*/
        SoftTimer_start(pTimer2, 20000u);
        Buzzer_beep(BUZZER_NOTIFY);
    }
}

extern Bool SearchningStartLineState_checkTransitionTriggerStartlineFound(void)
{
    return gStartlineDetected;
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