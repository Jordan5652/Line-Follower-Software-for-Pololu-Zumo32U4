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
    }

    if (BUTTON_STATE_TRIGGERED == Button_getState(BUTTON_ID_B))
    {
        Parameters_setParameterSet(INDEX_SET2);
        gButtonTriggered = TRUE;
    }

    if (BUTTON_STATE_TRIGGERED == Button_getState(BUTTON_ID_C))
    {
        Parameters_setParameterSet(INDEX_SET3);
        gButtonTriggered = TRUE;
    }
}

extern void ParameterSetState_exitDisplaySelectedParameterSetFor3s(void)
{
    //TBD
}

extern Bool ParameterSetState_checkTransitionTriggerConfigDone(void)
{
    if (TRUE == gButtonTriggered)
    {
        gButtonTriggered = FALSE;
        return TRUE;
    }
    return FALSE;
}
/* INTERNAL FUNCTIONS *****************************************************************************/