/***************************************************************************************************
  (c) NewTec GmbH 2024   -   www.newtec.de
***************************************************************************************************/
/**
 * @file       ReadyState.c
 *
 * Contains the functions and variables for the ReadyState.
 */
/**************************************************************************************************/

/* INCLUDES ***************************************************************************************/
#include "ReadyState.h"

/* CONSTANTS **************************************************************************************/
#define TEXT_READYSTATE ("ReadyState")

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

/* VARIABLES **************************************************************************************/

/* Button trigger state of Button A, B, C */
static Bool gButtonATriggered = FALSE;
static Bool gButtonBTriggered = FALSE;
static Bool gButtonCTriggered = FALSE;

/* EXTERNAL FUNCTIONS *****************************************************************************/
extern void ReadyState_enterDisplayState(void)
{
    Display_clear();
    Display_gotoxy(0,7);
    Display_write(TEXT_READYSTATE, sizeof(TEXT_READYSTATE));
}

extern void ReadyState_processPollingButtons(void)
{ 
    /* Checks if any button is triggered */
    if (BUTTON_STATE_TRIGGERED == Button_getState(BUTTON_ID_A))
    {
        gButtonATriggered = TRUE;
    }

    if (BUTTON_STATE_TRIGGERED == Button_getState(BUTTON_ID_B))
    {
        gButtonBTriggered = TRUE;
    }

    if (BUTTON_STATE_TRIGGERED == Button_getState(BUTTON_ID_C))
    {
        gButtonCTriggered = TRUE;
    }
}

extern Bool ReadyState_checkTransitionTriggerButtonAPressed(void)
{
    if (TRUE == gButtonATriggered)
    {
        gButtonATriggered = FALSE;
        return TRUE;
    }
    return FALSE;
}

extern Bool ReadyState_checkTransitionTriggerButtonBPressed(void)
{
    if (TRUE == gButtonBTriggered)
    {
        gButtonBTriggered = FALSE;
        return TRUE;
    }
    return FALSE;
}

extern Bool ReadyState_checkTransitionTriggerButtonCPressed(void)
{
    if (TRUE == gButtonCTriggered)
    {
        gButtonCTriggered = FALSE;
        return TRUE;
    }
    return FALSE;
}
/* INTERNAL FUNCTIONS *****************************************************************************/