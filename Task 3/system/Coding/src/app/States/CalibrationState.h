/***************************************************************************************************
  (c) NewTec GmbH 2024   -   www.newtec.de
***************************************************************************************************/
/**
 * @file       CalibrationState.h
 *
 * Header of CalibrationState.c.
 */
/**************************************************************************************************/
#ifndef CALIBRATION_STATE_H
#define CALIBRATION_STATE_H

/* INCLUDES ***************************************************************************************/
#include "StateDataTypes.h"

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/
/** @fn CalibrationState_enterCalibrate(void)
 * @brief starts calibrating the Line-Sensors
 * @return void
*/
void CalibrationState_enterCalibrate(void);

/** @fn States CalibrationState_getTransitions(void)
 * @brief checks if one transition to another State and returns the next State as enum
 * @return States: next State to be active or current state when no transition is true
*/
States CalibrationState_getTransitions(void);

/** @fn States CalibrationState_getStateFunctions(void)
 * @brief returns the pointer to the StateFunctions struct, which contains the entry, process and exit function of the state 
 * @return StateFunctions*: entry, process and exit functions of the state
*/
StateFunctions* CalibrationState_getStateFunctions(void);
#endif /* CALIBRATION_STATE_H */