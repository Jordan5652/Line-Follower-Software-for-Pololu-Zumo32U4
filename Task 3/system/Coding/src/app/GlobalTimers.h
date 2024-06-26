/***************************************************************************************************
  (c) NewTec GmbH 2024   -   www.newtec.de
***************************************************************************************************/
/**
 * @file       GlobalTimers.h
 *
 * Header of GlobalTimers.c.
 */
/**************************************************************************************************/
#ifndef GLOBALTIMERS_H
#define GLOBALTIMERS_H

/* INCLUDES ***************************************************************************************/
#include "SoftTimer.h"

/* CONSTANTS **************************************************************************************/
#define FIVE_SECONDS (5000u)
#define TWENTY_SECONDS (20000u)
#define ONE_SECOND (1000U)
#define TWO_SECONDS (2000u)
#define THREE_SECONDS (3000u)

#define TIMER1 (0u)
#define TIMER2 (1u)
#define TIMER3 (2u)

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

/* VARIABLES **************************************************************************************/

/**
 * @brief returns one of the three global timers
 * @return SoftTimer*: returns a pointer to timer
*/
extern SoftTimer* GlobalTimers_getTimer(UInt8 index);

#endif /* GLOBALTIMERS_H */