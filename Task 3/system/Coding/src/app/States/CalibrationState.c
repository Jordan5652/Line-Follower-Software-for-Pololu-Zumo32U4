/***************************************************************************************************
  (c) NewTec GmbH 2024   -   www.newtec.de
***************************************************************************************************/
/**
 * @file       CalibrationState.c
 *
 * contains the functions and variables for the CalibrationState.
 */
/**************************************************************************************************/

/* INCLUDES ***************************************************************************************/
#include "CalibrationState.h"
#include "StateDataTypes.h"
#include "DriveControl.h"
#include "LineSensor.h"

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

/* VARIABLES **************************************************************************************/
/** @var const StateFunctions calibrationStateFunctions
 * @brief variable to hold the functionspointers of the state
*/
const StateFunctions calibrationStateFunctions;

/* EXTERNAL FUNCTIONS *****************************************************************************/
/** @fn CalibrationState_enterCalibrate(void)
 * @brief starts calibrating the Line-Sensors
 * @return void
*/
void CalibrationState_enterCalibrate(void)
{


}

/** @fn States CalibrationState_getTransitions(void)
 * @brief checks if one transition to another State and returns the next State as enum
 * @return States: next State to be active or current state when no transition is true
*/
States CalibrationState_getTransitions(void)
{


}

/** @fn States CalibrationState_getStateFunctions(void)
 * @brief returns the pointer to the StateFunctions struct, which contains the entry, process and exit function of the state 
 * @return StateFunctions*: entry, process and exit functions of the state
*/
StateFunctions* CalibrationState_getStateFunctions(void)
{


}



/* INTERNAL FUNCTIONS *****************************************************************************/