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

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

/* VARIABLES **************************************************************************************/

extern SoftTimer timer1;
extern SoftTimer timer2;
extern SoftTimer timer3;

extern SoftTimer* pTimer1;
extern SoftTimer* pTimer2;
extern SoftTimer* pTimer3;

#endif /* GLOBALTIMERS_H */