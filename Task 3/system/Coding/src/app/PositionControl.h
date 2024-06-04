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

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/
/** 
 * @brief updates the sensorvalues, must be called before any of the other functions are beein called
*/
extern void PositionControl_UpdateSensorValues(void);

/** 
 * @brief simple PID controlling allgorithm to follow the trackline
*/

extern void PositionControl_DriveOnTrack(void);

/** 
 * @brief checks if StartLine is beeing detected
 * @return Bool: returns TRUE when StartLine is beeing detected, FALSE when not
*/
extern Bool PositionControl_checkForStartLine(void);

/** 
 * @brief checks if TrackLine was lost
 * @return Bool: returns TRUE when TrackLine was Lost, FALSE when not
*/
extern Bool PositionControl_checkForLineLost(void);

#endif /* POSITION_COTROL_H */