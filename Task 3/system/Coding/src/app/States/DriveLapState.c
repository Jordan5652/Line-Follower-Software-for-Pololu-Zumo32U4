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
#define SENSOR_WEIGHT_SCALE (1000u)

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

/* VARIABLES **************************************************************************************/

/* EXTERNAL FUNCTIONS *****************************************************************************/


extern void DriveLapState_processDriveOnTrackLine(void)
{
    Int8 buffer[] = "DrivingLapState";
    Display_clear();
    Display_write(buffer, sizeof(buffer));
}


extern Bool DriveLapState_checkTranstionTriggerTimer2Exceeds20s(void)
{


}

extern Bool DriveLapState_checkTranstionTriggerTrackNotFound(void)
{


}

extern Bool DriveLapState_checkTranstionTriggerStartlineFound(void)
{


}
/* INTERNAL FUNCTIONS *****************************************************************************/
