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

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

/* VARIABLES **************************************************************************************/

/** State of startline detection*/
static Bool gStartlineDetected = FALSE;


/* EXTERNAL FUNCTIONS *****************************************************************************/

extern void SearchingStartLineState_enterStartTimer1AndStartDriving(void)
{
    SoftTimer_start(pTimer1, FIVE_SECONDS);

    LineSensor_enableEmitter();
}

extern void SearchingStartLineState_processSearchForStartline(void)
{
    PositionControl_UpdateSensorValues();
    PositionControl_DriveOnTrack();
    gStartlineDetected = PositionControl_checkForStartLine();
}

extern void SearchingStartLineState_exitStartTimer2AndPlayBeepIfStartlineFound(void)
{
    /*Start timer for measuring lap time*/
    SoftTimer_start(pTimer2, 20000u);
    Buzzer_beep(BUZZER_NOTIFY);
}

extern Bool SearchningStartLineState_checkTransitionTriggerStartlineFound(void)
{
    if (gStartlineDetected)
    {
        gStartlineDetected = FALSE;
        return TRUE;
    }
    return FALSE;
}

extern Bool SearchningStartLineState_checkTransitionTriggerTimer1Exceeds5s(void)
{
    if (SOFTTIMER_IS_EXPIRED(pTimer1))
    {
        gStartlineDetected = FALSE;
        return TRUE;
    }
    return FALSE;
}

/* INTERNAL FUNCTIONS *****************************************************************************/