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
    Display_gotoxy(0, 0);
    Display_write("A: NAME SET 1", sizeof("A: NAME SET 1"));
    Display_gotoxy(0, 1);
    Display_write("B: NAME SET 2", sizeof("B: NAME SET 2"));
    Display_gotoxy(0, 2);
    Display_write("C: NAME SET 3", sizeof("C: NAME SET 3"));
}

extern void ParameterSetState_processSetParameterSet(void)
{
    if(BUTTON_STATE_TRIGGERED == Button_getState(BUTTON_ID_A))
    {
        setParameterSet(0u);
        gButtonTriggered = TRUE;
    }

    if(BUTTON_STATE_TRIGGERED == Button_getState(BUTTON_ID_B))
    {
        setParameterSet(1u);
        gButtonTriggered = TRUE;
    }

    if(BUTTON_STATE_TRIGGERED == Button_getState(BUTTON_ID_C))
    {
        setParameterSet(2u);
        gButtonTriggered = TRUE;
    }
}

extern void ParameterSetState_exitDisplaySelectedParameterSetFor3s(void)
{


}

extern Bool ParameterSetState_checkTransitionTriggerConfigDone(void)
{
    if(TRUE == gButtonTriggered)
    {
        gButtonTriggered = FALSE;
        return TRUE;
    }
    return FALSE;
}
/* INTERNAL FUNCTIONS *****************************************************************************/