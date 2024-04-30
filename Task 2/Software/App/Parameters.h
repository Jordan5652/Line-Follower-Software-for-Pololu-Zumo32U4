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
/** @fn void Parameters_setParameterSet(void)
 * @brief sets the selected ParameterSet
 * @return void
*/
void Parameters_setParameterSet(void);

/** @fn void Parameters_getParameterSet(void)
 * @brief gets the current ParameterSet
 * @return ParameterSet current ParameterSet
*/
ParameterSet Parameters_getParameterSet(void);

/** @fn void Parameters_displayParameterSet(void)
 * @brief displays the ParameterSet on the OLED-Display
 * @return void
*/
void Parameters_displayParameterSets(void);

#endif /* PARAMETERS_H */