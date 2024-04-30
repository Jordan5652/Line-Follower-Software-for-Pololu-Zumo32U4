/***************************************************************************************************
  (c) NewTec GmbH 2024   -   www.newtec.de
***************************************************************************************************/
/**
 * @file       InitializationState.c
 *
 * Contains the functions and variables for the InitializationState.
 */
/**************************************************************************************************/

/* INCLUDES ***************************************************************************************/
#include "InitializationState.h"
#include "StateDataTypes.h"
#include "SoftTimer.h"
#include "Display.h"

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

/* VARIABLES **************************************************************************************/
/** @var const StateFunctions initializationStateFunctions
 * @brief variable to hold the functionspointers of the state
*/
const StateFunctions initializationStateFunctions;

/* EXTERNAL FUNCTIONS *****************************************************************************/
/** @fn InitializationState_enterDisplayNameAndStartTimer1(void)
 * @brief displays the teamname and starts the timer1 to display the teamname for 2s 
 * @return void
*/
void InitializationState_enterDisplayNameAndStartTimer1(void)
{


}

/** @fn InitializationState_leaveStopAndResetTimer1(void)
 * @brief resets the timer1 
 * @return void
*/
void InitializationState_leaveStopAndResetTimer1(void)
{


}

/** @fn States InitializationState_getTransitions(void)
 * @brief checks if one transition to another State and returns the next State as enum
 * @return States: next State to be active or current state when no transition is true
*/
States InitializationState_getTransitions(void)
{


}

/** @fn States InitializationState_getStateFunctions(void)
 * @brief returns the pointer to the StateFunctions struct, which contains the entry, process and exit function of the state 
 * @return StateFunctions*: entry, process and exit functions of the state
*/
StateFunctions* InitializationState_getStateFunctions(void)
{


}
/* INTERNAL FUNCTIONS *****************************************************************************/