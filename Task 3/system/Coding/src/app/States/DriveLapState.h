/***************************************************************************************************
  (c) NewTec GmbH 2024   -   www.newtec.de
***************************************************************************************************/
/**
 * @file       DriveLapState.h
 *
 * Header of DriveLapState.c.
 */
/**************************************************************************************************/
#ifndef DRIVE_LAP_STATE_H
#define DRIVE_LAP_STATE_H

/* INCLUDES ***************************************************************************************/
#include "StateDataTypes.h"
#include "Parameters.h"
#include "Buzzer.h"
#include "DriveControl.h"
#include "LineSensor.h"
#include "SoftTimer.h"

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/
/** 
 * @brief starts timer2 measuring the lap-time plays a beep as an accustic signal
*/
extern void DriveLapState_enterRestartTimer2AndPlayBeep(void);

/** 
 * @brief follows the TrackLine
*/
extern void DriveLapState_processDriveOnTrackLine(void);

/** 
 * @brief checks if one transition to another State and returns the next State as enum
 * @return States: next State to be active or current state when no transition is true
*/
extern States DriveLapState_getTransitions(void);

/** 
 * @brief returns the pointer to the StateFunctions struct, which contains the entry, process and exit function of the state 
 * @return StateFunctions*: entry, process and exit functions of the state
*/
extern StateFunctions* DriveLapState_getStateFunctions(void);

#endif /* DRIVE_LAP_STATE_H */