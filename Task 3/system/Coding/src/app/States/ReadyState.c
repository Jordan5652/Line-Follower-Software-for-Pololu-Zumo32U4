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
    if(BUTTON_STATE_PRESSED == Button_getState(BUTTON_ID_A))
    {
        ButtonAPressed = TRUE;
    }

    if(BUTTON_STATE_RELEASED == Button_getState(BUTTON_ID_B))
    {
        ButtonAPressed = TRUE;
    }

    if(BUTTON_STATE_PRESSED == Button_getState(BUTTON_ID_C))
    {
        ButtonAPressed = TRUE;
    }
}

extern Bool ReadyState_checkTransitionTriggerButtonAPressed(void)
{
    if(ButtonAPressed)
    {
      return TRUE;
    }
}

extern Bool ReadyState_checkTransitionTriggerButtonBPressed(void)
{
    if(ButtonBReleased)
    {
      return TRUE;
    }
}

extern Bool ReadyState_checkTransitionTriggerButtonCPressed(void)
{
    if(ButtonCPressed)
    {
      return TRUE;
    }
}
/* INTERNAL FUNCTIONS *****************************************************************************/