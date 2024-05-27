/***************************************************************************************************
  (c) NewTec GmbH 2024   -   www.newtec.de
***************************************************************************************************/
/**
 * @file       SearchTrackState.h
 *
 * Header of SearchTrackState.c.
 */
/**************************************************************************************************/
#ifndef SEARCH_TRACK_STATE_H
#define SEARCH_TRACK_STATE_H

/* INCLUDES ***************************************************************************************/
#include "StateDataTypes.h"
#include "SoftTimer.h"
#include "DriveControl.h"
#include "LineSensor.h"

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/
/** 
 * @brief starts timer1 to measure the Time in SearchTrackState
*/
extern void SearchTrackState_enterRestartTimer1(void);

/** 
 * @brief Allgorithm to search the TrackLine, after it has been lost 
*/
extern void SearchTrackState_processFindTrackLine(void);

/**
 * @brief stops timer1
*/
extern void SearchTrackState_leaveStopTimer1(void);

/** 
 * @brief checks if one transition to another State and returns the next State as enum
 * @return States: next State to be active or current state when no transition is true
*/
extern States SearchTrackState_getTransitions(void);

/** 
 * @brief returns the pointer to the StateFunctions struct, which contains the entry, process and exit function of the state 
 * @return StateFunctions*: entry, process and exit functions of the state
*/
extern StateFunctions* SearchTrackState_getStateFunctions(void);

#endif /* SEARCH_TRACK_STATE_H */