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

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/
/** @fn SearchTrackState_enterStartTimer1(void)
 * @brief starts timer1 to measure the Time in SearchTrackState
 * @return void
*/
void SearchTrackState_enterStartTimer1(void);

/** @fn SearchTrackState_processFindTrackLine(void)
 * @brief Allgorithm to search the TrackLine, after it has been lost 
 * @return void
*/
void SearchTrackState_processFindTrackLine(void);

/** @fn SearchTrackState_leaveResetTimer1(void)
 * @brief stops and resets timer1
 * @return void
*/
void SearchTrackState_leaveStopAndResetTimer1(void);

/** @fn States SearchTrackState_getTransitions(void)
 * @brief checks if one transition to another State and returns the next State as enum
 * @return States: next State to be active or current state when no transition is true
*/
States SearchTrackState_getTransitions(void);

/** @fn States SearchTrackState_getStateFunctions(void)
 * @brief returns the pointer to the StateFunctions struct, which contains the entry, process and exit function of the state 
 * @return StateFunctions*: entry, process and exit functions of the state
*/
StateFunctions* SearchTrackState_getStateFunctions(void);

#endif /* SEARCH_TRACK_STATE_H */