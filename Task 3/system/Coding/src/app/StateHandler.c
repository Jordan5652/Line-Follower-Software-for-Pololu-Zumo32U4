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
static States gCurrentState;

/* EXTERNAL FUNCTIONS *****************************************************************************/

void StateHandler_stateHandler(void)
{
    switch(gCurrentState)
    {
        case DriveLapState:
            DriveLapState_processDriveOnTrackLine();

            if(DriveLapState_checkTranstionTriggerStartlineFound())
            {
                gCurrentState = LapFinishedState;
            }
            else if(DriveLapState_checkTranstionTriggerTrackNotFound())
            {
                gCurrentState = SearchTrackState;
            }
            else if(DriveLapState_checkTranstionTriggerTimer2Exceeds20s())
            {
                gCurrentState = ErrorState;
            }
            break;

        case ErrorState:
            if(!processedEntryFunction)
            {
                ErrorState_enterStopDriveAndPlayAlarmAndDisplayError();
                processedEntryFunction = TRUE;
            }

            ErrorState_processPollingButtonA();

            if(ErrorState_checkTransitionTriggerButtonAPressed())
            {
                gCurrentState = ReadyState;
                processedEntryFunction = FALSE;
            }
            break;

        case LapFinishedState:
            if(!processedEntryFunction)
            {
                LapFinishedState_enterStopTimer2AndDisplayTimeAndStopDriveAndPlayBeep();
                processedEntryFunction = TRUE;
            }

            LapFinishedState_processPollingButtonA();

            if(LapFinishedState_checkTransitionTriggerButtonAPressed())
            {
                gCurrentState = ReadyState;
                processedEntryFunction = FALSE;
            }
            break;

        case SearchTrackState:
            if(!processedEntryFunction)
            {
                SearchTrackState_enterStartTimer1();
                processedEntryFunction = TRUE;
            }

            SearchTrackState_processFindTrackLine();

            if(SearchTrackState_checkTransitionTriggerTrackFound())
            {
                SearchTrackState_exitStopTimer1();
                gCurrentState = DriveLapState;
                processedEntryFunction = FALSE;
            }
            else if(SearchTrackState_checkTransitionTriggerTimer1Exceeds5s())
            {
                SearchTrackState_exitStopTimer1();
                gCurrentState = ErrorState;
                processedEntryFunction = FALSE;
            }
            break;

        case SearchingStartLineState:
            if(!processedEntryFunction)
            {
                SearchingStartLineState_enterStartTimer1AndStartDriving();
                processedEntryFunction = TRUE;
            }

            SearchingStartLineState_exitStartTimer2AndPlayBeepIfStartlineFound();

            if(SearchningStartLineState_checkTransitionTriggerStartlineFound())
            {
                SearchingStartLineState_exitStartTimer2AndPlayBeepIfStartlineFound();
                gCurrentState = DriveLapState;
                processedEntryFunction = FALSE;
            }
            else if(SearchningStartLineState_checkTransitionTriggerTimer1Exceeds8s())
            {
                SearchingStartLineState_exitStartTimer2AndPlayBeepIfStartlineFound();
                gCurrentState = ErrorState;
                processedEntryFunction = FALSE;
            }
            break;

        case InitializationState:
            if(!processedEntryFunction)
            {
                InitializationState_enterDisplayNameAndStartTimer1();
                processedEntryFunction = TRUE;
            }

            if(InitializationState_checkTransitionTriggerTimer1Exceeds2s())
            {
                InitializationState_exitStopTimer1();
                gCurrentState = CalibrationState;
                processedEntryFunction = FALSE;
            }
            break;

        case CalibrationState:
            CalibrationState_processCalibrate();

            if(CalibrationState_checkTransitionTriggerCalibrationDone())
            {
                gCurrentState = ReadyState;
            }
            break;

        case ReadyState:
            ReadyState_processPollingButtons();

            if(ReadyState_checkTransitionTriggerButtonAPressed())
            {
                gCurrentState = PreDriveState;
            }
            else if(ReadyState_checkTransitionTriggerButtonBPressed())
            {
                gCurrentState = ParameterSetState;
            }
            else if(ReadyState_checkTransitionTriggerButtonCPressed())
            {
                gCurrentState = CalibrationState;
            }
            break;

        case ParameterSetState:
            if(!processedEntryFunction)
            {
                ParameterSetState_enterDisplayParameterSets();
                processedEntryFunction = TRUE;
            }

            ParameterSetState_processSetParameterSet();

            if(ParameterSetState_checkTransitionTriggerConfigDone())
            {
                ParameterSetState_exitDisplaySelectedParameterSetFor3s();
                gCurrentState = ReadyState;
                processedEntryFunction = FALSE;
            }
            break;

        case PreDriveState:
            if(!processedEntryFunction)
            {
                PreDriveState_enterStartTimer1AndWaitFor3s();
                processedEntryFunction = TRUE;
            }

            if(PreDriveState_checkTransitionTriggerTimer1Exceeds3s())
            {
                PreDriveState_exitStopTimer1();
                gCurrentState = SearchingStartLineState;
                processedEntryFunction = FALSE;
            }
            break;

    } 
}

/* INTERNAL FUNCTIONS *****************************************************************************/


