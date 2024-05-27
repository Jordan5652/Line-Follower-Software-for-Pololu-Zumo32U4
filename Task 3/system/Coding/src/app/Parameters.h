/***************************************************************************************************
  (c) NewTec GmbH 2024   -   www.newtec.de
***************************************************************************************************/
/**
 * @file       Parameters.h
 *
 * Header of Parameters.c.
 */
/**************************************************************************************************/
#ifndef PARAMETERS_H
#define PARAMETERS_H

/* INCLUDES ***************************************************************************************/

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/
/** @struct ParameterSet
 * @brief struct to represent a ParameterSet
*/
typedef struct
{

}ParameterSet;

/* PROTOTYPES *************************************************************************************/
/** 
 * @brief sets the selected ParameterSet
 * 
*/
void Parameters_setParameterSet(void);

/** 
 * @brief gets the current ParameterSet
 * 
*/
ParameterSet Parameters_getParameterSet(void);

/** 
 * @brief displays the ParameterSet on the OLED-Display
 * 
*/
void Parameters_displayParameterSets(void);

#endif /* PARAMETERS_H */