/***************************************************************************************************
  (c) NewTec GmbH 2024   -   www.newtec.de
***************************************************************************************************/
/**
 * @file       PreDriveState.h
 *
 * Header of PreDriveState.c.
 */
/**************************************************************************************************/
#ifndef PRE_DRIVE_STATE_H
#define PRE_DRIVE_STATE_H

/* INCLUDES ***************************************************************************************/
#include "Types.h"
#include "GlobalTimers.h"
#include "Display.h"

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/
/**
 * @brief start timer1 to measure delay before starting to drive
*/
extern void PreDriveState_enterStartTimer1AndWaitFor3s(void);

/**
 * @brief stop timer 1
*/
extern void PreDriveState_exitStopTimer1(void);

/**
 * @brief check if timer1 exceeded 3s
 * @return Bool: return true if timer1 exceeded 3s
*/
extern Bool PreDriveState_checkTransitionTriggerTimer1Exceeds3s(void);

#endif /* PRE_DRIVE_STATE_H */