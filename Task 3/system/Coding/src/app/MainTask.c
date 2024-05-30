/***************************************************************************************************
  (c) NewTec GmbH 2019   -   www.newtec.de
  $URL: https://svn.newtec.zz/NTCampus/SW-Entwicklung/trunk/system/50_Implementierung/Projekte/Linienfolger/20_Beistellung/Delivery/Beistellung_r300/Coding/src/app/MainTask.c $
***************************************************************************************************/
/**
@addtogroup App
@{
@file       MainTask.c

Main Application task.
For a detailed description see the detailed description in @ref MainTask.h.

@version    %$Id: MainTask.c 300 2024-02-01 12:58:40Z leglaz $
* @}
***************************************************************************************************/

/* INCLUDES ***************************************************************************************/

#include "app/MainTask.h"

#include "os/ErrorHandler.h"
#include "os/Task.h"
#include "os/Scheduler.h"
#include "service/Button.h"

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

/** Internal Task cyclic worker function.
 * @param[in] data task data (ignored).
 */
static void mainTaskWork (void * data);

/* VARIABLES **************************************************************************************/

/** MainTask task structure. */
static Task gMainTask;

/* EXTERNAL FUNCTIONS *****************************************************************************/

extern MainTask_Ret MainTask_init(void)
{
    MainTask_Ret result = MAINTASK_RET_INTERNAL_ERROR;

    /* TODO: Add your initalization here. */


    if (TASK_RET_SUCCESS == Task_init(&gMainTask, mainTaskWork, TASK_STATE_RUNNING, NULL))
    {
        if ( SCHEDULER_RET_SUCCESS == Scheduler_addTask(&gMainTask))
        {
            /* TODO: Add your application here. */
        }
        else
        {
            result = MAINTASK_RET_ADD_TASK_FAIL;
        }
    }
    else
    {
        result = MAINTASK_RET_INIT_TASK_FAIL;
    }

    return result;
}

/* INTERNAL FUNCTIONS *****************************************************************************/
typedef enum
{
    INIT,
    CALIBRATE,
    POS,
    IDLE,
    START_TIMER,
    CONTROLL
    
}States;

#include "SoftTimer.h"
#include "GlobalTimers.h"
#include "Display.h"
#include "CalibrationState.h"
#include "LineSensor.h"
#include <stdio.h> 
#include <stdlib.h>

static delay(uint16_t delay)
{
    static SoftTimer timer;
    SoftTimer_init(&timer);
    SoftTimerHandler_register(&timer);
    SoftTimer_start(&timer, delay);

    while(SOFTTIMER_IS_EXPIRED(&timer) == false)
    {
        
    } 
    SoftTimer_Stop(&timer); 
    SoftTimerHandler_unRegister(&timer);

}

static char text0[] = "SENSOR0: ";
static char text1[] = "SENSOR1: ";
static char text2[] = "SENSOR2: ";
static char text3[] = "SENSOR3: ";
static char text4[] = "SENSOR4: ";

static char value0[5];
static char value1[5];
static char value2[5];
static char value3[5];
static char value4[5];

//static UInt16 lastValue0 = 0u; 
//static UInt16 lastValue1 = 0u; 
//static UInt16 lastValue2 = 0u; 
//static UInt16 lastValue3 = 0u; 
//static UInt16 lastValue4 = 0u; 
#define MOTORSPEED 65u

static char text[] = "POSITION: ";
static char position[8];
static char speedLeft[8];
static char speedRight[8];

