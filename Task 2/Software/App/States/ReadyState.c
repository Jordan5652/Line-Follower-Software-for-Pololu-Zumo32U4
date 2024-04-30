/***************************************************************************************************
  (c) NewTec GmbH 2024   -   www.newtec.de
***************************************************************************************************/
/**
 * @file       ReadyState.c
 *
 * Contains the functions and variables for the ReadyState.
 */
/**************************************************************************************************/

/* INCLUDES ***************************************************************************************/
#include "ReadyState.h"
#include "StateDataTypes.h"
#include "SoftTimer.h"
#include "Button.h"

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

/* VARIABLES **************************************************************************************/
/** @var const StateFunctions readyStateFunctions
 * @brief variable to hold the functionspointers of the state
*/
const StateFunctions readyStateFunctions;

/* EXTERNAL FUNCTIONS *****************************************************************************/
/** @fn ReadyState_processPollingButtons(void)
 * @brief checks if any of the Buttons is pressed by polling (ReadyState is left when some Button is pressed)
 * @return void
*/
void ReadyState_processPollingButtons(void)
{


}

/** @fn States ReadyState_getTransitions(void)
 * @brief checks if one transition to another State and returns the next State as enum
 * @return States: next State to be active or current state when no transition is true
*/
States ReadyState_getTransitions(void)
{


}

/** @fn States ReadyState_getStateFunctions(void)
 * @brief returns the pointer to the StateFunctions struct, which contains the entry, process and exit function of the state 
 * @return StateFunctions*: entry, process and exit functions of the state
*/
StateFunctions* ReadyState_getStateFunctions(void)
{


}
/* INTERNAL FUNCTIONS *****************************************************************************/