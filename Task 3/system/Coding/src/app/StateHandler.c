/***************************************************************************************************
  (c) NewTec GmbH 2024   -   www.newtec.de
***************************************************************************************************/
/**
 * @file       StateHandler.c
 *
 * Module contains the functions for the genenrall logic of the statemachine.
 */
/**************************************************************************************************/

/* INCLUDES ***************************************************************************************/
#include "StateHandler.h"

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

/* VARIABLES **************************************************************************************/

/* store the current state ID */
static Bool gProcessedEntryFunction = FALSE;

/* store the current state ID */
static States gCurrentState = INITIALIZATION_STATE;

/* store the most recent error code */
static ErrorHandlerErrorCode gErrorCode = ERRORHANDLER_MAIN_SCHEDULER_EXIT;

/* EXTERNAL FUNCTIONS *****************************************************************************/

void StateHandler_stateHandler(void)
{
    switch (gCurrentState)
    {
        case DRIVE_LAP_STATE:
            if (!gProcessedEntryFunction)
            {
                DriveLapState_enterStartTimer3();
                gProcessedEntryFunction = TRUE;
            }

            DriveLapState_processDriveOnTrackLine();

            if (DriveLapState_checkTranstionTriggerStartlineFound())
            {
                gCurrentState = LAP_FINISHED_STATE;
                gProcessedEntryFunction = FALSE;
            }
            else if (DriveLapState_checkTranstionTriggerTrackNotFound())
            {
                gCurrentState = ERROR_STATE;
                gErrorCode = ERRORHANDLER_LINELOST_TIMEOUT;
                gProcessedEntryFunction = FALSE;
            }
            else if (DriveLapState_checkTranstionTriggerTimer2Exceeds20s())
            {
                gCurrentState = ERROR_STATE;
                gErrorCode = ERRORHANDLER_DRIVING_TIMEOUT;
                gProcessedEntryFunction = FALSE;
            }
            break;

        case ERROR_STATE:
            if (!gProcessedEntryFunction)
            {
                ErrorState_enterStopDriveAndPlayAlarmAndDisplayError(gErrorCode);
                gProcessedEntryFunction = TRUE;
            }

            ErrorState_processPollingButtonA();

            if (ErrorState_checkTransitionTriggerButtonAPressed())
            {
                gCurrentState = READY_STATE;
                gProcessedEntryFunction = FALSE;
            }
            break;

        case LAP_FINISHED_STATE:
            if (!gProcessedEntryFunction)
            {
                LapFinishedState_enterDisplayTimeAndStopDriveAndPlayBeep();
                gProcessedEntryFunction = TRUE;
            }

            LapFinishedState_processPollingButtonA();

            if (LapFinishedState_checkTransitionTriggerButtonAPressed())
            {
                gCurrentState = READY_STATE;
                gProcessedEntryFunction = FALSE;
            }
            break;

        case SEARCHING_STARTLINE_STATE:
            if (!gProcessedEntryFunction)
            {
                SearchingStartLineState_enterStartTimer1AndStartDriving();
                gProcessedEntryFunction = TRUE;
            }

            SearchingStartLineState_processSearchForStartline();

            if (SearchningStartLineState_checkTransitionTriggerStartlineFound())
            {
                SearchingStartLineState_exitStartTimer2AndPlayBeepIfStartlineFound();
                gCurrentState = DRIVE_LAP_STATE;
                gProcessedEntryFunction = FALSE;
            }
            else if (SearchningStartLineState_checkTransitionTriggerTimer1Exceeds5s())
            {
                SearchingStartLineState_exitStartTimer2AndPlayBeepIfStartlineFound();
                gCurrentState = ERROR_STATE;
                gProcessedEntryFunction = FALSE;
                gErrorCode = ERRORHANDLER_RELEASETRACK_TIMER_START_FAIL;
            }
            break;

        case INITIALIZATION_STATE:
            if (!gProcessedEntryFunction)
            {
                InitializationState_enterDisplayNameAndStartTimer1();
                gProcessedEntryFunction = TRUE;
            }

            if (InitializationState_checkTransitionTriggerTimer1Exceeds2s())
            {
                InitializationState_exitStopTimer1();
                gCurrentState = CALIBRATION_STATE;
                gProcessedEntryFunction = FALSE;
            }
            break;

        case CALIBRATION_STATE:
            CalibrationState_processCalibrate();

            if (CalibrationState_checkTransitionTriggerCalibrationDone())
            {
                gCurrentState = READY_STATE;
            }
            break;

        case READY_STATE:
            if (!gProcessedEntryFunction)
            {
                ReadyState_enterDisplayState();
                gProcessedEntryFunction = TRUE;
            }

            ReadyState_processPollingButtons();

            if (ReadyState_checkTransitionTriggerButtonAPressed())
            {
                Display_clear();
                gCurrentState = PRE_DRIVE_STATE;
                gProcessedEntryFunction = FALSE;
            }
            else if (ReadyState_checkTransitionTriggerButtonBPressed())
            {
                Display_clear();
                gCurrentState = PARAMETER_SET_STATE;
                gProcessedEntryFunction = FALSE;
            }
            else if (ReadyState_checkTransitionTriggerButtonCPressed())
            {
                Display_clear();
                gCurrentState = CALIBRATION_STATE;
                gProcessedEntryFunction = FALSE;
            }
            break;

        case PARAMETER_SET_STATE:
            if (!gProcessedEntryFunction)
            {
                ParameterSetState_enterDisplayParameterSets();
                gProcessedEntryFunction = TRUE;
            }

            ParameterSetState_processSetParameterSet();

            if (ParameterSetState_checkTransitionTriggerConfigDone())
            {
                ParameterSetState_exitDisplaySelectedParameterSetFor3s();
                gCurrentState = READY_STATE;
                gProcessedEntryFunction = FALSE;
            }
            break;

        case PRE_DRIVE_STATE:
            if (!gProcessedEntryFunction)
            {
                PreDriveState_enterStartTimer1AndWaitFor3s();
                gProcessedEntryFunction = TRUE;
            }

            if (PreDriveState_checkTransitionTriggerTimer1Exceeds3s())
            {
                PreDriveState_exitStopTimer1();
                gCurrentState = SEARCHING_STARTLINE_STATE;
                gProcessedEntryFunction = FALSE;
            }
            break;

    } 
}

/* INTERNAL FUNCTIONS *****************************************************************************/


