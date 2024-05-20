/***************************************************************************************************
  (c) NewTec GmbH 2024   -   www.newtec.de
***************************************************************************************************/
/**
 * @file       SearchTrackState.c
 *
 * Contains the functions and variables for the SearchTrackState.
 */
/**************************************************************************************************/

/* INCLUDES ***************************************************************************************/
#include "SearchTrackState.h"
#include "StateDataTypes.h"
#include "SoftTimer.h"
#include "DriveControl.h"
#include "LineSensor.h"

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

/* VARIABLES **************************************************************************************/
/** @var const StateFunctions searchTrackStateFunctions
 * @brief variable to hold the functionspointers of the state
*/
const StateFunctions searchTrackStateFunctions;

/* EXTERNAL FUNCTIONS *****************************************************************************/
/** @fn SearchTrackState_enterReStartTimer1(void)
 * @brief starts timer1 to measure the Time in SearchTrackState
 * @return void
*/
void SearchTrackState_enterRestartTimer1(void)
{


}

/** @fn SearchTrackState_processFindTrackLine(void)
 * @brief Allgorithm to search the TrackLine, after it has been lost 
 * @return void
*/
void SearchTrackState_processFindTrackLine(void)
{


}

/** @fn SearchTrackState_leaveStopTimer1(void)
 * @brief stops timer1
 * @return void
*/
void SearchTrackState_leaveStopTimer1(void)
{


}

/** @fn States SearchTrackState_getTransitions(void)
 * @brief checks if one transition to another State and returns the next State as enum
 * @return States: next State to be active or current state when no transition is true
*/
States SearchTrackState_getTransitions(void)
{


}

/** @fn States SearchTrackState_getStateFunctions(void)
 * @brief returns the pointer to the StateFunctions struct, which contains the entry, process and exit function of the state 
 * @return StateFunctions*: entry, process and exit functions of the state
*/
StateFunctions* SearchTrackState_getStateFunctions(void)
{


}

/* INTERNAL FUNCTIONS *****************************************************************************/