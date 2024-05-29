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

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/

/* VARIABLES **************************************************************************************/
static Bool ButtonAPressed = FALSE;
static Bool ButtonBReleased = FALSE;
static Bool ButtonCPressed = FALSE;

/* EXTERNAL FUNCTIONS *****************************************************************************/

extern void ReadyState_processPollingButtons(void)
{ 
    if(BUTTON_STATE_TRIGGERED == Button_getState(BUTTON_ID_A))
    {
        ButtonAPressed = TRUE;
    }

    if(BUTTON_STATE_TRIGGERED == Button_getState(BUTTON_ID_B))
    {
        ButtonBReleased = TRUE;
    }

    if(BUTTON_STATE_TRIGGERED == Button_getState(BUTTON_ID_C))
    {
        ButtonCPressed = TRUE;
    }
}

extern Bool ReadyState_checkTransitionTriggerButtonAPressed(void)
{
    if(TRUE == ButtonAPressed)
    {
        ButtonAPressed = FALSE;
        return TRUE;
    }
    return FALSE;
}

extern Bool ReadyState_checkTransitionTriggerButtonBPressed(void)
{
    if(TRUE == ButtonBReleased)
    {
        ButtonBReleased = FALSE;
        return TRUE;
    }
    return FALSE;
}

extern Bool ReadyState_checkTransitionTriggerButtonCPressed(void)
{
    if(TRUE == ButtonCPressed)
    {
        ButtonCPressed = FALSE;
        return TRUE;
    }
    return FALSE;
}
/* INTERNAL FUNCTIONS *****************************************************************************/