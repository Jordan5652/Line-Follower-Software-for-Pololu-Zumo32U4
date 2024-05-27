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
#include "Types.h"

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
 * @brief checks if timer2 exeeded 20s
 * @return Bool: returns true if timer2 exceeded 20s
*/
extern Bool DriveLapState_checkTranstionTriggerTimer2Exceeds20s(void);

/** 
 * @brief checks if track cannot be found
 * @return Bool: returns true track cannot be found
*/
extern Bool DriveLapState_checkTranstionTriggerTrackNotFound(void);

/** 
 * @brief checks if startline is found
 * @return Bool: returns true if startline is found
*/
extern Bool DriveLapState_checkTranstionTriggerStartlineFound(void);

#endif /* DRIVE_LAP_STATE_H */