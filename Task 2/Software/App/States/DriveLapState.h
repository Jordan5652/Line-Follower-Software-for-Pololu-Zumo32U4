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

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/
/** @fn DriveLapState_enterRestartTimer2AndPlayBeep(void)
 * @brief starts timer2 measuring the lap-time plays a beep as an accustic signal
 * @return void
*/
void DriveLapState_enterRestartTimer2AndPlayBeep(void);

/** @fn DriveLapState_processDriveOnTrackLine(void)
 * @brief follows the TrackLine
 * @return void
*/
void DriveLapState_processDriveOnTrackLine(void);

/** @fn States DriveLapState_getTransitions(void)
 * @brief checks if one transition to another State and returns the next State as enum
 * @return States: next State to be active or current state when no transition is true
*/
States DriveLapState_getTransitions(void);

/** @fn States DriveLapState_getStateFunctions(void)
 * @brief returns the pointer to the StateFunctions struct, which contains the entry, process and exit function of the state 
 * @return StateFunctions*: entry, process and exit functions of the state
*/
StateFunctions* DriveLapState_getStateFunctions(void);

#endif /* DRIVE_LAP_STATE_H */