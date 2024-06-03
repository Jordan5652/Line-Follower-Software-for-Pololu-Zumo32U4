
/***************************************************************************************************
  (c) NewTec GmbH 2024   -   www.newtec.de
***************************************************************************************************/
/**
 * @file       ErrorState.c
 *
 * Contains the functions and variables for the ErrorState.
 */
/**************************************************************************************************/

/* INCLUDES ***************************************************************************************/
#include "ErrorState.h"


/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

/* VARIABLES **************************************************************************************/
const UInt8 *ErrorNames[] = {
    "ERRORHANDLER_MAIN_SCHEDULER_EXIT",           // 1
    "ERRORHANDLER_MAINTASK_INIT_FAIL",            // 100
    "ERRORHANDLER_STARTUP_INIT_FAIL",             // 110
    "ERRORHANDLER_STARTUP_UNINIT_FAIL",           // 111
    "ERRORHANDLER_CALIBRATE_TIMER_INIT_FAIL",     // 200
    "ERRORHANDLER_CALIBRATE_ALOGRITMIC_FAIL",     // 201
    "ERRORHANDLER_CALIBRATE_TIMEOUT",             // 202
    "ERRORHANDLER_CALIBRATE_TIMER_UNINIT_FAIL",   // 203
    "ERRORHANDLER_RELEASETRACK_TIMER_INIT_FAIL",  // 250
    "ERRORHANDLER_RELEASETRACK_TIMER_UNINIT_FAIL",// 251
    "ERRORHANDLER_RELEASETRACK_TIMER_START_FAIL", // 252
    "ERRORHANDLER_DRIVING_TIMER_INIT_FAIL",       // 300
    "ERRORHANDLER_DRIVING_TIMER_UNINIT_FAIL",     // 301
    "ERRORHANDLER_DRIVING_TIMER_START_FAIL",      // 302
    "ERRORHANDLER_DRIVING_TIMEOUT",               // 303
    "ERRORHANDLER_LINELOST_TIMEOUT",              // 304
    "ERRORHANDLER_FINISH_TIMER_INIT_FAIL",        // 400
    "ERRORHANDLER_FINISH_TIMER_UNINIT_FAIL"       // 401
};
/* EXTERNAL FUNCTIONS *****************************************************************************/

extern void ErrorState_enterStopDriveAndPlayAlarmAndDisplayError(UInt8* errorName, UInt8 sizeofErrorName, UInt8 errorCode)
{
    // TODO  ErrorHandlerErrorCode errorcode rausfinden den richtignen   
    

    

    Display_gotoxy(3,3);

    Display_write(errorName, sizeofErrorName);
    ErrorHandler_show(errorCode);
    DriveControl_drive(DRIVE_CONTROL_MOTOR_LEFT, 0, DRIVE_CONTROL_FORWARD);
    DriveControl_drive(DRIVE_CONTROL_MOTOR_RIGHT, 0, DRIVE_CONTROL_BACKWARD);
        Buzzer_beep(BUZZER_ALARM);



}

extern void ErrorState_processPollingButtonA(void)
{
    if(true == Button_getState(BUTTON_ID_A))
    {
      //TODO
    }
}

extern Bool ErrorState_checkTransitionTriggerButtonAPressed(void)
{
      // TODO  ErrorHandlerErrorCode errorcode rausfinden den richtignen   

        Buzzer_beep(BUZZER_ALARM);
        handleError(100 , true);


}

/* INTERNAL FUNCTIONS *****************************************************************************/
