/***************************************************************************************************
  (c) NewTec GmbH 2024   -   www.newtec.de
***************************************************************************************************/
/**
 * @file       ErrorState.h
 *
 * Header of ErrorState.c.
 */
/**************************************************************************************************/
#ifndef ERROR_STATE_H
#define ERROR_STATE_H

/* INCLUDES ***************************************************************************************/
#include "StateDataTypes.h"

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/
/** @fn ErrorState_enterStopDriveAndPlayAlarmAndDisplayErrorAndResetTimer1AndTimer2(void)
 * @brief stops the motors when error occurs, emits an accustic alarm and displays the error message on the display and resets all timers
 * @return void
*/
void ErrorState_enterStopDriveAndPlayAlarmAndDisplayErrorAndStopAndResetAllTimers(void);

/** @fn ErrorState_processPollingButtonA(void)
 * @brief checks if ButtonA is pressed by polling (ErrorState is left when ButtonA is pressed)
 * @return void
*/
void ErrorState_processPollingButtonA(void);

/** @fn States ErrorState_getTransitions(void)
 * @brief checks if one transition to another State and returns the next State as enum
 * @return States: next State to be active or current state when no transition is true
*/
States ErrorState_getTransitions(void);

/** @fn States ErrorState_getStateFunctions(void)
 * @brief returns the pointer to the StateFunctions struct, which contains the entry, process and exit function of the state 
 * @return StateFunctions*: entry, process and exit functions of the state
*/
StateFunctions* ErrorState_getStateFunctions(void);

#endif /* ERROR_STATE_H */