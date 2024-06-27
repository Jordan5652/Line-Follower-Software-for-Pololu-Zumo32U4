/***************************************************************************************************
  (c) NewTec GmbH 2024   -   www.newtec.de
***************************************************************************************************/
/**
 * @file       DriveLapState.c
 *
 * Contains the functions and variables for the DriveLapState.
 */
/**************************************************************************************************/

/* INCLUDES ***************************************************************************************/
#include "DriveLapState.h"

#include "Led.h"

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

/* VARIABLES **************************************************************************************/
static Bool gTrackLeft = FALSE;

/* EXTERNAL FUNCTIONS *****************************************************************************/

extern void DriveLapState_enterStartTimer3(void)
{
    gTrackLeft = FALSE;

    SoftTimer_Stop(GlobalTimers_getTimer(TIMER3));
    SoftTimer_start(GlobalTimers_getTimer(TIMER3), 2000u);
    
}

extern void DriveLapState_processDriveOnTrackLine(void)
{ 
    static Bool OffTrack = FALSE;
    static UInt16 LineNotFoundCounter = 0u;
    ParameterSet* pParameters = Parameters_getParameterSet();
 
    PositionControl_UpdateSensorValues();
    if ((TRUE == PositionControl_checkForLineLost()))
    {
        LineNotFoundCounter = 0u;

        if (FALSE == OffTrack)
        {
            Led_switchOn(LED_YELLOW);
            SoftTimer_Stop(GlobalTimers_getTimer(TIMER1));
            SoftTimer_start(GlobalTimers_getTimer(TIMER1), 5000u);
            OffTrack = TRUE;
        }
        else
        {
            if (SOFTTIMER_IS_EXPIRED(GlobalTimers_getTimer(TIMER1)))
            {
                gTrackLeft = TRUE;
                SoftTimer_Stop(GlobalTimers_getTimer(TIMER1));
                LineNotFoundCounter = 0u;
            }
        }
    }

    else
    {
        if (OffTrack)
        {
            LineNotFoundCounter++;
            /* Measurement against Noise: preventing Softtimer to constantly stop due to noise of sensors (black line detected) */
            if (LineNotFoundCounter >= 100u)
            
            {
                Led_switchOff(LED_YELLOW);
                SoftTimer_Stop(GlobalTimers_getTimer(TIMER1));
                OffTrack = FALSE;
            }
        }
    } 
     
    if (OffTrack)
    {
        DriveControl_drive(DRIVE_CONTROL_MOTOR_RIGHT, pParameters->motorspeed, DRIVE_CONTROL_FORWARD);
        DriveControl_drive(DRIVE_CONTROL_MOTOR_LEFT, pParameters->motorspeed, DRIVE_CONTROL_FORWARD);
    }
    else
    {
        PositionControl_DriveOnTrack();
    }
    
}

extern Bool DriveLapState_checkTranstionTriggerTimer2Exceeds20s(void)
{
    if (SOFTTIMER_IS_EXPIRED(GlobalTimers_getTimer(TIMER2)))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }

}

extern Bool DriveLapState_checkTranstionTriggerStartlineFound(void)
{ 
    
    /* Wait some time to prevent immediatly finding startline after starting to drive */
    
    if (SOFTTIMER_IS_EXPIRED(GlobalTimers_getTimer(TIMER3)))
    {
        return PositionControl_checkForStartLine();   
    }
    else
    {
        return FALSE;
    }
    
}

extern Bool DriveLapState_checkTranstionTriggerTrackNotFound(void)
{
    if (gTrackLeft)
    {
        gTrackLeft = FALSE;
        Led_switchOff(LED_YELLOW);
        SoftTimer_Stop(GlobalTimers_getTimer(TIMER1));
        return TRUE;
    }
    
    return FALSE;
}
/* INTERNAL FUNCTIONS *****************************************************************************/