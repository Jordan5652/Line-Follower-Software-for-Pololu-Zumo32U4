/***************************************************************************************************
  (c) NewTec GmbH 2024   -   www.newtec.de
***************************************************************************************************/
/**
 * @file       PositionControl.c
 *
 * Module contains the functions for position control for the robot.
 */
/**************************************************************************************************/

/* INCLUDES ***************************************************************************************/
#include "PositionControl.h"

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

/* VARIABLES **************************************************************************************/
#define MOTORSPEED 65u

static LineSensorValues values;
UInt32 sumOfActualValues;
Int16 sumOfWeightedValues;
Int16 sumOfWeightedValuesBefore = 0u;
Int16 sumOfWeightedValuesIntegrated = 0u;
Int16 Pos = 0;

/* EXTERNAL FUNCTIONS *****************************************************************************/
extern void PositionControl_DriveOnTrack(ParameterSet parameters)
{
    LineSensor_read(&values);

    sumOfWeightedValues = 0;
    sumOfWeightedValues += values.value[LINESENSOR_MIDDLE_LEFT] * -1;
    sumOfWeightedValues += values.value[LINESENSOR_MIDDLE] * 0;
    sumOfWeightedValues += values.value[LINESENSOR_MIDDLE_RIGHT] * 1;
    sumOfWeightedValues += values.value[LINESENSOR_LEFT] * -5;
    sumOfWeightedValues += values.value[LINESENSOR_RIGHT] * 5;
    
    Float32 kp = 0.04;
    Float32 kd = 0.0;
    Float32 ki = 0.0;
    
    Int32 speedDifference = parameters.kp*sumOfWeightedValues + parameters.kd*(sumOfWeightedValues-sumOfWeightedValuesBefore) + parameters.ki * (sumOfWeightedValuesIntegrated); 

    Int32 left = speedDifference + parameters.motorspeed;
    Int32 right = -speedDifference + parameters.motorspeed;

    if (left < 0)
    {
        left = 0;
    }
    if (right < 0)
    {
        right = 0;
    }

    //if(left > (2*MOTORSPEED))
    if (left > 100)
    {
        //left = 2*MOTORSPEED;
        left = 100;
    }

    //if(right > 2*MOTORSPEED)
    if (right > 100)
    {
        //right = 2*MOTORSPEED;
        right = 100;
    }

    DriveControl_drive(DRIVE_CONTROL_MOTOR_LEFT, left, DRIVE_CONTROL_FORWARD);
    DriveControl_drive(DRIVE_CONTROL_MOTOR_RIGHT, right, DRIVE_CONTROL_FORWARD);
    sumOfWeightedValuesBefore = sumOfWeightedValues;
    sumOfWeightedValuesIntegrated += sumOfWeightedValues;
}

/* INTERNAL FUNCTIONS *****************************************************************************/