static LineSensorValues values;
uint32_t sumOfActualValues;
Int16 sumOfWeightedValues;
Int16 sumOfWeightedValuesBefore = 0u;
Int16 sumOfWeightedValuesIntegrated = 0u;
Int16 Pos = 0; 
//static char test[] = "ENTERED IDLE";
static States eStates = INIT;
static void mainTaskWork(void * data)
{
    (void)data;

    /* TODO: Add your application here. */
    switch (eStates)
    {
        case INIT:
            //SoftTimer_init(pTimer1);
            SoftTimerHandler_register(pTimer1);
            eStates = CALIBRATE;
            break;
        case CALIBRATE:
            if(CalibrationState_checkTransitionTriggerCalibrationDone() == false)
            {
                CalibrationState_processCalibrate();
            }
            else
            {
                LineSensor_enableEmitter();
                //LineSensor_read(&values);
                //LineSensor_disableEmitter();
                SoftTimer_start(pTimer1, 5000u);
                eStates = START_TIMER;

            }
            break;

        case START_TIMER:
            //SoftTimer_start(pTimer1, 5000u);
            if SOFTTIMER_IS_EXPIRED(pTimer1)
            {
                eStates = CONTROLL;
                SoftTimer_Stop(pTimer1);
                SoftTimer_start(pTimer1, 5000u);

            }
            //eStates = CONTROLL;

            break; 
        case POS:
            if (SOFTTIMER_IS_EXPIRED(pTimer1))
            {
                //LineSensor_enableEmitter();
                LineSensor_read(&values);
                //sumOfActualValues = 0u;
                //sumOfActualValues += values.value[LINESENSOR_LEFT];
                //sumOfActualValues += values.value[LINESENSOR_MIDDLE_LEFT];
                //sumOfActualValues += values.value[LINESENSOR_MIDDLE];
                //sumOfActualValues += values.value[LINESENSOR_MIDDLE_RIGHT];
                //sumOfActualValues += values.value[LINESENSOR_RIGHT];

                sumOfWeightedValues = 0;
                //sumOfWeightedValues += values.value[LINESENSOR_LEFT] * 555;
                sumOfWeightedValues += values.value[LINESENSOR_MIDDLE_LEFT] * -1;// * -95;
                sumOfWeightedValues += values.value[LINESENSOR_MIDDLE] * 0;
                sumOfWeightedValues += values.value[LINESENSOR_MIDDLE_RIGHT]; // * 95;
                //sumOfWeightedValues += values.value[LINESENSOR_RIGHT] * 1445;

                if (sumOfWeightedValues < 0)
                {
            
                } 
                Pos = sumOfWeightedValues; 

                snprintf(position, sizeof(position), "%d", Pos);

                Display_clear();
                //Display_gotoxy(0, 6);
                //Display_write(text, sizeof(text));
                Display_gotoxy(10, 6);
                Display_write(position, sizeof(position));

                //LineSensor_disableEmitter();

            
            //char text[] = "CALIBRATION \n DONE";
            //Display_clear();
            //Display_gotoxy(0, 0);
            //Display_write(text0, sizeof(text0));
            //Display_gotoxy(0, 1);
            //Display_write(text1, sizeof(text1));
            //Display_gotoxy(0, 2);
            //Display_write(text2, sizeof(text2));
            //Display_gotoxy(0, 3);
            //Display_write(text3, sizeof(text3));
            //Display_gotoxy(0, 4);
            //Display_write(text4, sizeof(text4));
            //LineSensor_enableEmitter();
            //LineSensor_read(&values);
            //LineSensor_disableEmitter();
            
            //values.value[LINESENSOR_LEFT]
            snprintf(value0, sizeof(value0), "%d", values.value[LINESENSOR_LEFT]);
            snprintf(value1, sizeof(value1), "%d", values.value[LINESENSOR_MIDDLE_LEFT]);
            snprintf(value2, sizeof(value2), "%d", values.value[LINESENSOR_MIDDLE]);
            snprintf(value3, sizeof(value3), "%d", values.value[LINESENSOR_MIDDLE_RIGHT]);
            snprintf(value4, sizeof(value4), "%d", values.value[LINESENSOR_RIGHT]);

            //lastValue0 = values.value[LINESENSOR_LEFT];
            //lastValue1 = values.value[LINESENSOR_MIDDLE_LEFT];
            //lastValue2 = values.value[LINESENSOR_MIDDLE];
            //lastValue3 = values.value[LINESENSOR_MIDDLE_RIGHT];
            //lastValue4 = values.value[LINESENSOR_RIGHT];

            Display_gotoxy(10, 0);
            Display_write(value0, sizeof(value0));
            Display_gotoxy(10, 1);
            Display_write(value1, sizeof(value1));
            Display_gotoxy(10, 2);
            Display_write(value2, sizeof(value2));
            Display_gotoxy(10, 3);
            Display_write(value3, sizeof(value3));
            Display_gotoxy(10, 4);
            Display_write(value4, sizeof(value4));
            
            SoftTimer_Stop(pTimer1);
            eStates = START_TIMER;
            }

            break;
        case CONTROLL:
            if SOFTTIMER_IS_EXPIRED(pTimer1)
            {
                //eStates = IDLE;
            }
            LineSensor_read(&values);

            sumOfWeightedValues = 0;
            //sumOfWeightedValues += values.value[LINESENSOR_LEFT] * 555;
            sumOfWeightedValues += values.value[LINESENSOR_MIDDLE_LEFT] * -1;// * -95;
            sumOfWeightedValues += values.value[LINESENSOR_MIDDLE] * 0;
            sumOfWeightedValues += values.value[LINESENSOR_MIDDLE_RIGHT] * 1;
            sumOfWeightedValues += values.value[LINESENSOR_LEFT] * -5;
            //sumOfWeightedValues += values.value[LINESENSOR_MIDDLE_LEFT] * -7;
            sumOfWeightedValues += values.value[LINESENSOR_RIGHT] * 5;
            //sumOfWeightedValues += values.value[LINESENSOR_MIDDLE_RIGHT] * 7;

            //if (sumOfWeightedValues < 0)
            //{
            //    sumOfWeightedValues = sumOfWeightedValues * sumOfWeightedValues * -1;
            //}
            //else
            //{
            //    sumOfWeightedValues = sumOfWeightedValues * sumOfWeightedValues;
            //}

           // Float32 kp = 0.01287;
           // Float32 kd = 0.003;
           // Float32 ki = 0.00000002;
            //Float32 kp = 0.01287;
            //Float32 kd = 0.004;
            //Float32 ki = 0.00002;
            Float32 kp = 0.04;
            Float32 kd = 0.0;
            Float32 ki = 0.0;



            Int32 speedDifference = kp*sumOfWeightedValues + kd*(sumOfWeightedValues-sumOfWeightedValuesBefore) + ki * (sumOfWeightedValuesIntegrated); 

            Int32 left = speedDifference + MOTORSPEED;
            Int32 right = -speedDifference + MOTORSPEED;

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
            /*
            Display_clear();
            snprintf(speedLeft, sizeof(speedLeft), "%d", left);
            snprintf(speedRight, sizeof(speedRight), "%d", right);

            Display_gotoxy(0, 0);
            Display_write("speedRight: ", sizeof("speedRight: "));
            Display_gotoxy(0, 12);
            Display_write(speedRight, sizeof(speedRight));

            Display_gotoxy(2, 3);
            Display_write("speedLeft: ", sizeof("speedLeft: "));
            Display_gotoxy(2, 12);
            Display_write(speedLeft, sizeof(speedLeft));
            */
            DriveControl_drive(DRIVE_CONTROL_MOTOR_LEFT, left, DRIVE_CONTROL_FORWARD);
            DriveControl_drive(DRIVE_CONTROL_MOTOR_RIGHT, right, DRIVE_CONTROL_FORWARD);
            sumOfWeightedValuesBefore = sumOfWeightedValues;
            sumOfWeightedValuesIntegrated += sumOfWeightedValues;
            

        case IDLE:


            break;
        
    }

}

