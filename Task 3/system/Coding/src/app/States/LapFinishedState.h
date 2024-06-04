/***************************************************************************************************
  (c) NewTec GmbH 2024   -   www.newtec.de
***************************************************************************************************/
/**
 * @file       LapFinishedState.h
 *
 * Header of LapFinishedState.c.
 */
/**************************************************************************************************/
#ifndef LAP_FINISHED_STATE_H
#define LAP_FINISHED_STATE_H

/* INCLUDES ***************************************************************************************/
#include "stdio.h"
#include "Types.h"

#include "Button.h"
#include "Buzzer.h"
#include "DriveControl.h"
#include "SoftTimer.h"
#include "Display.h"
#include "GlobalTimers.h"

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/
/**
 * @brief stops timer2 measuring the lap-time, displays the lap-time, stops the motors and plays a beep as an accustic signal
*/
extern void LapFinishedState_enterStopTimer2AndDisplayTimeAndStopDriveAndPlayBeep(void);

/**
 * @brief checks if ButtonA is pressed by polling
*/
extern void LapFinishedState_processPollingButtonA(void);

/**
 * @brief checks if button A was pressed by a user
 * @return Bool: return true if button A was pressed
*/
extern Bool LapFinishedState_checkTransitionTriggerButtonAPressed(void);

#endif /* LAP_FINISHED_STATE_H */