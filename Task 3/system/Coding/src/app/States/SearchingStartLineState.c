/***************************************************************************************************
  (c) NewTec GmbH 2024   -   www.newtec.de
***************************************************************************************************/
/**
 * @file       SearchingStartLineState.c
 *
 * Contains the functions and variables for the SearchingStartLineState.
 */
/**************************************************************************************************/

/* INCLUDES ***************************************************************************************/
#include "SearchingStartLineState.h"
#include "StateDataTypes.h"
#include "SoftTimer.h"
#include "DriveControl.h"
#include "LineSensor.h"


/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

/* VARIABLES **************************************************************************************/
/** @var const StateFunctions searchingStartlineStateFunctions
 * @brief variable to hold the functionspointers of the state
*/
const StateFunctions searchingStartLineStateFunctions;

/* EXTERNAL FUNCTIONS *****************************************************************************/
/** @fn SearchingStartLineState_enterRestartTimer1AndWait3sAndStartDriving(void)
 * @brief Restarts timer1 to measure the time until the startLine is found and starts the DualMotorDriveSystem to drive to the StartLine
 * @return void
*/
void SearchingStartLineState_enterRestartTimer1AndWait3sAndStartDriving(void)
{


}

/** @fn SearchingStartLineState_exitStopTimer1(void)
 * @brief stops and resets timer1
 * @return void
*/
void SearchingStartLineState_exitStopTimer1(void)
{


}

/** @fn States SearchingStartLineState_getTransitions(void)
 * @brief checks if one transition to another State and returns the next State as enum
 * @return States: next State to be active or current state when no transition is true
*/
States SearchningStartLineState_getTransitions(void)
{


}

/** @fn States SearchingStartLineState_getStateFunctions(void)
 * @brief returns the pointer to the StateFunctions struct, which contains the entry, process and exit function of the state 
 * @return StateFunctions*: entry, process and exit functions of the state
*/
StateFunctions* SearchingStartLineState_getStateFunctions(void)
{


}

/* INTERNAL FUNCTIONS *****************************************************************************/