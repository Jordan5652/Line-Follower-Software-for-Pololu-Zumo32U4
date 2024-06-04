/***************************************************************************************************
  (c) NewTec GmbH 2024   -   www.newtec.de
***************************************************************************************************/
/**
 * @file       SearchingStartLineState.h
 *
 * Header of SearchingStartLineState.c.
 */
/**************************************************************************************************/
#ifndef SEARCHING_START_LINE_STATE_H
#define SEARCHING_START_LINE_STATE_H

/* INCLUDES ***************************************************************************************/
#include "Types.h"

#include "SoftTimer.h"
#include "GlobalTimers.h"
#include "DriveControl.h"
#include "LineSensor.h"
#include "Buzzer.h"
#include "Display.h"

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/
/**
 * @brief Restarts timer1 to measure the time until the startLine is found and starts the DualMotorDriveSystem to drive to the StartLine
*/
extern void SearchingStartLineState_enterStartTimer1AndStartDriving(void);

/**
 * @brief Searches for the startline with the line sensors
*/
extern void SearchingStartLineState_processSearchForStartline(void);

/** 
 * @brief starts timer2 and plays beep if startline found
*/
extern void SearchingStartLineState_exitStartTimer2AndPlayBeepIfStartlineFound(void);

/**
 * @brief checks if the lines sensors detect the startline
 * @return Bool: returns true if startline is found
*/
extern Bool SearchningStartLineState_checkTransitionTriggerStartlineFound(void);

/**
 * @brief checks if timer1 exceeded 2s
 * @return Bool: returns true if timer exceeded 2s
*/
extern Bool SearchningStartLineState_checkTransitionTriggerTimer1Exceeds5s(void);

#endif /* SEARCHING_START_LINE_STATE_H */