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
        SoftTimer_start(pTimer1, THREE_SECONDS);
        Display_clear();
        Display_write("Set1 selected", sizeof("Set1 selected"));
    }

    if (BUTTON_STATE_TRIGGERED == Button_getState(BUTTON_ID_B))
    {
        Parameters_setParameterSet(INDEX_SET2);
        gButtonTriggered = TRUE;
        SoftTimer_start(pTimer1, THREE_SECONDS);
        Display_clear();
        Display_write("Set2 selected", sizeof("Set2 selected"));
    }

    if (BUTTON_STATE_TRIGGERED == Button_getState(BUTTON_ID_C))
    {
        Parameters_setParameterSet(INDEX_SET3);
        gButtonTriggered = TRUE;
        SoftTimer_start(pTimer1, THREE_SECONDS);
        Display_clear();
        Display_write("Set3 selected", sizeof("Set3 selected"));
    }
}

extern void ParameterSetState_exitDisplaySelectedParameterSetFor3s(void)
{
    Display_clear();
}

extern Bool ParameterSetState_checkTransitionTriggerConfigDone(void)
{
    if (SOFTTIMER_IS_EXPIRED(pTimer1))
    {
        gButtonTriggered = FALSE;
        return TRUE;
    }
    return FALSE;
}
/* INTERNAL FUNCTIONS *****************************************************************************/