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
static Bool gOffTrack = FALSE;
static Bool gStartlineFound = FALSE;

/* EXTERNAL FUNCTIONS *****************************************************************************/

extern void DriveLapState_enterStartTimer3(void)
{
    gTrackLeft = FALSE;
    gOffTrack = FALSE;
}

extern void DriveLapState_processDriveOnTrackLine(void)
{ 
    // checking if line was left or line was refound 
    PositionControl_UpdateSensorValues();
    if((TRUE == PositionControl_checkForLineLost()) && (FALSE == gOffTrack))
    {
        Led_switchOn(LED_GREEN);
        SoftTimer_Stop(pTimer1);
        SoftTimer_start(pTimer1, 5000u);
        gOffTrack = TRUE;
        DriveControl_drive(DRIVE_CONTROL_MOTOR_LEFT, 0u, DRIVE_CONTROL_FORWARD);
        DriveControl_drive(DRIVE_CONTROL_MOTOR_RIGHT, 0u, DRIVE_CONTROL_FORWARD);
        Display_clear();
        Display_write("TRACKLINE LOST!", sizeof("TRACKLINE LOST!"));
        while(1);
        
    }

    else
    {
        if((FALSE == PositionControl_checkForLineLost()) && (TRUE == gOffTrack))
        {
            Led_switchOff(LED_GREEN);
            SoftTimer_Stop(pTimer1);
            gOffTrack = FALSE;
        }
    } 
     
    if(gOffTrack)
    {
        DriveControl_drive(DRIVE_CONTROL_MOTOR_RIGHT, pParameters->motorspeed, DRIVE_CONTROL_FORWARD);
        DriveControl_drive(DRIVE_CONTROL_MOTOR_LEFT, pParameters->motorspeed, DRIVE_CONTROL_FORWARD);
    }
    else
    {
        PositionControl_DriveOnTrack();
    }
    
    gStartlineFound = PositionControl_checkForStartLine();
}

extern Bool DriveLapState_checkTranstionTriggerTimer2Exceeds20s(void)
{
    if SOFTTIMER_IS_EXPIRED(pTimer2)
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
        if (gStartlineFound)
        {
            gStartlineFound = FALSE;
            return TRUE;
        }
        return FALSE;
}

extern Bool DriveLapState_checkTranstionTriggerTrackNotFound(void)
{
    if SOFTTIMER_IS_EXPIRED(pTimer1)
    {
        SoftTimer_Stop(pTimer1);
        gOffTrack = FALSE;
        return TRUE;
    }
    
    return FALSE;
}
/* INTERNAL FUNCTIONS *****************************************************************************/