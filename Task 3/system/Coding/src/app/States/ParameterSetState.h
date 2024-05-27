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
#include "Button.h"
#include "Parameters.h"
/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/
/** 
 * @brief displays all the available parameter-sets that can be used
*/
extern void ParameterSetState_enterDisplayParameterSets(void);

/** 
 * @brief lets the user choose a parameter-set
*/
extern void ParameterSetState_processSetParameterSet(void);

/** 
 * @brief checks if one transition to another State and returns the next State as enum
 * @return States: next State to be active or current state when no transition is true
*/
extern States ParameterSetState_getTransitions(void);

/** 
 * @brief returns the pointer to the StateFunctions struct, which contains the entry, process and exit function of the state 
 * @return StateFunctions*: entry, process and exit functions of the state
*/
extern StateFunctions* ParameterSetState_getStateFunctions(void);

#endif /* PARAMETER_SET_STATE_H */