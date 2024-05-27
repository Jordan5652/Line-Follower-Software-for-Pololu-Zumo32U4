/***************************************************************************************************
  (c) NewTec GmbH 2024   -   www.newtec.de
***************************************************************************************************/
/**
 * @file       InitializationState.h
 *
 * Header of InitializationState.c.
 */
/**************************************************************************************************/
#ifndef INITIALIZATION_STATE_H
#define INITIALIZATION_STATE_H

/* INCLUDES ***************************************************************************************/
#include "Types.h"

#include "StateDataTypes.h"
#include "SoftTimer.h"
#include "Display.h"
/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/
/** 
 * @brief displays the teamname and starts the timer1 to display the teamname for 2s 
*/
extern void InitializationState_enterDisplayNameAndStartTimer1(void);

/** 
 * @brief resets the timer1 
*/
extern void InitializationState_exitStopTimer1(void);

/** 
 * @brief checks if timer1 exeeded 2s
 * @return Bool: returns true if timer1 exceeded 2s
*/
extern Bool InitializationState_checkTransitionTriggerTimer1Exceeds2s(void);

#endif /* INITIALIZATION_STATE_H */