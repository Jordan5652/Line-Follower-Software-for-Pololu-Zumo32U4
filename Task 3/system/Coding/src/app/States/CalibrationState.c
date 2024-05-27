/***************************************************************************************************
  (c) NewTec GmbH 2024   -   www.newtec.de
***************************************************************************************************/
/**
 * @file       CalibrationState.c
 *
 * contains the functions and variables for the CalibrationState.
 */
/**************************************************************************************************/

/* INCLUDES ***************************************************************************************/
#include "CalibrationState.h"


/* CONSTANTS **************************************************************************************/
#define CALIB_SPEED 33u       /**< Motor speed while calibrating */
#define CALIB_SPEED_SLOW 25u  /**< Motor speed while centering on line  */

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

/* VARIABLES **************************************************************************************/

/** Calibration state of local state machine */
static CalibrationState gState = CALIBRATION_STATE_INIT;

/** Timer used by calibration steps. */
//static SoftTimer gTimer;

/** Variable used for checking whether calibration was finished*/
static Bool gCalibrationFinished = false; 
/* EXTERNAL FUNCTIONS *****************************************************************************/
char textTimeout[] = "TIMEOUT: CALIBRATION FAILED!"; 

void CalibrationState_processCalibrate(void)
{
  LineSensorValues values;

    switch (gState)
    {
        case CALIBRATION_STATE_INIT:
            //if (SOFTTIMER_IS_EXPIRED(&gTimer))
            //if (SOFTTIMER_IS_EXPIRED(pTimer1))
            //{
                gState = CALIBRATION_STATE_TURN_RIGHT_UNTIL_LEFT_SENSOR;
                //SoftTimer_start(&gTimer, 5000u);
                SoftTimer_start(pTimer1, 5000u);
                LineSensor_startCalibration();
            //}
            //REMOVE LATER!
            //else 
            //{
            //    Display_clear();
            //    Display_write(WTF1, sizeof(WTF1));
            //}
            //REMOVE LATER END!
            break;

        case CALIBRATION_STATE_TURN_RIGHT_UNTIL_LEFT_SENSOR:
            DriveControl_drive(DRIVE_CONTROL_MOTOR_LEFT, CALIB_SPEED, DRIVE_CONTROL_FORWARD);
            DriveControl_drive(DRIVE_CONTROL_MOTOR_RIGHT, CALIB_SPEED, DRIVE_CONTROL_BACKWARD);

            //if (SOFTTIMER_IS_EXPIRED(&gTimer))
            if (SOFTTIMER_IS_EXPIRED(pTimer1))
            {
                gState = CALIBRATION_STATE_TIMEOUT;
            }

            LineSensor_read(&values);
            if (true == (values.calibrated[LINESENSOR_LEFT] && CALIB_OVER_LINE(values.value[LINESENSOR_LEFT])))
            {
                //SoftTimer_restart(&gTimer);
                SoftTimer_restart(pTimer1);
                gState = CALIBRATION_STATE_TURN_LEFT_UNTIL_RIGHT_SENSOR;
            }
            break;

        case CALIBRATION_STATE_TURN_LEFT_UNTIL_RIGHT_SENSOR:
            DriveControl_drive(DRIVE_CONTROL_MOTOR_LEFT, CALIB_SPEED, DRIVE_CONTROL_BACKWARD);
            DriveControl_drive(DRIVE_CONTROL_MOTOR_RIGHT, CALIB_SPEED, DRIVE_CONTROL_FORWARD);

            //if (SOFTTIMER_IS_EXPIRED(&gTimer))
            if (SOFTTIMER_IS_EXPIRED(pTimer1))
            {
                gState = CALIBRATION_STATE_TIMEOUT;
            }

            LineSensor_read(&values);
            if (true == (values.calibrated[LINESENSOR_RIGHT] &&  CALIB_OVER_LINE(values.value[LINESENSOR_RIGHT])))
            {
                if (!LineSensor_getCalibrationState())
                {
                    /* restart sequence, some sensors not yet calibrated. */
                    gState = CALIBRATION_STATE_TURN_RIGHT_UNTIL_LEFT_SENSOR;
                }
                else 
                {
                    //SoftTimer_restart(&gTimer);
                    SoftTimer_restart(pTimer1);
                    gState = CALIBRATION_STATE_CENTER_ON_LINE;
                }
            }
            break;

        case CALIBRATION_STATE_CENTER_ON_LINE:
            DriveControl_drive(DRIVE_CONTROL_MOTOR_LEFT, CALIB_SPEED_SLOW, DRIVE_CONTROL_FORWARD);
            DriveControl_drive(DRIVE_CONTROL_MOTOR_RIGHT, CALIB_SPEED_SLOW, DRIVE_CONTROL_BACKWARD);

            //if (SOFTTIMER_IS_EXPIRED(&gTimer))
            if (SOFTTIMER_IS_EXPIRED(pTimer1))
            {
                gState = CALIBRATION_STATE_TIMEOUT;
            }

            LineSensor_read(&values);

            /* stop if only middle sensor sees a line */

            if (CALIB_NO_LINE(values.value[LINESENSOR_LEFT]) &&
                CALIB_NO_LINE(values.value[LINESENSOR_MIDDLE_LEFT]) &&
                CALIB_OVER_LINE(values.value[LINESENSOR_MIDDLE]) &&
                CALIB_NO_LINE(values.value[LINESENSOR_MIDDLE_RIGHT]) &&
                CALIB_NO_LINE(values.value[LINESENSOR_RIGHT]))
            {
                DriveControl_drive(DRIVE_CONTROL_MOTOR_LEFT, 0u, DRIVE_CONTROL_FORWARD);
                DriveControl_drive(DRIVE_CONTROL_MOTOR_RIGHT, 0u, DRIVE_CONTROL_BACKWARD);

                //SoftTimer_Stop(&gTimer);
                SoftTimer_Stop(pTimer1);

                //if (SOFTTIMER_RET_SUCCESS != SoftTimerHandler_unRegister(&gTimer))
                //{
                    //errorState_enter(pState, ERRORHANDLER_CALIBRATE_TIMER_UNINIT_FAIL);
                    //gState = CALIBRATION_STATE_TIMEOUT;
                //}
                //else
                //{
                //    gState = CALIBRATION_STATE_FINISHED;

                //}
                gState = CALIBRATION_STATE_FINISHED;
                
                //gState = CALIBRATION_STATE_FINISHED;
            }
            break;

        case CALIBRATION_STATE_TIMEOUT:

            DriveControl_drive(DRIVE_CONTROL_MOTOR_LEFT, 0u, DRIVE_CONTROL_FORWARD);
            DriveControl_drive(DRIVE_CONTROL_MOTOR_RIGHT, 0u, DRIVE_CONTROL_BACKWARD);
            LineSensor_stopCalibration();
            Display_clear();
            Display_write(textTimeout, sizeof(textTimeout));
            gState = CALIBRATION_STATE_FINISHED;
            //ErrorState_enter(pState, ERRORHANDLER_CALIBRATE_TIMEOUT);
            break;

        case CALIBRATION_STATE_FINISHED:
            LineSensor_stopCalibration();
            //SoftTimerHandler_unRegister(&gTimer);
            SoftTimer_Stop(pTimer1);
            //ReadyState_enter(pState);
            gCalibrationFinished = true;
            break;
    }

}


extern Bool CalibrationState_checkTransitionTriggerCalibrationDone(void)
{
    if (gCalibrationFinished)
    {
        gCalibrationFinished = false; //resetting variable in case calibration is done again later
        return true;

    }
    else
    {
        return false; 
    }

}

/* INTERNAL FUNCTIONS *****************************************************************************/