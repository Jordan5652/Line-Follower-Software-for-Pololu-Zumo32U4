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

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

/* VARIABLES **************************************************************************************/


/* EXTERNAL FUNCTIONS *****************************************************************************/

extern void DriveLapState_enterStartTimer3(void)
{
    SoftTimer_Stop(pTimer3);
    SoftTimer_start(pTimer3, 2000u);
}

extern void DriveLapState_processDriveOnTrackLine(void)
{
    PositionControl_UpdateSensorValues();
    PositionControl_DriveOnTrack();
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

extern Bool DriveLapState_checkTranstionTriggerTrackNotFound(void)
{
    return FALSE;

}

extern Bool DriveLapState_checkTranstionTriggerStartlineFound(void)
{
    if(SOFTTIMER_IS_EXPIRED(pTimer3))
    {
        return PosionControl_checkForStartLine();
    }
    else
    {
        return FALSE;
    }

}
/* INTERNAL FUNCTIONS *****************************************************************************/