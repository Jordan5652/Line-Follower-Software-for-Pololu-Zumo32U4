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

#include "GlobalTimers.h"
/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

/** Internal Task cyclic worker function.
 * @param[in] data task data (ignored).
 */
static void mainTaskWork (void * data);

/* VARIABLES **************************************************************************************/
Bool test = false;

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
 
#include "PositionControl.h"
#include "Display.h"
#include "Button.h"
#include "CalibrationState.h"

typedef enum
{
    INIT,
    CALIBRATION_STATE_BLA,
    TEST_SEARCH_TRACK_LINE

}states;

states State = INIT;
//extern LineSensorValues gSensorValues;

char value0Text[8]; 
char value1Text[8]; 
char value2Text[8]; 
char value3Text[8]; 
char value4Text[8]; 

static void mainTaskWork(void * data)
{
    (void)data;

    /* TODO: Add your application here. */
    StateHandler_stateHandler();
    /*
    switch (State)
    {
        case INIT:
            SoftTimerHandler_register(pTimer1);
            State = CALIBRATION_STATE_BLA;
            Display_write("STARTLINE DETECTED!", sizeof("STARTLINE DETECTED"));
            break;
        case CALIBRATION_STATE_BLA:
            if (FALSE == CalibrationState_checkTransitionTriggerCalibrationDone())
            {
                CalibrationState_processCalibrate();
            }
            else
            {
                State = TEST_SEARCH_TRACK_LINE;
                LineSensor_enableEmitter();
            }
            break;

        case TEST_SEARCH_TRACK_LINE:
            if (Button_getState(BUTTON_ID_A) == BUTTON_STATE_PRESSED)
            {
                PositionControl_UpdateSensorValues();
                Display_clear();
                Display_gotoxy(0,0);
                if(PosionControl_checkForStartLine())
                {
                    Display_clear();
                    Display_write("STARTLINE DETECTED!", sizeof("STARTLINE DETECTED"));
                }
                else
                {
                    Display_clear();
                    Display_write("AIN'T DETECTING SHIT!", sizeof("AIN'T DETECTING SHIT!"));
                }

            Display_gotoxy(0,1);
            Display_write("SENSOR L:", sizeof("SENSOR L:"));
            snprintf(value0Text, sizeof(value0Text),"%u", gSensorValues.value[LINESENSOR_LEFT]);
            Display_gotoxy(12,1);
            Display_write(value0Text, sizeof(value0Text));

            Display_gotoxy(0,2);
            Display_write("SENSOR ML:", sizeof("SENSOR ML:"));
            snprintf(value1Text, sizeof(value1Text),"%u", gSensorValues.value[LINESENSOR_MIDDLE_LEFT]);
            Display_gotoxy(12,2);
            Display_write(value1Text, sizeof(value1Text));

            Display_gotoxy(0,3);
            Display_write("SENSOR M:", sizeof("SENSOR M:"));
            snprintf(value2Text, sizeof(value2Text),"%u", gSensorValues.value[LINESENSOR_MIDDLE]);
            Display_gotoxy(12,3);
            Display_write(value2Text, sizeof(value2Text));

            Display_gotoxy(0,4);
            Display_write("SENSOR MR:", sizeof("SENSOR MR:"));
            snprintf(value3Text, sizeof(value3Text),"%u", gSensorValues.value[LINESENSOR_MIDDLE_RIGHT]);
            Display_gotoxy(12,4);
            Display_write(value3Text, sizeof(value3Text));

            Display_gotoxy(0,5);
            Display_write("SENSOR R:", sizeof("SENSOR R:"));
            snprintf(value4Text, sizeof(value4Text), "%u", gSensorValues.value[LINESENSOR_RIGHT]);
            Display_gotoxy(12,5);
            Display_write(value4Text, sizeof(value4Text));



            
                
            }

            break;
            

    }

    */
}

