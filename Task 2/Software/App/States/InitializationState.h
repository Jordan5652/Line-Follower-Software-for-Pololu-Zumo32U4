/***************************************************************************************************
  (c) NewTec GmbH 2024   -   www.newtec.de
***************************************************************************************************/
/**
 * @file       InitializationState.h
 *
 * Header of InitializationState.c.
 */
/**************************************************************************************************/
#ifndef INITIALIZATION_STATE_H
#define INITIALIZATION_STATE_H

/* INCLUDES ***************************************************************************************/
#include "StateDataTypes.h"

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/
/** @fn InitializationState_enterDisplayNameAndStartTimer1(void)
 * @brief displays the teamname and starts the timer1 to display the teamname for 2s 
 * @return void
*/
void InitializationState_enterDisplayNameAndStartTimer1(void);

/** @fn InitializationState_leaveStopAndResetTimer1(void)
 * @brief resets the timer1 
 * @return void
*/
void InitializationState_leaveStopAndResetTimer1(void);

/** @fn States InitializationState_getTransitions(void)
 * @brief checks if one transition to another State and returns the next State as enum
 * @return States: next State to be active or current state when no transition is true
*/
States InitializationState_getTransitions(void);

/** @fn States InitializationState_getStateFunctions(void)
 * @brief returns the pointer to the StateFunctions struct, which contains the entry, process and exit function of the state 
 * @return StateFunctions*: entry, process and exit functions of the state
*/
StateFunctions* InitializationState_getStateFunctions(void);

#endif /* INITIALIZATION_STATE_H */