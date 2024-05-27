/***************************************************************************************************
  (c) NewTec GmbH 2024   -   www.newtec.de
***************************************************************************************************/
/**
 * @file       ReadyState.h
 *
 * Header of ReadyState.c.
 */
/**************************************************************************************************/
#ifndef READY_STATE_H
#define READY_STATE_H

/* INCLUDES ***************************************************************************************/
#include "StateDataTypes.h"
#include "Button.h"

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/
/** 
 * @brief checks if any of the Buttons is pressed by polling (ReadyState is left when some Button is pressed)
*/
extern void ReadyState_processPollingButtons(void);

/** 
 * @brief checks if one transition to another State and returns the next State as enum
 * @return States: next State to be active or current state when no transition is true
*/
extern States ReadyState_getTransitions(void);

/** 
 * @brief returns the pointer to the StateFunctions struct, which contains the entry, process and exit function of the state 
 * @return StateFunctions*: entry, process and exit functions of the state
*/
extern StateFunctions* ReadyState_getStateFunctions(void);

#endif /* READY_STATE_H */