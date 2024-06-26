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
#include "Types.h"

#include "Display.h"

/* CONSTANTS **************************************************************************************/
#define INDEX_SET1 (0U)
#define INDEX_SET2 (1U)
#define INDEX_SET3 (2U)

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

/** Pointer to the selected parameter set */
//extern ParameterSet* pParameters;

/* PROTOTYPES *************************************************************************************/
/**
 * @brief returns to pointer to the currently selected ParameterSet
 * @return ParameterSet*: pointer to the currently selected ParameterSet 
 */
extern ParameterSet* Parameters_getParameterSet(void);


/**
 * @brief sets the selected ParameterSet
 * @param index the index used to set the parameterset
*/
extern void Parameters_setParameterSet(UInt8 index);

/**
 * @brief displays the ParameterSet on the OLED-Display
*/
extern void Parameters_displayParameterSets(void);

/**
 * @brief initializes the ParameterSets
*/
extern void Parameters_initParameterSets(void);

#endif /* PARAMETERS_H */