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

/**
 * @brief store the current state ID
*/
static States gCurrentState;

/* EXTERNAL FUNCTIONS *****************************************************************************/

void StateHandler_stateHandler(void)
{
   
}

/* INTERNAL FUNCTIONS *****************************************************************************/


