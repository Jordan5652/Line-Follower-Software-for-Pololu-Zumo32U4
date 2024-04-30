/***************************************************************************************************
  (c) NewTec GmbH 2024   -   www.newtec.de
***************************************************************************************************/
/**
 * @file       StateHandler.c
 *
 * Module contains the functions for the genenrall logic of the statemachine.
 */
/**************************************************************************************************/

/* INCLUDES ***************************************************************************************/
#include "StateHandler.h"
#include "StateDataTypes.h"
#include "SearchTrackState.h"
#include "SearchingStartLineState.h"
#include "CalibrationState.h"
#include "LapFinishedState.h"
#include "ParameterSetState.h"
#include "ErrorState.h"
#include "ReadyState.h"
#include "DriveLapState.h"
#include "InitializationState.h"

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

/* VARIABLES **************************************************************************************/
static StateFunctions gCurrentState;
static States gNextStateId;
static StateFunctions* gStatesBuffer[9];

/* EXTERNAL FUNCTIONS *****************************************************************************/
/** @fn StateHandler_stateHandler(void)
 * @brief runs the statemachine
 * @return void
*/
void StateHandler_stateHandler(void)
{
   
}

/** @fn StateHandler_initStatesBuffer(void)
 * @brief fills the internal Buffer, in which the Function Pointers of the states are stored
 * @return void
*/
void StateHandler_initStatesBuffer(void)
{
   
}

/* INTERNAL FUNCTIONS *****************************************************************************/
/** @fn stateEntryHandler(void)
 * @brief calls entry function of current state
 * @return void
*/
static void stateEntryHandler(void)
{
   
}

/** @fn stateProcessHandler(void)
 * @brief calls process function of current state
 * @return void
*/
static void stateProcessHandler(void)
{
   
}

/** @fn stateExitHandler(void)
 * @brief calls exit (leave) function of current state
 * @return void
*/
static void stateExitHandler(void)
{
   
}

/** @fn States getNextState(void)
 * @brief sets the next state if any transition of the current state is true
 * @return States: enum containing the next state (or the current state if no transition is active)
*/
static States getNextState(void)
{
   
}

