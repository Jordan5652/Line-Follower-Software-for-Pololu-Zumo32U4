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
#include "Types.h"

#include "CalibrationState.h"
#include "DriveLapState.h"
#include "ErrorState.h"
#include "InitializationState.h"
#include "LapFinishedState.h"
#include "ParameterSetState.h"
#include "PreDriveState.h"
#include "ReadyState.h"
#include "SearchingStartlineState.h"
#include "SearchTrackState.h"

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

typedef enum
{
    INITIALIZATION_STATE,
    READY_STATE,
    CALIBRATION_STATE,
    PARAMETER_SET_STATE,
    SEARCHING_STARTLINE_STATE,
    DRIVE_LAP_STATE,
    LAP_FINISHED_STATE,
    SEARCH_TRACK_STATE,
    ERROR_STATE,
    PRE_DRIVE_STATE,
}States;

/* PROTOTYPES *************************************************************************************/
/** @fn StateHandler_stateHandler(void)
 * @brief runs the statemachine
 * @return void
*/
extern void StateHandler_stateHandler(void);

#endif /* STATE_HANDLER_H */