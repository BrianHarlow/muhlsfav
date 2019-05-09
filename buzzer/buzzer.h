#ifndef _BUZZER_H_
#define _BUZZER_H_

#include <stdint.h>

/**
 * @defgroup buzzer_module Buzzer Module
 * 
 * Created on: Mar 26, 2019
 *
 * @authors Nikola Kosaric
 * @authors Nate Hoffman
 * @authors Brian Harlow
 * @authors DJ Stahlberger 
 *
 * @brief This module implements control for a buzzer that sounds at different
 * frequencies for different lengths of time.
 *
 * The following module utilizes the task manager and timing module
 * in order to inact a buzzer to produce a sound at a determined frequency.
 * The timing module is used to control the frequency of the sound produced
 * and the task module is used to control the length of time the buzzer will 
 * sound.
 *
 * In order to utilize this module, first, the Buzzer_Init() must be called.
 * Then, the Buzzer_Sound() function must be called in order to determine the
 * frequency at which the buzzer will sound and the length of time the buzzer
 * will sound in milliseconds. The channel used for the buzzer will be determined in the 
 * hardware abstraction layer. At this time, multiple buzzers cannot be attached
 * at once, nor is the pin reconfigurable.
 *
 * Note that this uses the <a href="https://muhlbaier.github.io/embedded-software/group__task.html">Task Module from embedded-software</a>
 * to schedule a task to shut down the buzzer after the timeout period has elapsed.
 * HAL implementations should be careful to support the full range of frequencies
 * that can be requested by the user of this module (from 1 Hz to 65.535 kHz). HAL
 * implementations may need to adjust prescaling into timers or entirely switch clock
 * sources for the timer depending on how low or high the frequency is. Care should
 * be taken that frequencies are accurate at various frequencies, especially near the
 * point(s) where the clock gets switched out.
 * 
 * @{
 */

/** @brief Initializes the buzzer module
 * 
 * Initializes the task manager to allow the
 * module to be used within the Buzzer_Sound() function.
 * Relies on the HAL to configure the timer for operation.
 * Note that a sound is not played when started up.
 *
 */

void Buzzer_Init(void);

/** @brief Plays a sound on the buzzer
 *
 * Call to play a sound on the buzzer at a specific `frequency`. This frequency is
 * a positive integer in Hertz. The sound is then played for the `timeout` number of
 * milliseconds. After the timeout elapses, the buzzer is then stopped. If this method is
 * called while a sound is already playing, the first sound stops and then it plays the new
 * sound.
 * 
 * @param frequency Frequency of the buzzer. The maximum value can be 65535, or 65.535 kHz
 * @param timeout Length at which the buzzer is active in milliseconds
 */

void Buzzer_Sound(uint16_t frequency, uint16_t timeout);

/** @brief Hardware abstaction layer buzzer initialization
 *
 * Must be implemented for each MCU in hal_buzzer.c and configure 
 * the pin which will utilize the buzzer. This can include configuring any timers used
 * to run the buzzer on command.
 */
 
void hal_Buzzer_Init(void);
 
 /** @brief Hardware abstraction layer to start buzzer at a specific frequency
 * 
 * Given a `frequency` in Hertz, oscillate the output pin. The output continuously run
 * without stopping until a separate function is called.
 *
 * @param frequency Frequency of the buzzer. The maximum value can be 65535, or 65.535 kHz
 *
 */
 
void hal_Start_Buzzer(uint16_t frequency);

 /** @brief Hardware abstraction layer to stop buzzer
 * 
 * The buzzer should stop oscillating the output pin when this function is called.
 * This is a stop of the buzzer, but does not free the timer(s) used to play the sound
 * for use in other tasks. The hal_Start_Buzzer() function can be called again and the buzzer
 * will play the new sound.
 */
 
void hal_Stop_Buzzer(void);
 
 /** @} */

#endif // _BUZZER_H_