/***************************************************************************************************
  (c) NewTec GmbH 2024   -   www.newtec.de
***************************************************************************************************/
/**
 * @file       PositionControl.h
 *
 * Header of PositionControl.c.
 */
/**************************************************************************************************/
#ifndef POSITION_COTROL_H
#define POSITION_COTROL_H

/* INCLUDES ***************************************************************************************/
#include "Types.h"
#include "LineSensor.h"
#include "DriveControl.h"
#include "Parameters.h"
#include "GlobalTimers.h"

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/
/** 
 * @brief update the sensorvalues, must be called before any of the other functions are beein called
*/
extern void PositionControl_UpdateSensorValues(void);

/** 
 * @brief simple PID controlling allgorithm to follow the trackline
*/
extern void PositionControl_DriveOnTrack(void);

/** 
 * @brief check if StartLine is beeing detected
 * @return Bool: return TRUE when StartLine is beeing detected, FALSE when not
*/
extern Bool PositionControl_checkForStartLine(void);

/** 
 * @brief check if TrackLine was lost
 * @return Bool: return TRUE when TrackLine was Lost, FALSE when not
*/
extern Bool PositionControl_checkForLineLost(void);

/** 
 * @brief calculate the moving average of measured weighted values
 * @return Int16: return the calculated average
*/
Int16 calcMovingAverage2(Int16 currentWeightedValues);

#endif /* POSITION_COTROL_H */