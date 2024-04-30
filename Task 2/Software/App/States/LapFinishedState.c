/***************************************************************************************************
  (c) NewTec GmbH 2024   -   www.newtec.de
***************************************************************************************************/
/**
 * @file       LapFinishedState.c
 *
 * Contains the functions and variables for the LapFinishedState.
 */
/**************************************************************************************************/

/* INCLUDES ***************************************************************************************/
#include "LapFinishedState.h"
#include "StateDataTypes.h"
#include "Button.h"
#include "Buzzer.h"
#include "DriveControl.h"
#include "SoftTimer.h"
#include "Display.h"

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

/* VARIABLES **************************************************************************************/
/** @var state lapFinishedStateFunctions
 * @brief variable to hold the functionspointers of the state
*/
const StateFunctions lapFinishedStateFunctions;

/* EXTERNAL FUNCTIONS *****************************************************************************/
/** @fn LapFinishedState_enterStopTimer2AndDisplayTimeAndStopDriveAndPlayBeep(void)
 * @brief stops timer2 measuring the lap-time, displays the lap-time, stops the motors and plays a beep as an accustic signal
 * @return void
*/
void LapFinishedState_enterStopTimer2AndDisplayTimeAndStopDriveAndPlayBeep(void)
{


}

/** @fn LapFinishedState_leaveResetTimer2(void)
 * @brief resets timer2
 * @return void
*/
void LapFinishedState_leaveResetTimer2(void)
{


}

/** @fn const StateFunctions LapFinishedState_getTransitions(void)
 * @brief checks if one transition to another State and returns the next State as enum
 * @return States: next State to be active or current state when no transition is true
*/
States LapFinishedState_getTransitions(void)
{


}

/** @fn States LapFinishedState_getStateFunctions(void)
 * @brief returns the pointer to the StateFunctions struct, which contains the entry, process and exit function of the state 
 * @return StateFunctions*: entry, process and exit functions of the state
*/
StateFunctions* LapFinishedState_getStateFunctions(void)
{


}

/* INTERNAL FUNCTIONS *****************************************************************************/