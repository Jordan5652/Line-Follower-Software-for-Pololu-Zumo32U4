/***************************************************************************************************
  (c) NewTec GmbH 2024   -   www.newtec.de
***************************************************************************************************/
/**
 * @file       StateDataTypes.h
 *
 * Header containing all the custom datatypes regarding the statemachine.
 */
/**************************************************************************************************/
#ifndef STATE_DATA_TYPES_H
#define STATE_DATA_TYPES_H

/* INCLUDES ***************************************************************************************/

/* CONSTANTS **************************************************************************************/

/* MACROS *****************************************************************************************/

/* TYPES ******************************************************************************************/

/** @enum States
 * @brief representation of all states 
*/
typedef enum
{
    initializationState = 0,
    ReadyState = 1,
    CalibrationState = 2,
    ParameterSetState = 3,
    SearchingStartLineState = 4,
    DriveLapState = 5,
    LapFinishedState = 6,
    SearchTrackState = 7,
    ErrorState = 8,

}States;

/** @struct StateFunctions
 * @brief struct holds the stateFunctions 
*/
typedef struct
{
    void (*pointerEntry) (void);
    void (*pointerProcess) (void);
    void (*pointerExit) (void);
    (States*) (*pointerGetNextState) (void); 
  
}StateFunctions;


/* PROTOTYPES *************************************************************************************/

#endif /* STATE_DATA_TYPES_H */