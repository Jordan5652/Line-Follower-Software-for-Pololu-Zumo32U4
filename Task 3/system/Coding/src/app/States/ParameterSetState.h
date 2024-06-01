/***************************************************************************************************
  (c) NewTec GmbH 2024   -   www.newtec.de
***************************************************************************************************/
/**
 * @file       ParameterSetState.h
 *
 * Header of ParameterSetState.c.
 */
/**************************************************************************************************/
#ifndef PARAMETER_SET_STATE_H
#define PARAMETER_SET_STATE_H

/* INCLUDES ***************************************************************************************/
#include "Types.h"

#include "Button.h"
#include "Parameters.h"
#include "Display.h"
/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/
/** 
 * @brief displays all the available parameter-sets that can be used
*/
extern void ParameterSetState_enterDisplayParameterSets(void);

/** 
 * @brief lets the user choose a parameter-set
*/
extern void ParameterSetState_processSetParameterSet(void);

/** 
 * @brief displays the selected parameter set on the OLED
*/
extern void ParameterSetState_exitDisplaySelectedParameterSetFor3s(void);

/** 
 * @brief checks if configuration of parameters is done 
 * @return Bool: return true if configuration is done
*/
extern Bool ParameterSetState_checkTransitionTriggerConfigDone(void);

#endif /* PARAMETER_SET_STATE_H */