/***************************************************************************************************
  (c) NewTec GmbH 2024   -   www.newtec.de
***************************************************************************************************/
/**
 * @file       ParameterSetState.c
 *
 * Contains the functions and variables for the ParameterSetState.
 */
/**************************************************************************************************/

/* INCLUDES ***************************************************************************************/
#include "ParameterSetState.h"

/* CONSTANTS **************************************************************************************/
#define TEXT_SET1_SELECTED ("Set1 selected")
#define TEXT_SET2_SELECTED ("Set2 selected")
#define TEXT_SET3_SELECTED ("Set3 selected")

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

/* VARIABLES **************************************************************************************/
static Bool gButtonTriggered = FALSE;

/* EXTERNAL FUNCTIONS *****************************************************************************/

extern void ParameterSetState_enterDisplayParameterSets(void)
{
    Parameters_displayParameterSets();
}

extern void ParameterSetState_processSetParameterSet(void)
{
    if (BUTTON_STATE_TRIGGERED == Button_getState(BUTTON_ID_A))
    {
        Parameters_setParameterSet(INDEX_SET1);
        gButtonTriggered = TRUE;

        /* Display selected set for 3s */
        SoftTimer_start(GlobalTimers_getTimer(TIMER1), THREE_SECONDS);
        Display_clear();
        Display_write(TEXT_SET1_SELECTED, sizeof(TEXT_SET1_SELECTED));
    }

    if (BUTTON_STATE_TRIGGERED == Button_getState(BUTTON_ID_B))
    {
        Parameters_setParameterSet(INDEX_SET2);
        gButtonTriggered = TRUE;

        /* Display selected set for 3s */
        SoftTimer_start(GlobalTimers_getTimer(TIMER1), THREE_SECONDS);
        Display_clear();
        Display_write(TEXT_SET2_SELECTED, sizeof(TEXT_SET2_SELECTED));
    }

    if (BUTTON_STATE_TRIGGERED == Button_getState(BUTTON_ID_C))
    {
        Parameters_setParameterSet(INDEX_SET3);
        gButtonTriggered = TRUE;

        /* Display selected set for 3s */
        SoftTimer_start(GlobalTimers_getTimer(TIMER1), THREE_SECONDS);
        Display_clear();
        Display_write(TEXT_SET3_SELECTED, sizeof(TEXT_SET3_SELECTED));
    }
}

extern void ParameterSetState_exitDisplaySelectedParameterSetFor3s(void)
{
    SoftTimer_Stop(GlobalTimers_getTimer(TIMER1));
    Display_clear();
}

extern Bool ParameterSetState_checkTransitionTriggerConfigDone(void)
{
    if (SOFTTIMER_IS_EXPIRED(GlobalTimers_getTimer(TIMER1)))
    {
        gButtonTriggered = FALSE;
        return TRUE;
    }
    return FALSE;
}
/* INTERNAL FUNCTIONS *****************************************************************************/