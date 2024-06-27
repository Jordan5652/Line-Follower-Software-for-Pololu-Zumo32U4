/***************************************************************************************************
  (c) NewTec GmbH 2024   -   www.newtec.de
***************************************************************************************************/
/**
 * @file       ErrorState.h
 *
 * Header of ErrorState.c.
 */
/**************************************************************************************************/
#ifndef ERROR_STATE_H
#define ERROR_STATE_H

/* INCLUDES ***************************************************************************************/
#include "Types.h"
#include "Buzzer.h"
#include "Display.h"
#include "Button.h"
#include "DriveControl.h"
#include "ErrorHandler.h"

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/
/** 
 * @brief stop the motors when error occurs, emits an accustic alarm and displays the error message on the display and resets all timers
*/
extern void ErrorState_enterStopDriveAndPlayAlarmAndDisplayError(ErrorHandlerErrorCode errorCode);

/** 
 * @brief check if ButtonA is pressed by polling (ErrorState is left when ButtonA is pressed)
*/
extern void ErrorState_processPollingButtonA(void);

/** 
 * @brief check if button A was pressed by a user
 * @return Bool: return true if button A was pressed
*/
extern Bool ErrorState_checkTransitionTriggerButtonAPressed(void);

#endif /* ERROR_STATE_H */