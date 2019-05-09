#ifndef THIEF_PIEZO_H_
#define THIEF_PIEZO_H_

/**
 * @defgroup thief_piezo Thief Piezo Module
 *
 *  Created on: May 7, 2019
 *      @authors Brian Harlow
 *      @authors Nate Hoffman
 * 
 * @brief This module implements a piezo vibration sensor trap for a thief simulation game.
 *
 * This module is designed as a trap for a thief simulator game which
 * will act as a landmine trap. The piezo sensor is a transducer that
 * produces a signal when it senses vibrations. The ADC module is used 
 * to read the analog input from the piezo and determine how strong the
 * vibrations are by using a callback to the Thief_CheckADC() function.
 * The Thief module of Professor Michael Muhlbaier's Embedded-Software 
 * git which can be viewed <a href="https://github.com/muhlbaier/embedded-software/blob/master/src/games/thief.c">here</a>
 * is used to run the Thief_Piezo_Arm(), Thief_Piezo_Disarm(), and
 * Thief_Piezo_Difficulty() functions.
 *
 * In order to use this module Thief_Piezo_Init() must be called in the main.
 * 
 * @{
 */
 
 /** @brief Initializes the Thief_Piezo module for use
 * 
 * Initializes the Thief_Piezo module by initializing the Piezo as a subsystem
 * using the Subsystem module from the Embedded-Software git which can be viewed
 * <a href="https://github.com/muhlbaier/embedded-software/blob/master/src/subsystem.c">here</a>.
 * The system initializes the ADC and begins reading the piezo's output through 
 * the ADC at a period of 1 millisecond and also sets a local variable to show 
 * that the system has been initialized. Lastly, the system sends a trip message
 * so the systems communications are confirmed and the nRF modules of other traps
 * can see that the Thief_Piezo is connected.
 * 
 * Calling this function will initialize the thief module on its own, thus it does
 * not need to be initialized in the main.
 * 
 * @param CE Chip Enable Callback - allows control of the chip enable pin, the connection to the nRF.
 * @param CSN Chip Select Not Callback - enables or disables SPI communication with the nRF.
 */

void Thief_Piezo_Init(void(*CE)(uint8_t), void(*CSN)(uint8_t));

 /** @} */

#endif /* THIEF_PIEZO_H_ */
