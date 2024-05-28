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
static States gCurrentState;

/**
 * @brief store the status of transitions
*/
static Bool gTransitionStatus[3u] = FALSE;

/* EXTERNAL FUNCTIONS *****************************************************************************/
void StateHandler_stateHandler(void)
{
    switch(gCurrentState)
    {
        case DriveLapState:

            gTransitionStatus[0] = DriveLapState_checkTranstionTriggerStartlineFound();
            gTransitionStatus[1] = DriveLapState_checkTranstionTriggerTrackNotFound();
            gTransitionStatus[2] = DriveLapState_checkTranstionTriggerTimer2Exceeds20s();
            while(FALSE == gTransitionStatus[0] && FALSE == gTransitionStatus[1] && FALSE == gTransitionStatus[2])
            {
                DriveLapState_processDriveOnTrackLine();
                gTransitionStatus[0] = DriveLapState_checkTranstionTriggerStartlineFound();
                gTransitionStatus[1] = DriveLapState_checkTranstionTriggerTrackNotFound();
                gTransitionStatus[2] = DriveLapState_checkTranstionTriggerTimer2Exceeds20s();
            }

            if(gTransitionStatus[0])
            {
                gCurrentState = LapFinishedState;
            }
            else if(gTransitionStatus[1])
            {
                gCurrentState = SearchTrackState;
            }
            else if(gTransitionStatus[2])
            {
                gCurrentState = ErrorState;
            }

            break;

        case ErrorState:

            ErrorState_enterStopDriveAndPlayAlarmAndDisplayError();
            gTransitionStatus[0] = ErrorState_checkTransitionTriggerButtonAPressed();
            while(FALSE == gTransitionStatus[0])
            {
                ErrorState_processPollingButtonA();
                gTransitionStatus[0] = ErrorState_checkTransitionTriggerButtonAPressed();
            }
            gCurrentState = ReadyState;

            break;

        case LapFinishedState:
    
            LapFinishedState_enterStopTimer2AndDisplayTimeAndStopDriveAndPlayBeep();
            gTransitionStatus[0] = LapFinishedState_checkTransitionTriggerButtonAPressed();
            while(FALSE == gTransitionStatus[0])
            {
                LapFinishedState_processPollingButtonA();
                gTransitionStatus[0] = LapFinishedState_checkTransitionTriggerButtonAPressed();
            }
            if(gTransitionStatus[0])
            {
                gCurrentState = ReadyState;
            }

            break;

        case SearchTrackState:

            SearchTrackState_enterStartTimer1();
            gTransitionStatus[0] = SearchTrackState_checkTransitionTriggerTrackFound();
            gTransitionStatus[1] = SearchTrackState_checkTransitionTriggerTimer1Exceeds5s();
            while(FALSE == gTransitionStatus[0] && FALSE == gTransitionStatus[1])
            {
                SearchTrackState_processFindTrackLine();
                gTransitionStatus[0] = SearchTrackState_checkTransitionTriggerTrackFound();
                gTransitionStatus[1] = SearchTrackState_checkTransitionTriggerTimer1Exceeds5s();
            }
            if(gTransitionStatus[0])
            {
                SearchTrackState_exitStopTimer1();
                gCurrentState = DriveLapState;
            }
            else if(gTransitionStatus[1])
            {
                SearchTrackState_exitStopTimer1();
                gCurrentState = ErrorState;
            }

            break;

        case SearchingStartLineState:

            SearchingStartLineState_enterStartTimer1AndStartDriving();
            gTransitionStatus[0] = SearchningStartLineState_checkTransitionTriggerStartlineFound();
            gTransitionStatus[1] = SearchningStartLineState_checkTransitionTriggerTimer1Exceeds8s();
            while(FALSE == gTransitionStatus[0] && FALSE == gTransitionStatus[1])
            {
                SearchingStartLineState_exitStartTimer2AndPlayBeepIfStartlineFound();
                gTransitionStatus[0] = SearchningStartLineState_checkTransitionTriggerStartlineFound();
                gTransitionStatus[1] = SearchningStartLineState_checkTransitionTriggerTimer1Exceeds8s();
            }
            if(gTransitionStatus[0])
            {
                SearchingStartLineState_exitStartTimer2AndPlayBeepIfStartlineFound();
                gCurrentState = DriveLapState;
            }
            else if(gTransitionStatus[1])
            {
                SearchingStartLineState_exitStartTimer2AndPlayBeepIfStartlineFound();
                gCurrentState = ErrorState;
            }

            break;

        case InitializationState:

            gTransitionStatus[0] = InitializationState_checkTransitionTriggerTimer1Exceeds2s();
            while(FALSE == gTransitionStatus[0])
            {
                InitializationState_enterDisplayNameAndStartTimer1();
                gTransitionStatus[0] = InitializationState_checkTransitionTriggerTimer1Exceeds2s();
            }
            if(gTransitionStatus[0])
            {
                InitializationState_exitStopTimer1();
                gCurrentState = CalibrationState;
            }

            break;

        case CalibrationState:

            gTransitionStatus[0] = CalibrationState_checkTransitionTriggerCalibrationDone();
            while(FALSE == gTransitionStatus[0])
            {
                CalibrationState_processCalibrate();
                gTransitionStatus[0] = CalibrationState_checkTransitionTriggerCalibrationDone();
            }
            if(gTransitionStatus[0])
            {
                gCurrentState = ReadyState;
            }

            break;

        case ReadyState:

            gTransitionStatus[0] = ReadyState_checkTransitionTriggerButtonAPressed();
            gTransitionStatus[1] = ReadyState_checkTransitionTriggerButtonBPressed();
            gTransitionStatus[2] = ReadyState_checkTransitionTriggerButtonCPressed();
            while(FALSE == gTransitionStatus[0] && FALSE == gTransitionStatus[1] && FALSE == gTransitionStatus[2])
            {
                ReadyState_processPollingButtons();
                gTransitionStatus[0] = ReadyState_checkTransitionTriggerButtonAPressed();
                gTransitionStatus[1] = ReadyState_checkTransitionTriggerButtonBPressed();
                gTransitionStatus[2] = ReadyState_checkTransitionTriggerButtonCPressed();
            }
            if(gTransitionStatus[0])
            {
                gCurrentState = PreDriveState;
            }
            else if(gTransitionStatus[1])
            {
                gCurrentState = ParameterSetState;
            }
            else if(gTransitionStatus[2])
            {
                gCurrentState = CalibrationState;
            }

            break;

        case ParameterSetState:

            ParameterSetState_enterDisplayParameterSets();
            gTransitionStatus[0] = ParameterSetState_checkTransitionTriggerConfigDone();
            while(FALSE == gTransitionStatus[0])
            {
                ParameterSetState_processSetParameterSet();
                gTransitionStatus[0] = ParameterSetState_checkTransitionTriggerConfigDone();
            }
            if(gTransitionStatus[0])
            {
                ParameterSetState_exitDisplaySelectedParameterSetFor3s();
                gCurrentState = ReadyState;
            }

            break;

        case PreDriveState:

            PreDriveState_enterStartTimer1AndWaitFor3s();
            gTransitionStatus[0] = PreDriveState_checkTransitionTriggerTimer1Exceeds3s();
            while(FALSE == gTransitionStatus[0])
            {
                // do nothing
                gTransitionStatus[0] = PreDriveState_checkTransitionTriggerTimer1Exceeds3s();
            }
            if(gTransitionStatus[0])
            {
                PreDriveState_exitStopTimer1();
                gCurrentState = SearchingStartLineState;
            }

            break;
    } 
}

/* INTERNAL FUNCTIONS *****************************************************************************/


