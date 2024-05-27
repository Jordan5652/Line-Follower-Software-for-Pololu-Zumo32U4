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
#include "GlobalTimers.h"
#include "Display.h"
//#include "SoftTimer.h"

/* CONSTANTS **************************************************************************************/
#define WHITE_BACKGROUND_VALUE_TRESHHOLD 150u
#define BLACK_LINE_VALUE_TRESHHOLD 550u

/* MACROS *****************************************************************************************/
#define CALIB_NO_LINE(sensorValue) \
    ((WHITE_BACKGROUND_VALUE_TRESHHOLD) > (sensorValue))
#define CALIB_OVER_LINE(sensorValue) \
    ((BLACK_LINE_VALUE_TRESHHOLD) < (sensorValue))
    //((sensorValue > 700u) ? ((true) : (false)))

//#define SOFTTIMER_IS_EXPIRED(pSoftTimer) \
    ((0 == (pSoftTimer)->counter) && (SOFT_TIMER_RUNNING == (pSoftTimer)->state))


/* TYPES ******************************************************************************************/
typedef enum
{
    CALIBRATION_STATE_INIT,
    CALIBRATION_STATE_TURN_RIGHT_UNTIL_LEFT_SENSOR,
    CALIBRATION_STATE_TURN_LEFT_UNTIL_RIGHT_SENSOR,
    CALIBRATION_STATE_CENTER_ON_LINE,
    CALIBRATION_STATE_TIMEOUT,
    CALIBRATION_STATE_FINISHED

}CalibrationState;


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