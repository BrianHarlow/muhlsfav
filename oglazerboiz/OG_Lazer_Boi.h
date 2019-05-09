#ifndef OG_LAZER_BOI_H_
#define OG_LAZER_BOI_H_

#warning "edit the task schedule and thief trip part to include the embedded software link to the task file"
/**
 * @defgroup OG_Lazer_Boi_module Laser Trap Module Module
 *
 * Created on: May 6, 2019
 *    @author DJ Stahlberger
 *
 * @brief This module implements a laser trap for a thief simulation game.
 *
 * The following module utilizes the Task Schedule and Task Remove functions
 *  from <a href="https://github.com/muhlbaier/embedded-software/blob/master/src/task.c">Task.c</a>
 * in order to periodically check whether the trap has been triggered.
 * The Thief Trip function is also used from
 * <a href="https://github.com/muhlbaier/embedded-software/blob/master/src/games/thief.c">Thief.c</a>
 * to notifiy the Master node whenever the trap is tripped.
 *
 * In order to use this module, Laser_Init has to be called first. Doing this will
 * schedule both Check_Object and Check_Trip to be run at a period of 10ms. These
 * functions will run until Laser_Disarm is called. The difficulty function is
 * utilized by the Thief_Init function to incorporate a score multiplier.
 *
 *
 * @{
 */

/** @brief initializes the laser module for use
 *
 * Initializes the pins for the laser receivers and emitters as well as calls the
 * Task_Schedule function for Check_Object and Check_Trip so they will be polled
 * for a trip.
 *
 */
void Laser_Init(void);


/** @brief disarms the laser module
 *
 * Sets all the power pins for the laser emitters to be 0 so they will no
 * longer be on
 * Also calls the Task_Remove functions on Check_Trip and Check_Object so
 * no trips or false disarms will be called.
 *
 */
void Laser_Disarm(void);

/** @brief checks to see if the laser being obstructed by the object is reaching
 * the emitter
 *
 * Checks to see if the sensor value from the emitter is receiving a signal. If it is,
 * it calls the Disarm function to turn off the trap... (CONGRATS YOU WIN).
 *
 */
void Check_Object(void);

/** @brief checks to see if any of the lasers , excluding the object laser,
 *  were tripped
 *
 * Checks the 4 lasers in front of the object for trips. First it checks to see
 * if the laser is being powered, to see if it was already tripped. It then
 * checks the signal from the emitter to see if there was a trip. In the event
 * that this happens, the power pin for that laser is then turned off and the
 * Thief_Trip function is called to send a score to the MASTER node. This score
 * is based off of the difficulty value from the Difficulty function.
 *
 */
void Check_Trip(void);

/** @brief receives the difficulty from the master node for the trap
 *
 * Utilizes a static variable to hold the difficulty data from the master.
 * This value gets utilized in Check_Trip. This function also uses the LogMsg
 * function to display what the current difficulty is.
 *
 * @param data difficulty being passed from the master node
 *
 */


void Difficulty(uint8_t data);


#endif /* OG_LAZER_BOI_H_ */
