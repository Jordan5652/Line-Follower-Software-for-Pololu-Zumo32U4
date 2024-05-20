/***************************************************************************************************
  (c) NewTec GmbH 2024   -   www.newtec.de
***************************************************************************************************/
/**
 * @file       ParameterSetState.h
 *
 * Header of ParameterSetState.c.
 */
/**************************************************************************************************/
#ifndef PARAMETER_SET_STATE_H
#define PARAMETER_SET_STATE_H

/* INCLUDES ***************************************************************************************/
#include "StateDataTypes.h"

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/
/** @fn ParameterSetState_enterDisplayParameterSets(void)
 * @brief displays all the available parameter-sets that can be used
 * @return void
*/
void ParameterSetState_enterDisplayParameterSets(void);

/** @fn ParameterSetState_processSetParameterSet(void)
 * @brief lets the user choose a parameter-set
 * @return void
*/
void ParameterSetState_processSetParameterSet(void);

/** @fn States ParameterSetState_getTransitions(void)
 * @brief checks if one transition to another State and returns the next State as enum
 * @return States: next State to be active or current state when no transition is true
*/
States ParameterSetState_getTransitions(void);

/** @fn States ParameterSetState_getStateFunctions(void)
 * @brief returns the pointer to the StateFunctions struct, which contains the entry, process and exit function of the state 
 * @return StateFunctions*: entry, process and exit functions of the state
*/
StateFunctions* ParameterSetState_getStateFunctions(void);

#endif /* PARAMETER_SET_STATE_H */