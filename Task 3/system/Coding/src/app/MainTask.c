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

//RINGBUFFER FOR MOVING AVERAGES
//typedef struct
//{


//}RingBuffer; 


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
#define MOTORSPEED 100u

static char text[] = "POSITION: ";
static char position[8];
//static char speedLeft[8];
//static char speedRight[8];

static LineSensorValues values;
uint32_t sumOfActualValues;
Int16 sumOfWeightedValues;
Int16 buffer[30] = {0};
UInt8 bufferElements = 0u;
Int16 sumOfWeightedValuesBefore = 0u;
Int16 sumOfWeightedValuesIntegrated = 0u;
static Bool idleEnetered = TRUE;
Int16 Pos = 0;
static UInt16 Counter = 0u; 
//static char test[] = "ENTERED IDLE";
static States eStates = INIT;
static void mainTaskWork(void * data)
{
    (void)data;

    /* TODO: Add your application here. */
    switch (eStates)
    {
        case INIT:
            SoftTimer_init(pTimer1);
            SoftTimerHandler_register(pTimer1);
            eStates = CALIBRATE;
            //SoftTimer_start(pTimer1, 3000u);
            //DriveControl_drive(DRIVE_CONTROL_MOTOR_LEFT, 100u, DRIVE_CONTROL_FORWARD);
            //DriveControl_drive(DRIVE_CONTROL_MOTOR_RIGHT, 100u, DRIVE_CONTROL_FORWARD);
            //eStates = IDLE;
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
                //eStates = POS;
                SoftTimer_Stop(pTimer1);
                SoftTimerHandler_unRegister(pTimer1);
                //SoftTimer_start(pTimer1, 5000u);

            }
            

            break; 
        case POS:
            //if (SOFTTIMER_IS_EXPIRED(pTimer1))
            if (Button_getState(BUTTON_ID_A) == BUTTON_STATE_PRESSED)
            {
                //LineSensor_enableEmitter();
                LineSensor_read(&values);
                //LineSensor_disableEmitter();
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

                //if value of line sensor middle is smaller than 250 
                if (values.value[LINESENSOR_MIDDLE] < 250)
                {
                    //just for driving over gap, wioll be removed later
                    if(values.value[LINESENSOR_MIDDLE] < 120 
                       && values.value[LINESENSOR_MIDDLE_RIGHT] < 120 
                       && values.value[LINESENSOR_MIDDLE_RIGHT] < 120)
                    {
                        Pos = 0u;
                    }
                    
                    else
                    {
                        //if sumOfWeightedValues()
                    }
                    
                } 
                else
                {
                    Pos = sumOfWeightedValues; 
                }


                Pos = sumOfWeightedValues; 

                snprintf(position, sizeof(position), "%d", Pos);

                Display_clear();
                Display_gotoxy(0, 6);
                Display_write(text, sizeof(text));
                Display_gotoxy(10, 6);
                Display_write(position, sizeof(position));

                //LineSensor_disableEmitter();

            
            //char text[] = "CALIBRATION \n DONE";
            
            Display_gotoxy(0, 0);
            Display_write(text0, sizeof(text0));
            Display_gotoxy(0, 1);
            Display_write(text1, sizeof(text1));
            Display_gotoxy(0, 2);
            Display_write(text2, sizeof(text2));
            Display_gotoxy(0, 3);
            Display_write(text3, sizeof(text3));
            Display_gotoxy(0, 4);
            Display_write(text4, sizeof(text4));
            //LineSensor_enableEmitter();
            //LineSensor_read(&values);
            //LineSensor_disableEmitter();
            
            //values.value[LINESENSOR_LEFT]
            snprintf(value0, sizeof(value0), "%d", values.value[LINESENSOR_LEFT]);
            snprintf(value1, sizeof(value1), "%d", values.value[LINESENSOR_MIDDLE_LEFT]);
            snprintf(value2, sizeof(value2), "%d", values.value[LINESENSOR_MIDDLE]);
            snprintf(value3, sizeof(value3), "%d", values.value[LINESENSOR_MIDDLE_RIGHT]);
            snprintf(value4, sizeof(value4), "%d", values.value[LINESENSOR_RIGHT]);


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
            //eStates = START_TIMER;
            }

            break;
        case CONTROLL:
            if SOFTTIMER_IS_EXPIRED(pTimer1)
            {
                //eStates = IDLE;
            }
            //LineSensor_enableEmitter();
            LineSensor_read(&values);
            //LineSensor_disableEmitter();

            sumOfWeightedValues = 0;

            Bool overLine = TRUE;

            sumOfWeightedValues += values.value[LINESENSOR_MIDDLE_LEFT] * -1;// * -95;
            sumOfWeightedValues += values.value[LINESENSOR_MIDDLE] * 0;
            sumOfWeightedValues += values.value[LINESENSOR_MIDDLE_RIGHT] * 1;
            sumOfWeightedValues += values.value[LINESENSOR_LEFT] * -5;
            sumOfWeightedValues += values.value[LINESENSOR_RIGHT] * 5;
            
            //Bool lastDirectionLeft = (sumOfWeightedValues < 0);
            //Float32 kp = 0.03;
            //Float32 kp = 0.06;
            //Float32 kp = 0.12; SPEED 70!
            //Float32 kp = 0.22; SPEED 85!
            //Float32 kp = 0.3; SPEED 100!
            Float32 kp = 16.0;
            Float32 kd = 2.6;
            Float32 ki = 0.0011;
 
            UInt8 speed = MOTORSPEED;
            
            //test adaptive control
            if(values.value[LINESENSOR_MIDDLE] > 240)
            {
                kp = 0.1;
                kd = 0.04;
                ki = 0.0001;
            }

            else{ 
                speed = 70;
            if((values.value[LINESENSOR_MIDDLE_LEFT] < 120u) && 
               (values.value[LINESENSOR_MIDDLE_LEFT] < 120u) && 
               (values.value[LINESENSOR_MIDDLE_RIGHT] < 120u) &&
               (values.value[LINESENSOR_LEFT] < 120u) &&
               (values.value[LINESENSOR_RIGHT] < 120u))
            {
                Counter++;
                if(Counter >= 2u){
                //DriveControl_drive(DRIVE_CONTROL_MOTOR_LEFT, 0u, DRIVE_CONTROL_FORWARD);
                //DriveControl_drive(DRIVE_CONTROL_MOTOR_RIGHT, 0u, DRIVE_CONTROL_FORWARD);
                //Display_clear();
                //Display_write("WHY TF NOT?", sizeof("WHY TF NOT?"));
                //while (1);
                //{
                    /* code */
                //}
                
                //}
                overLine = FALSE;
                sumOfWeightedValuesIntegrated = 0;
                }

            }
            else
            {
                Counter = 0u;
            }
            }
            
            //just for testing
            /*
            else
            {
                
                */
                /*
                DriveControl_drive(DRIVE_CONTROL_MOTOR_LEFT, 0u, DRIVE_CONTROL_FORWARD);
                DriveControl_drive(DRIVE_CONTROL_MOTOR_RIGHT, 0u, DRIVE_CONTROL_FORWARD);
                Display_clear();
                Display_write("Curve detected!", sizeof("curve detected"));
                snprintf(value2, sizeof(value2), "%d", values.value[LINESENSOR_MIDDLE]);
                Display_gotoxy(10, 2);
                Display_write(value2, sizeof(value2));
                while (1);
                
                if (!((values.value[LINESENSOR_MIDDLE] > 100u) || 
                    (values.value[LINESENSOR_MIDDLE_RIGHT] > 100u) || 
                    (values.value[LINESENSOR_MIDDLE_RIGHT] > 100u)))
                {
                    //if (values.value[LINESENSOR_MIDDLE_LEFT] < 100u)
                    //{
                    //    if(values.value[LINESENSOR_MIDDLE_RIGHT] < 100u)
                    //    {
                    Counter++;
                    if(Counter > 20)
                    {

                    overLine = FALSE;
                    DriveControl_drive(DRIVE_CONTROL_MOTOR_LEFT, 0, DRIVE_CONTROL_FORWARD);
                    DriveControl_drive(DRIVE_CONTROL_MOTOR_RIGHT, 0, DRIVE_CONTROL_FORWARD);
                    
                    //snprintf(value0, sizeof(value0), "%d", values.value[LINESENSOR_LEFT]);
                    snprintf(value1, sizeof(value1), "%d", values.value[LINESENSOR_MIDDLE_LEFT]);
                    snprintf(value2, sizeof(value2), "%d", values.value[LINESENSOR_MIDDLE]);
                    snprintf(value3, sizeof(value3), "%d", values.value[LINESENSOR_MIDDLE_RIGHT]);
                    //snprintf(value4, sizeof(value4), "%d", values.value[LINESENSOR_RIGHT]);
                    Display_clear();
                    Display_gotoxy(10, 0);
                    //Display_write(value0, sizeof(value0));
                    Display_gotoxy(10, 1);
                    Display_write(value1, sizeof(value1));
                    Display_gotoxy(10, 2);
                    Display_write(value2, sizeof(value2));
                    Display_gotoxy(10, 3);
                    Display_write(value3, sizeof(value3));
                    Display_gotoxy(10, 4);
                    //Display_write(value4, sizeof(value4));

                    while(1);
                    }                        
                    
                }
                else{
                    Counter = 0u;
                    speed = 65;
                }
                //Display_clear();
                //Display_write("WHY TF NOT?", sizeof("WHY TF NOT?"));
                
            }
            */

            if(overLine)
            {

            sumOfWeightedValuesIntegrated += sumOfWeightedValues;

            if(sumOfWeightedValuesIntegrated > 30000)
            {
                sumOfWeightedValuesIntegrated = 30000;
            }
            if(sumOfWeightedValuesIntegrated < -30000)
            {
                sumOfWeightedValuesIntegrated = -30000;
            }

            Int32 speedDifference = kp*sumOfWeightedValues + kd*(sumOfWeightedValues-sumOfWeightedValuesBefore) + ki * (sumOfWeightedValuesIntegrated); 

            //adaptive controll
            

            /*
            Int32 left = 0;
            Int32 right = 0;
            
            //if(speedDifference > -20 && speedDifference < 20)
            if(0)
            {
                left = MOTORSPEED;
                right = MOTORSPEED;
            }
            else
            {
                if(speedDifference >= 0)
                {
                    left = speed;
                    right = -speedDifference + speed;

                    if (right < 0)
                    {
                        right = 0;
                    } 
                }
                else
                {
                    left = speedDifference + speed;
                    right = speed;

                    if (left < 0)
                    {
                        left = 0;
                    } 
                }
            }
            */
            /*
            char leftVal[7];
            char rigthVal[7];

            snprintf(leftVal, sizeof(leftVal), "%d", left);
            snprintf(rigthVal, sizeof(rigthVal), "%d", right);

            Display_clear();
            Display_gotoxy(0,0);
            Display_write("left Speed:", sizeof("left Speed:"));
            Display_gotoxy(0,1);
            Display_write("right Speed:", sizeof("right Speed"));
            Display_gotoxy(13,0);
            Display_write(leftVal, sizeof(leftVal));
            Display_gotoxy(13,1);
            Display_write(rigthVal, sizeof(rigthVal));

            eStates = START_TIMER;
            }
            */
            
            
            Int32 left = speedDifference + speed;
            Int32 right = -speedDifference + speed;

            Int32 leftAdditional = 0;
            Int32 rightAdditional = 0;

            if (left > right)
            {
                if(left > 100)
                {
                    rightAdditional = left-100;
                    right = right -rightAdditional;
                }
                else
                {
                    leftAdditional = right - 100;
                    left = left -leftAdditional;
                }
            }
            else
            {

            }

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
            }
            else
            {
                DriveControl_drive(DRIVE_CONTROL_MOTOR_LEFT, 100, DRIVE_CONTROL_FORWARD);
                DriveControl_drive(DRIVE_CONTROL_MOTOR_RIGHT, 100, DRIVE_CONTROL_FORWARD);
            }
            
        case IDLE:
            if SOFTTIMER_IS_EXPIRED(pTimer1)
            {
                DriveControl_drive(DRIVE_CONTROL_MOTOR_LEFT, 0u, DRIVE_CONTROL_FORWARD);
                DriveControl_drive(DRIVE_CONTROL_MOTOR_RIGHT, 0u, DRIVE_CONTROL_FORWARD);
                SoftTimer_Stop(pTimer1);
                Display_write("5 seconds passed?", sizeof("5 seconds passed?"));
            }

            break;
    }

}

