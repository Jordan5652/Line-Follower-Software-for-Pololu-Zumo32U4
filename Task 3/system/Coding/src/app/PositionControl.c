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
#define MIN_MOTOR_SPEED (20u)

#define WHITE_THRESHHOLD (250u)

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

#define BUFFER_SIZE (9)
Int16 calcMovingAverage(Int16 currentWeightedValues)
{
    static Int16 Buffer[BUFFER_SIZE] = {0};
    static UInt8 NumberOfElements = 0; 
    Int16 movingAvr = 0;

    if(NumberOfElements < BUFFER_SIZE)
    {
        Buffer[NumberOfElements] = currentWeightedValues;
        NumberOfElements++;        
    }
    else
    {
        for(UInt8 counter1 = 1u; counter1 < NumberOfElements; counter1++)
        {
            Buffer[counter1-1u] = Buffer[counter1];
        }
        Buffer[NumberOfElements-1] = currentWeightedValues;   
    }

    for(UInt8 counter2 = 0u; counter2 < NumberOfElements; counter2++)
    {
        movingAvr += Buffer[counter2];
    }  
    movingAvr = movingAvr / NumberOfElements;
    return movingAvr;
}
#define BUFFER_SIZE2 (30)

Int16 calcMovingAverage2(Int16 currentWeightedValues)
{
    static Int16 Buffer2[BUFFER_SIZE2] = {0};
    static UInt8 NumberOfElements2 = 0; 
    Int16 movingAvr = 0;

    if(NumberOfElements2 < BUFFER_SIZE)
    {
        Buffer2[NumberOfElements2] = currentWeightedValues;
        NumberOfElements2++;       
        return 0; 
    }
    else
    {
        for(UInt8 counter1 = 1u; counter1 < NumberOfElements2; counter1++)
        {
            Buffer2[counter1-1u] = Buffer2[counter1];
        }
        Buffer2[NumberOfElements2-1] = currentWeightedValues;   
    }

    for(UInt8 counter2 = 0u; counter2 < NumberOfElements2; counter2++)
    {
        movingAvr += Buffer2[counter2];
    }  
    movingAvr = movingAvr / NumberOfElements2;
    return movingAvr;

}

#include "Led.h"
Bool onStraightLine = TRUE;
UInt16 TESTCOUNTER = 0u;
UInt16 TESTCOUNTER2 = 0u;
extern void PositionControl_DriveOnTrack(void)
{
    Int16 sumOfWeightedValues;
    static Int16 sumOfWeightedValuesBefore = 0;
    static Int16 sumOfWeightedValuesIntegrated = 0;
    static Int16 movAverageSpeedDifference = 0;

    sumOfWeightedValues = 0u;
    sumOfWeightedValues += gSensorValues.value[LINESENSOR_MIDDLE_LEFT] * -1;
    sumOfWeightedValues += gSensorValues.value[LINESENSOR_MIDDLE] * 0;
    sumOfWeightedValues += gSensorValues.value[LINESENSOR_MIDDLE_RIGHT] * 1;

    sumOfWeightedValues = calcMovingAverage(sumOfWeightedValues); 

    ParameterSet* pParameters = Parameters_getParameterSet();

    Int32 speedDifference = pParameters->kp*sumOfWeightedValues + pParameters->kd*(sumOfWeightedValues-sumOfWeightedValuesBefore) + pParameters->ki * (sumOfWeightedValuesIntegrated);

    Int32 leftSpeed = speedDifference + pParameters->motorspeed;
    Int32 rightSpeed = -speedDifference + pParameters->motorspeed;

    if (leftSpeed < MIN_MOTOR_SPEED)
    {
        rightSpeed += leftSpeed;
        leftSpeed = MIN_MOTOR_SPEED;
        
    }
    if (rightSpeed < MIN_MOTOR_SPEED)
    {

        leftSpeed += rightSpeed;
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
    movAverageSpeedDifference = calcMovingAverage2(rightSpeed - leftSpeed);
}

extern Bool PositionControl_checkForStartLine(void)
{
    static UInt8 gCounter = 0;
    
    if (((gSensorValues.value[LINESENSOR_LEFT]) > 200u && (gSensorValues.value[LINESENSOR_RIGHT]) > 200u)) 
    {
        gCounter++;
    }

    if (2 < gCounter)
    {
        SoftTimer_Stop(GlobalTimers_getTimer(TIMER2));
        gCounter = 0;
        return TRUE;
    }

    return FALSE;
}

extern Bool PositionControl_checkForLineLost(void)
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