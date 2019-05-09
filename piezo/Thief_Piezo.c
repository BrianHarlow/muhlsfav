/**
 * @addtogroup thief_piezo
 *
 *  Created on: May 7, 2019
 *      @authors Brian Harlow
 * 		@authors Nate Hoffman
 * @{
 * 
 */

#include "thief.h"
#include "adc.h"
#include "subsystem.h"
#include "timing.h"

static uint8_t initialized = 0;
static uint8_t sys_id;
static uint8_t armed = 0;
static uint8_t difficulty = 1;
static uint32_t samplingStartTime = 0;


/** @brief Arms the piezo trap. 
 * 
 * Changes local variable to show the program that the trap has been armed.
 * If this variable is not changed, the trap will not be able to send trip
 * messages to the master. The master must arm the trap, it cannot do it on its own.
 * 
 */
void Thief_Piezo_Arm();

/** @brief Disarms the piezo trap. 
 * 
 * Changes local variable to show the program that the trap has been disarmed.
 * Disarming the trap restricts the piezo from sending trip messages to the master.
 * The master must disarm the trap, it cannot do it on its own.
 * 
 */
 
void Thief_Piezo_Disarm();

/** @brief Changes the difficulty the piezo trap. 
 * 
 * Changes local variable that handles the difficulty of the trap. The higher
 * the difficulty, the higher the penalty for tripping the trap.
 *
 * @param diff Difficulty - A value representing the difficulty of the game from 0 to 10, 10 being most difficult. 
 */
 
void Thief_Piezo_Difficulty(uint8_t diff);

/** @brief Reads a value from the piezo into the ADC to see if the trap has been tripped. 
 * 
 * If the system is armed and initialized, this function will check the value of the ADC to
 * see if the trap has been tripped. If it has been tripped, it will send a trip message to
 * the master with a time to add to the score.
 * 
 * @param value ADC Read Value - Analog value that is output from the piezo representing the
 * magnitude of vibrations.
 * @param pointer Void pointer that is not being used.
 */

void Thief_CheckADC(uint16_t value, void *pointer);

 /** @}
 * 
 * 
 */
 
void Thief_Piezo_Init(void(*CE)(uint8_t), void(*CSN)(uint8_t)){
    version_t version;
    version.word = 0x01010001;
    sys_id = Subsystem_Init("PIEZO", version, 0);
    LogMsg(sys_id, "Piezo start");
    Thief_Init(CE, CSN, Thief_Piezo_Arm, Thief_Piezo_Disarm, Thief_Piezo_Difficulty);
    ADC_Init();
    ADC_AddChannel(0, 1, Thief_CheckADC, 0);
    Thief_Trip(0);
    initialized = 1;
    LogMsg(sys_id, "Piezo Initialized");

}

void Thief_Piezo_Arm(){
    armed = 1;
    LogMsg(sys_id, "Armed");
}

void Thief_Piezo_Disarm(){
    armed = 0;
    LogMsg(sys_id, "Disarmed");
}

void Thief_Piezo_Difficulty(uint8_t diff){
    difficulty = diff;
    LogMsg(sys_id, "New difficulty: %d", difficulty);
}

void Thief_CheckADC(uint16_t value, void *pointer){
    if(armed && initialized){
        if(value > 30){
            if (samplingStartTime < (TimeNow() - 3000)) {
                LogMsg(sys_id, "%d", value);
                samplingStartTime = TimeNow();
                Thief_Trip(1 * (difficulty+1));
            }
        }
    }
}
