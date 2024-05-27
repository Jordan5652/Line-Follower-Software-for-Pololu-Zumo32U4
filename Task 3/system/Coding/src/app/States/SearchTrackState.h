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
#include "Types.h"

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
extern void SearchTrackState_enterStartTimer1(void);

/** 
 * @brief Allgorithm to search the TrackLine, after it has been lost 
*/
extern void SearchTrackState_processFindTrackLine(void);

/**
 * @brief stops timer1
*/
extern void SearchTrackState_exitStopTimer1(void);

/** 
 * @brief checks if timer1 exceeded 5s
 * @return Bool: returns true if timer1 exceeded 5s
*/
extern Bool SearchTrackState_checkTransitionTriggerTimer1Exceeds5s(void);

/** 
 * @brief checks if line sensor detect the track again
 * @return Bool: returns true if line sensor detect the track again
*/
extern Bool SearchTrackState_checkTransitionTriggerTrackFound(void);

#endif /* SEARCH_TRACK_STATE_H */