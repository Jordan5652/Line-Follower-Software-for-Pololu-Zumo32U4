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
#include "SoftTimer.h"
#include "Display.h"
/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/
/** 
 * @brief displays the teamname and starts the timer1 to display the teamname for 2s 
*/
extern void InitializationState_enterDisplayNameAndRestartTimer1(void);

/** 
 * @brief resets the timer1 
*/
extern void InitializationState_leaveStopTimer1(void);

/** 
 * @brief checks if one transition to another State and returns the next State as enum
 * @return States: next State to be active or current state when no transition is true
*/
extern States InitializationState_getTransitions(void);

/**
 * @brief returns the pointer to the StateFunctions struct, which contains the entry, process and exit function of the state 
 * @return StateFunctions*: entry, process and exit functions of the state
*/
extern StateFunctions* InitializationState_getStateFunctions(void);

#endif /* INITIALIZATION_STATE_H */