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
#define STARTING_SPEED 80u
#define AVERAGE_THRESHHOLD 281u

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

/* VARIABLES **************************************************************************************/

static LineSensorValues gLineSensorValues;
static Bool gStartlineDetected = FALSE;
static ParameterSet gStartingParameters;

/* EXTERNAL FUNCTIONS *****************************************************************************/

extern void SearchingStartLineState_enterStartTimer1AndStartDriving(void)
{   
    Int8 buffer[] = "SearchingStartlineState";
    Display_clear();
    Display_write(buffer, sizeof(buffer));
    SoftTimer_start(pTimer1, 8000000U);

    //DriveControl_drive(DRIVE_CONTROL_MOTOR_LEFT, STARTING_SPEED, DRIVE_CONTROL_FORWARD);
    //DriveControl_drive(DRIVE_CONTROL_MOTOR_RIGHT, STARTING_SPEED, DRIVE_CONTROL_FORWARD);

    gStartingParameters.kp = 0.4;
    gStartingParameters.ki = 0;
    gStartingParameters.kd = 0;
    gStartingParameters.motorspeed = 50;

    LineSensor_enableEmitter();
}

extern void SearchingStartLineState_processSearchForStartline(void)
{
    PositionControl_DriveOnTrack(gStartingParameters);

    LineSensor_read(&gLineSensorValues);

    static UInt16 gLineSensorAverage = 0;
    static UInt8 gCounter;
    for(gCounter = 0; gCounter < LINESENSOR_COUNT; gCounter++)
    {
        if(gCounter == 0 || gCounter == 2  || gCounter == 4)
        {
            gLineSensorAverage += gLineSensorValues.value[gCounter]*4;
        }
        else 
        {
            gLineSensorAverage += gLineSensorValues.value[gCounter];
        }
    }
    gLineSensorAverage /= 14;

    if(AVERAGE_THRESHHOLD < gLineSensorAverage)
    {
        gStartlineDetected = TRUE;
    }

    /*For Testing*/
    char av[5];
    snprintf(av, sizeof(av), "%d", gLineSensorAverage);
    
    Display_clear();
    Display_gotoxy(0, 1);
    Display_write(av, sizeof(av));
    /*For Testing End*/
}

extern void SearchingStartLineState_exitStartTimer2AndPlayBeepIfStartlineFound(void)
{
    /*Start timer for measuring track time*/
    SoftTimer_start(pTimer2, 20000u);
    Buzzer_beep(BUZZER_NOTIFY);
}

extern Bool SearchningStartLineState_checkTransitionTriggerStartlineFound(void)
{
    if(gStartlineDetected)
    {
        gStartlineDetected = FALSE;
        return TRUE;
    }
    return FALSE;
}

extern Bool SearchningStartLineState_checkTransitionTriggerTimer1Exceeds8s(void)
{
    if (SOFTTIMER_IS_EXPIRED(pTimer1))
    {
        gStartlineDetected = FALSE;
        //return TRUE;
    }
    return FALSE;
}

/* INTERNAL FUNCTIONS *****************************************************************************/