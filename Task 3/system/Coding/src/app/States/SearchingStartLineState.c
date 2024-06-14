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

/* MACROS *****************************************************************************************/
#define FIVE_SECONDS (5000u)

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

/* VARIABLES **************************************************************************************/

/** State of startline detection*/
static Bool gStartlineDetected = FALSE;


/* EXTERNAL FUNCTIONS *****************************************************************************/

extern void SearchingStartLineState_enterStartTimer1AndStartDriving(void)
{
    
    Int8 buffer[] = "SearchingStartlineState";
    Display_clear();
    Display_write(buffer, sizeof(buffer));
    

    SoftTimer_start(pTimer1, FIVE_SECONDS);

    LineSensor_enableEmitter();
}

extern void SearchingStartLineState_processSearchForStartline(void)
{
    /*
    LineSensor_read(&gLineSensorValues);
    gLineSensorAverage = 0;
    for (UInt8 gCounter = 0; gCounter < LINESENSOR_COUNT; gCounter++)
    {
        if (gCounter == 0 || gCounter == 2  || gCounter == 4)
        {
            gLineSensorAverage += gLineSensorValues.value[gCounter]*4;
        }
        else
        {
            gLineSensorAverage += gLineSensorValues.value[gCounter];
        }
    }
    gLineSensorAverage /= 14;

    if (AVERAGE_THRESHHOLD < gLineSensorAverage)
    {
        gStartlineDetected = TRUE;
    }
    */
    PositionControl_UpdateSensorValues();
    PositionControl_DriveOnTrack();
    gStartlineDetected = PositionControl_checkForStartLine();
}

extern void SearchingStartLineState_exitStartTimer2AndPlayBeepIfStartlineFound(void)
{
    /*Start timer for measuring track time*/
    SoftTimer_start(pTimer2, 20000u);
    Buzzer_beep(BUZZER_NOTIFY);
}

extern Bool SearchningStartLineState_checkTransitionTriggerStartlineFound(void)
{
    if (gStartlineDetected)
    {
        gStartlineDetected = FALSE;
        Display_clear();
        return TRUE;
    }
    return FALSE;
}

extern Bool SearchningStartLineState_checkTransitionTriggerTimer1Exceeds5s(void)
{
    if (SOFTTIMER_IS_EXPIRED(pTimer1))
    {
        gStartlineDetected = FALSE;
        Display_clear();
        return TRUE;
    }
    return FALSE;
}

/* INTERNAL FUNCTIONS *****************************************************************************/