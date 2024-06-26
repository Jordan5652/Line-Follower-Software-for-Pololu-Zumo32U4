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
    //gOffTrack = FALSE;

    SoftTimer_Stop(pTimer3);
    SoftTimer_start(pTimer3, 2000u);

}

#include <stdio.h>


extern void DriveLapState_processDriveOnTrackLine(void)
{ 
    static Bool OffTrack = FALSE;
    static UInt16 LineNotFoundCounter = 0u;
    ParameterSet* pParameters = Parameters_getParameterSet();

    // checking if line was left or line was refound 
    PositionControl_UpdateSensorValues();
    if((TRUE == PositionControl_checkForLineLost())) // && (FALSE == OffTrack))
    {
        LineNotFoundCounter = 0u;

        if(FALSE == OffTrack)
        {
            Led_switchOn(LED_YELLOW);
            SoftTimer_Stop(pTimer1);
            SoftTimer_start(pTimer1, 5000u);
            OffTrack = TRUE;
            //DriveControl_drive(DRIVE_CONTROL_MOTOR_LEFT, 0u, DRIVE_CONTROL_FORWARD);
            //DriveControl_drive(DRIVE_CONTROL_MOTOR_RIGHT, 0u, DRIVE_CONTROL_FORWARD);
            //Display_clear();
            //Display_write("TRACKLINE LOST!", sizeof("TRACKLINE LOST!"));
            //while(1);
        }
        else
        {
            //Counter++;
            if SOFTTIMER_IS_EXPIRED(pTimer1)
            {
                gTrackLeft = TRUE;
                SoftTimer_Stop(pTimer1);
                LineNotFoundCounter = 0u;
                
                //DriveControl_drive(DRIVE_CONTROL_MOTOR_LEFT, 0u, DRIVE_CONTROL_FORWARD);
                //DriveControl_drive(DRIVE_CONTROL_MOTOR_RIGHT, 0u, DRIVE_CONTROL_FORWARD);
                //Display_clear();
                //Display_write("YAY FINALLY!", sizeof("YAY FINALLY!"));
                //while(1);
            }

            /*
            if(Counter >= 20u)
            {
                
                DriveControl_drive(DRIVE_CONTROL_MOTOR_LEFT, 0u, DRIVE_CONTROL_FORWARD);
                DriveControl_drive(DRIVE_CONTROL_MOTOR_RIGHT, 0u, DRIVE_CONTROL_FORWARD);
                char buffer[8];
                UInt16 timerValue = SoftTimer_get(pTimer1);
                snprintf(buffer, sizeof(buffer), "%u", timerValue);
                Display_clear();
                Display_write("TRACKLINE LOST!", sizeof("TRACKLINE LOST!"));
                Display_gotoxy(1,1);
                Display_write(buffer, sizeof(buffer));
                while(1);
                
            }
            */
            
        }
    }

    else
    {
        if(OffTrack)
        {
            LineNotFoundCounter++;
            // Measurement against Noise: preventing Softtimer to constantly stop due to noise of sensors (black line detected)
            if(LineNotFoundCounter >= 100u)
            
            {
                Led_switchOff(LED_YELLOW);
                SoftTimer_Stop(pTimer1);
                OffTrack = FALSE;
            }
        }
    } 
     
    if(OffTrack)
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
    //Wait some time to prevent immediatly finding startline after starting to drive
    if(SOFTTIMER_IS_EXPIRED(pTimer3))
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
    //if SOFTTIMER_IS_EXPIRED(pTimer1)
    if(gTrackLeft)
    {
        gTrackLeft = FALSE;
        Led_switchOff(LED_YELLOW);
        SoftTimer_Stop(pTimer1);
        return TRUE;
    }
    
    return FALSE;
}
/* INTERNAL FUNCTIONS *****************************************************************************/