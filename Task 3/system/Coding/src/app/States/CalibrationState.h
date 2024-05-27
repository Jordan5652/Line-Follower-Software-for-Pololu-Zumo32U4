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
#include "DriveControl.h"
#include "LineSensor.h"

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/
/** 
 * @brief starts calibrating the Line-Sensors
*/
extern void CalibrationState_enterCalibrate(void);

/** 
 * @brief checks if one transition to another State and returns the next State as enum
 * @return States: next State to be active or current state when no transition is true
*/
extern States CalibrationState_getTransitions(void);

/** 
 * @brief returns the pointer to the StateFunctions struct, which contains the entry, process and exit function of the state 
 * @return StateFunctions*: entry, process and exit functions of the state
*/
extern StateFunctions* CalibrationState_getStateFunctions(void);
#endif /* CALIBRATION_STATE_H */