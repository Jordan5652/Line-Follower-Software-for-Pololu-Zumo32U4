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
#define CALIB_SPEED 30u       /**< Motor speed while calibrating */
#define CALIB_SPEED_SLOW 25u  /**< Motor speed while centering on line  */

#define WHITE_BACKGROUND_VALUE_TRESHHOLD 200u /**< Thresshhold of value of linesensor: when value is below, white background is beeing detected */
//#define BLACK_LINE_VALUE_TRESHHOLD 650u /**< Thresshhold of value of linesensor: when value is below, white background is beeing detected */
#define BLACK_LINE_VALUE_TRESHHOLD 750u

/* MACROS *****************************************************************************************/
#define CALIB_NO_LINE(sensorValue) \ 
    ((WHITE_BACKGROUND_VALUE_TRESHHOLD) > (sensorValue))
#define CALIB_OVER_LINE(sensorValue) \
    ((BLACK_LINE_VALUE_TRESHHOLD) < (sensorValue))

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

/* VARIABLES **************************************************************************************/

/** Calibration state of local state machine */
static CalibrationState gState = CALIBRATION_STATE_INIT;

/** Variable used for checking whether calibration was finished*/
static Bool gCalibrationFinished = false;

/** buffer containing the text displayed when timeout occured during center line*/
static const UInt8 gCalibrationTimeOutMessage[] = "CALIBRATION TIMEOUT!";

/** buffer containing the text displayed when timeout occured during center line*/
static const UInt8 gCenterLineTimeOutMessage[] = "CENTER-LINE TIMEOUT!";

/* EXTERNAL FUNCTIONS *****************************************************************************/

void CalibrationState_processCalibrate(void)
{
  LineSensorValues values;

    switch (gState)
    {
        case CALIBRATION_STATE_INIT:
            
                gState = CALIBRATION_STATE_TURN_RIGHT_UNTIL_LEFT_SENSOR;
                SoftTimer_start(GlobalTimers_getTimer(TIMER1), 5000u);
                LineSensor_startCalibration();
            
            break;

        case CALIBRATION_STATE_TURN_RIGHT_UNTIL_LEFT_SENSOR:
            DriveControl_drive(DRIVE_CONTROL_MOTOR_LEFT, CALIB_SPEED, DRIVE_CONTROL_FORWARD);
            DriveControl_drive(DRIVE_CONTROL_MOTOR_RIGHT, CALIB_SPEED, DRIVE_CONTROL_BACKWARD);

            if (SOFTTIMER_IS_EXPIRED(GlobalTimers_getTimer(TIMER1)))
            {
                gState = CALIBRATION_STATE_TIMEOUT_CALIBRATION;
            }

            LineSensor_read(&values);
            if (true == (values.calibrated[LINESENSOR_LEFT] && CALIB_OVER_LINE(values.value[LINESENSOR_LEFT])))
            {
                SoftTimer_restart(GlobalTimers_getTimer(TIMER1));
                gState = CALIBRATION_STATE_TURN_LEFT_UNTIL_RIGHT_SENSOR;
            }
            break;

        case CALIBRATION_STATE_TURN_LEFT_UNTIL_RIGHT_SENSOR:
            DriveControl_drive(DRIVE_CONTROL_MOTOR_LEFT, CALIB_SPEED, DRIVE_CONTROL_BACKWARD);
            DriveControl_drive(DRIVE_CONTROL_MOTOR_RIGHT, CALIB_SPEED, DRIVE_CONTROL_FORWARD);

            if (SOFTTIMER_IS_EXPIRED(GlobalTimers_getTimer(TIMER1)))
            {
                gState = CALIBRATION_STATE_TIMEOUT_CALIBRATION;
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
                    SoftTimer_restart(GlobalTimers_getTimer(TIMER1));
                    gState = CALIBRATION_STATE_CENTER_ON_LINE;
                }
            }
            break;

        case CALIBRATION_STATE_CENTER_ON_LINE:
            DriveControl_drive(DRIVE_CONTROL_MOTOR_LEFT, CALIB_SPEED_SLOW, DRIVE_CONTROL_BACKWARD);
            DriveControl_drive(DRIVE_CONTROL_MOTOR_RIGHT, CALIB_SPEED_SLOW, DRIVE_CONTROL_FORWARD);

            if (SOFTTIMER_IS_EXPIRED(GlobalTimers_getTimer(TIMER1)))
            {
                gState = CALIBRATION_STATE_TIMEOUT_CENTER_LINE;
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

                SoftTimer_Stop(GlobalTimers_getTimer(TIMER1));

                gState = CALIBRATION_STATE_FINISHED;
                
            }
            break;

        case CALIBRATION_STATE_TIMEOUT_CALIBRATION:

            DriveControl_drive(DRIVE_CONTROL_MOTOR_LEFT, 0u, DRIVE_CONTROL_FORWARD);
            DriveControl_drive(DRIVE_CONTROL_MOTOR_RIGHT, 0u, DRIVE_CONTROL_BACKWARD);
            LineSensor_stopCalibration();
            Display_clear();
            Display_write(gCalibrationTimeOutMessage, sizeof(gCalibrationTimeOutMessage));
            gState = CALIBRATION_STATE_FINISHED;
            
            break;
        case CALIBRATION_STATE_TIMEOUT_CENTER_LINE:
            DriveControl_drive(DRIVE_CONTROL_MOTOR_LEFT, 0u, DRIVE_CONTROL_FORWARD);
            DriveControl_drive(DRIVE_CONTROL_MOTOR_RIGHT, 0u, DRIVE_CONTROL_BACKWARD);
            LineSensor_stopCalibration();
            Display_clear();
            Display_write(gCenterLineTimeOutMessage, sizeof(gCenterLineTimeOutMessage));
            gState = CALIBRATION_STATE_FINISHED;
            
            break;

        case CALIBRATION_STATE_FINISHED:
            LineSensor_stopCalibration();
            SoftTimer_Stop(GlobalTimers_getTimer(TIMER1));
            gCalibrationFinished = TRUE;
            break;
    }

}


extern Bool CalibrationState_checkTransitionTriggerCalibrationDone(void)
{
    if (gCalibrationFinished)
    {
        gCalibrationFinished = FALSE; //resetting variable in case calibration is done again later
        gState = CALIBRATION_STATE_INIT; //resetting statemachine
        return TRUE;

    }
    else
    {
        return FALSE; 
    }

}

/* INTERNAL FUNCTIONS *****************************************************************************/