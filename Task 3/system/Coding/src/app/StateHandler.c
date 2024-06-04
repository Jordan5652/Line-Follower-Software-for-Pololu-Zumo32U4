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

/**
 * @brief store the current state ID
*/
static Bool processedEntryFunction = FALSE;

/**
 * @brief store the current state ID
*/
static States gCurrentState = INITIALIZATION_STATE;

static ErrorHandlerErrorCode gErrorCode = ERRORHANDLER_MAIN_SCHEDULER_EXIT;

/* EXTERNAL FUNCTIONS *****************************************************************************/

void StateHandler_stateHandler(void)
{
    switch(gCurrentState)
    {
        case DRIVE_LAP_STATE:
            DriveLapState_processDriveOnTrackLine();

            if(DriveLapState_checkTranstionTriggerStartlineFound())
            {
                gCurrentState = LAP_FINISHED_STATE;
            }
            else if(DriveLapState_checkTranstionTriggerTrackNotFound())
            {
                gCurrentState = SEARCH_TRACK_STATE;
            }
            else if(DriveLapState_checkTranstionTriggerTimer2Exceeds20s())
            {
                gCurrentState = ERROR_STATE;
                gErrorCode = ERRORHANDLER_DRIVING_TIMEOUT;
            }
            break;

        case ERROR_STATE:
            if(!processedEntryFunction)
            {
                ErrorState_enterStopDriveAndPlayAlarmAndDisplayError(gErrorCode);
                processedEntryFunction = TRUE;
            }

            ErrorState_processPollingButtonA();

            if(ErrorState_checkTransitionTriggerButtonAPressed())
            {
                gCurrentState = READY_STATE;
                processedEntryFunction = FALSE;
            }
            break;

        case LAP_FINISHED_STATE:
            if(!processedEntryFunction)
            {
                LapFinishedState_enterStopTimer2AndDisplayTimeAndStopDriveAndPlayBeep();
                processedEntryFunction = TRUE;
            }

            LapFinishedState_processPollingButtonA();

            if(LapFinishedState_checkTransitionTriggerButtonAPressed())
            {
                gCurrentState = READY_STATE;
                processedEntryFunction = FALSE;
            }
            break;

        case SEARCH_TRACK_STATE:
            if(!processedEntryFunction)
            {
                SearchTrackState_enterStartTimer1();
                processedEntryFunction = TRUE;
            }

            SearchTrackState_processFindTrackLine();

            if(SearchTrackState_checkTransitionTriggerTrackFound())
            {
                SearchTrackState_exitStopTimer1();
                gCurrentState = DRIVE_LAP_STATE;
                processedEntryFunction = FALSE;
            }
            else if(SearchTrackState_checkTransitionTriggerTimer1Exceeds5s())
            {
                SearchTrackState_exitStopTimer1();
                gCurrentState = ERROR_STATE;
                processedEntryFunction = FALSE;
                gErrorCode = ERRORHANDLER_RELEASETRACK_TIMER_START_FAIL;
            }
            break;

        case SEARCHING_STARTLINE_STATE:
            if(!processedEntryFunction)
            {
                SearchingStartLineState_enterStartTimer1AndStartDriving();
                processedEntryFunction = TRUE;
            }

            SearchingStartLineState_processSearchForStartline();

            if(SearchningStartLineState_checkTransitionTriggerStartlineFound())
            {
                SearchingStartLineState_exitStartTimer2AndPlayBeepIfStartlineFound();
                gCurrentState = DRIVE_LAP_STATE;
                processedEntryFunction = FALSE;
            }
            else if(SearchningStartLineState_checkTransitionTriggerTimer1Exceeds2s())
            {
                SearchingStartLineState_exitStartTimer2AndPlayBeepIfStartlineFound();
                gCurrentState = ERROR_STATE;
                processedEntryFunction = FALSE;
                gErrorCode = ERRORHANDLER_RELEASETRACK_TIMER_START_FAIL;
            }
            break;

        case INITIALIZATION_STATE:
            if(!processedEntryFunction)
            {
                InitializationState_enterDisplayNameAndStartTimer1();
                processedEntryFunction = TRUE;
            }

            if(InitializationState_checkTransitionTriggerTimer1Exceeds2s())
            {
                InitializationState_exitStopTimer1();
                gCurrentState = CALIBRATION_STATE;
                processedEntryFunction = FALSE;
            }
            break;

        case CALIBRATION_STATE:
            CalibrationState_processCalibrate();

            if(CalibrationState_checkTransitionTriggerCalibrationDone())
            {
                gCurrentState = READY_STATE;
            }
            break;

        case READY_STATE:
            ReadyState_processPollingButtons();

            if(ReadyState_checkTransitionTriggerButtonAPressed())
            {
                gCurrentState = PRE_DRIVE_STATE;
            }
            else if(ReadyState_checkTransitionTriggerButtonBPressed())
            {
                gCurrentState = PARAMETER_SET_STATE;
            }
            else if(ReadyState_checkTransitionTriggerButtonCPressed())
            {
                gCurrentState = CALIBRATION_STATE;
            }
            break;

        case PARAMETER_SET_STATE:
            if(!processedEntryFunction)
            {
                ParameterSetState_enterDisplayParameterSets();
                processedEntryFunction = TRUE;
            }

            ParameterSetState_processSetParameterSet();

            if(ParameterSetState_checkTransitionTriggerConfigDone())
            {
                ParameterSetState_exitDisplaySelectedParameterSetFor3s();
                gCurrentState = READY_STATE;
                processedEntryFunction = FALSE;
            }
            break;

        case PRE_DRIVE_STATE:
            if(!processedEntryFunction)
            {
                PreDriveState_enterStartTimer1AndWaitFor3s();
                processedEntryFunction = TRUE;
            }

            if(PreDriveState_checkTransitionTriggerTimer1Exceeds3s())
            {
                PreDriveState_exitStopTimer1();
                gCurrentState = SEARCHING_STARTLINE_STATE;
                processedEntryFunction = FALSE;
            }
            break;

    } 
}

/* INTERNAL FUNCTIONS *****************************************************************************/


