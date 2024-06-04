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
#define MAX_MOTOR_SPEED (100u)
#define MIN_MOTOR_SPEED (0u)

#define SUM_THRESHHOLD (10000u)
#define WHITE_THRESHHOLD (180u)

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

/* VARIABLES **************************************************************************************/
static LineSensorValues gSensorValues;

/* EXTERNAL FUNCTIONS *****************************************************************************/
extern void PositionControl_UpdateSensorValues(void)
{
    LineSensor_read(&gSensorValues);
}

extern void PositionControl_DriveOnTrack(void)
{
    Int16 sumOfWeightedValues;
    Int16 sumOfWeightedValuesBefore = 0;
    static Int16 sumOfWeightedValuesIntegrated = 0;

    sumOfWeightedValues = 0u;
    sumOfWeightedValues += gSensorValues.value[LINESENSOR_MIDDLE_LEFT] * -1;
    sumOfWeightedValues += gSensorValues.value[LINESENSOR_MIDDLE] * 0;
    sumOfWeightedValues += gSensorValues.value[LINESENSOR_MIDDLE_RIGHT] * 1;
    sumOfWeightedValues += gSensorValues.value[LINESENSOR_LEFT] * -5;
    sumOfWeightedValues += gSensorValues.value[LINESENSOR_RIGHT] * 5;
    
    Int32 speedDifference = pParameters->kp*sumOfWeightedValues + pParameters->kd*(sumOfWeightedValues-sumOfWeightedValuesBefore) + pParameters->ki * (sumOfWeightedValuesIntegrated);

    Int32 leftSpeed = speedDifference + pParameters->motorspeed;
    Int32 rightSpeed = -speedDifference + pParameters->motorspeed;

    if (leftSpeed < MIN_MOTOR_SPEED)
    {
        leftSpeed = MIN_MOTOR_SPEED;
    }
    if (rightSpeed < MIN_MOTOR_SPEED)
    {
        rightSpeed = MIN_MOTOR_SPEED;
    }

    if (leftSpeed > MAX_MOTOR_SPEED)
    {
        leftSpeed = MAX_MOTOR_SPEED;
    }

    if (rightSpeed > MAX_MOTOR_SPEED)
    {
        rightSpeed = MAX_MOTOR_SPEED;
    }

    DriveControl_drive(DRIVE_CONTROL_MOTOR_LEFT, leftSpeed, DRIVE_CONTROL_FORWARD);
    DriveControl_drive(DRIVE_CONTROL_MOTOR_RIGHT, rightSpeed, DRIVE_CONTROL_FORWARD);
    sumOfWeightedValuesBefore = sumOfWeightedValues;
    sumOfWeightedValuesIntegrated += sumOfWeightedValues;
}

extern Bool PosionControl_checkForStartLine(void)
{
    UInt16 sumOfWeightedValues = 0u;
    static UInt16 sumOfWeightedValuesBefore = 0u;

    if (SUM_THRESHHOLD < (sumOfWeightedValues - sumOfWeightedValuesBefore))
    {
        return TRUE;
    }
    else
    { 
        return FALSE;
    } 

    for (UInt8 Counter = 0; Counter < LINESENSOR_COUNT; Counter++)
    {
        if (Counter == 0 || Counter == 2  || Counter == 4)
        {
            sumOfWeightedValues += gSensorValues.value[Counter]*4;
        }
        else
        {
            sumOfWeightedValues += gSensorValues.value[Counter];
        }
    }
    sumOfWeightedValuesBefore = sumOfWeightedValues;

    UInt8 av[20];
    snprintf(av, sizeof(av),"%d", (sumOfWeightedValues - sumOfWeightedValuesBefore));

    Display_clear();
    Display_write(av, sizeof(av));
}

extern Bool PosionControl_checkForLineLost(void)
{
    Bool lineLost = TRUE;
    for (UInt8 Counter = 0; Counter < LINESENSOR_COUNT; Counter++)
    {
        if(gSensorValues.value[Counter] > WHITE_THRESHHOLD)
        {
            lineLost = FALSE;
        }
    }
    return lineLost;
}

/* INTERNAL FUNCTIONS *****************************************************************************/


