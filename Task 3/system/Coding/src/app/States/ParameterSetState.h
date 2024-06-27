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
#include "GlobalTimers.h"

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/* PROTOTYPES *************************************************************************************/
/**
 * @brief display all the available parameter-sets that can be used
*/
extern void ParameterSetState_enterDisplayParameterSets(void);

/**
 * @brief let the user choose a parameter-set
*/
extern void ParameterSetState_processSetParameterSet(void);

/**
 * @brief display the selected parameter set on the OLED
*/
extern void ParameterSetState_exitDisplaySelectedParameterSetFor3s(void);

/**
 * @brief check if configuration of parameters is done
 * @return Bool: return true if configuration is done
*/
extern Bool ParameterSetState_checkTransitionTriggerConfigDone(void);

#endif /* PARAMETER_SET_STATE_H */