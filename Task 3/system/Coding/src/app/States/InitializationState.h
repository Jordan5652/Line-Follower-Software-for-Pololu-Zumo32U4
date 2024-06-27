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
#include "Display.h"
#include "GlobalTimers.h"
#include "Parameters.h"

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/
/** 
 * @brief display the teamname and startsthe timer1 to display the teamname for 2s 
*/
extern void InitializationState_enterDisplayNameAndStartTimer1(void);

/**
 * @brief reset the timer1
*/
extern void InitializationState_exitStopTimer1(void);

/**
 * @brief check if timer1 exeeded 2s
 * @return Bool: return true if timer1 exceeded 2s
*/
extern Bool InitializationState_checkTransitionTriggerTimer1Exceeds2s(void);

#endif /* INITIALIZATION_STATE_H */