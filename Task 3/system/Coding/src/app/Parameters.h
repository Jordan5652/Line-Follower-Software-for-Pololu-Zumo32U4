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
    Float32 kp;
    Float32 kd;
    Float32 ki;
    Int16 motorspeed;
}ParameterSet;

/* PROTOTYPES *************************************************************************************/
/** 
 * @brief sets the selected ParameterSet
 * 
*/
extern void Parameters_setParameterSet(UInt8 index);

/** 
 * @brief gets the current ParameterSet
 * 
*/
ParameterSet Parameters_getParameterSet(void);

/** 
 * @brief displays the ParameterSet on the OLED-Display
 * 
*/
extern void Parameters_displayParameterSets(void);

extern void Parameters_initParameterSets(void);

#endif /* PARAMETERS_H */