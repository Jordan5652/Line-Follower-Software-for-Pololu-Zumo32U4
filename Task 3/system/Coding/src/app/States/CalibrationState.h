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
#include "Types.h"

#include "DriveControl.h"
#include "LineSensor.h"

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/
/** 
 * @brief starts calibrating the Line-Sensors
*/
extern void CalibrationState_processCalibrate(void);

/** 
 * @brief checks if calibration is done
 * @return Bool: returns true if calibration is done
*/
extern Bool CalibrationState_checkTransitionTriggerCalibrationDone(void);

#endif /* CALIBRATION_STATE_H */