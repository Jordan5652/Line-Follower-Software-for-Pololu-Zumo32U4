/***************************************************************************************************
  (c) NewTec GmbH 2024   -   www.newtec.de
***************************************************************************************************/
/**
 * @file       ReadyState.h
 *
 * Header of ReadyState.c.
 */
/**************************************************************************************************/
#ifndef READY_STATE_H
#define READY_STATE_H

/* INCLUDES ***************************************************************************************/
#include "Types.h"
#include "Button.h"
#include "Display.h"

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

/**
 * @brief show ReadyState on display
*/
extern void ReadyState_enterDisplayState(void);

/**
 * @brief check if any of the Buttons is pressed by polling (ReadyState is left when some Button is pressed)
*/
extern void ReadyState_processPollingButtons(void);

/**
 * @brief check if button A was pressed by a user
 * @return Bool: return true if button A was pressed
*/
extern Bool ReadyState_checkTransitionTriggerButtonAPressed(void);

/**
 * @brief check if button B was pressed by a user
 * @return Bool: return true if button B was pressed
*/
extern Bool ReadyState_checkTransitionTriggerButtonBPressed(void);

/**
 * @brief check if button C was pressed by a user
 * @return Bool: return true if button C was pressed
*/
extern Bool ReadyState_checkTransitionTriggerButtonCPressed(void);

#endif /* READY_STATE_H */