/***************************************************************************************************
  (c) NewTec GmbH 2024   -   www.newtec.de
***************************************************************************************************/
/**
 * @file       StateHandler.h
 *
 * Header of StateHandler.c.
 */
/**************************************************************************************************/
#ifndef STATE_HANDLER_H
#define STATE_HANDLER_H

/* INCLUDES ***************************************************************************************/
#include "StateDataTypes.h"

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/
/** @fn StateHandler_stateHandler(void)
 * @brief runs the statemachine
 * @return void
*/
void StateHandler_stateHandler(void);

/** @fn StateHandler_initStatesBuffer(void)
 * @brief fills the internal Buffer, in which the Function Pointers of the states are stored
 * @return void
*/
void StateHandler_initStatesBuffer(void);

#endif /* STATE_HANDLER_H */