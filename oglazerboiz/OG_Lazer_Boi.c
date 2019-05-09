/**
 * @addtogroup OG_Lazer_Boi_module
 *
 *  Created on: May 6, 2019
 *      @author DJ Stahlberger
 *
 *
 */

#include "task.h"
#include "thief.h"
#include "subsystem.h"
#include "OG_Lazer_Boi.h"


/* Variables */

static uint8_t penalty = 0;     //difficulty multiplier



//Initialization of the ports using lasers
//All ports set to GPIO
void Laser_Init(void){

    //Sensor Pin Initialization

    //Pin 3.4
    P3SEL &= ~BIT4;             //Sets pin to GPIO
    P3DIR &= ~BIT4;             //Sets direction to input
    P3REN |= BIT4;              //Enables pullup/pulldown resistor
    P3OUT |= BIT4;              //Sets internal resistor to pullup mode

    //Pin 3.3
    P3SEL &= ~BIT3;
    P3DIR &= ~BIT3;
    P3REN |= BIT3;
    P3OUT |= BIT3;

    //Pin 6.0
    P6SEL &= ~BIT0;
    P6DIR &= ~BIT0;
    P6REN |= BIT0;
    P6OUT |= BIT0;

    //Pin 6.1
    P6SEL &= ~BIT1;
    P6DIR &= ~BIT1;
    P6REN |= BIT1;
    P6OUT |= BIT1;

    //Pin 6.2
    P6SEL &= ~BIT2;
    P6DIR &= ~BIT2;
    P6REN |= BIT2;
    P6OUT |= BIT2;


    //Power Pin Initialization
    //Again, the numbers represent the corresponding sensors
    //for ease of use

    //Power pin for the 3.4 emitter
    P6SEL &= ~BIT3;             //Sets pin to GPIO
    P6DIR |= BIT3;              //Enables Output
    P6OUT |= BIT3;              //Sets the pin to be digital high

    //Power pin for the 3.3 emitter
    P6SEL &= ~BIT4;
    P6DIR |= BIT4;
    P6OUT |= BIT4;


    //Power pin for the 6.0 emitter
    P7SEL &= ~BIT0;
    P7DIR |= BIT0;
    P7OUT |= BIT0;

    //Power pin for the 6.1 emitter
    P3SEL &= ~BIT6;
    P3DIR |= BIT6;
    P3OUT |= BIT6;

    //Power pin for the 6.2 emitter
    P3SEL &= ~BIT5;
    P3DIR |= BIT5;
    P3OUT |= BIT5;

    //Schedules Check_Trip to be run every 10ms
    Task_Schedule(Check_Trip, 0, 0, 10);

    //Schedules Check_Object to be run every 10ms
    Task_Schedule(Check_Object, 0, 0, 10);
}

//Disarms the trap
void Laser_Disarm(void){

    //Makes sure the trap can't be tripped anymore
    Task_Remove(Check_Trip, 0);

    //Makes sure the trap isn't checking the object after disarm
    Task_Remove(Check_Object, 0);

    //Turns off the Power Pins for the laser emitters. The numbers represent
    //the corresponding sensors for ease of use

    //Power pin for the 3.4 emitter
    P6OUT &= ~BIT3;

    //Power pin for the 3.3 emitter
    P6OUT &= ~BIT4;

    //Power pin for the 6.0 emitter
    P7OUT &= ~BIT0;

    //Power pin for the 6.1 emitter
    P3OUT &= ~BIT6;

    //Power pin for the 6.2 emitter
    P3OUT &= ~BIT5;
}


//Checks to see if the object was moved
void Check_Object(void){
    if(P6IN & BIT2)                 //Checks if the sensor is reading a value
        Laser_Disarm();             //Disarms the trap if the object was moved


}

//Checks to see if there were any trips in the trap
void Check_Trip(void){
    if(P6OUT & BIT3)                //Checks if the laser is "powered"
        if(~P3IN & BIT4){           //Checks if the sensor is reading a value
            P6OUT &= ~BIT3;         //Turns off the "power" pin
            Thief_Trip(penalty*5);  //Sends score data to the MASTER node
        }

    if(P6OUT & BIT4)
        if(~P3IN & BIT3){
            P6OUT &= ~BIT4;
            Thief_Trip(penalty*5);
        }

    if(P7OUT & BIT0)
        if(~P6IN & BIT0){
            P7OUT &= ~BIT0;
            Thief_Trip(penalty*5);
        }

    if(P3OUT & BIT6)
        if(~P6IN & BIT1){
            P3OUT &= ~BIT6;
            Thief_Trip(penalty*5);
        }
}


//Utilized by Thief_Init to receive difficulty data from the MASTER node
void Difficulty(uint8_t data)
{
    penalty = data;                 //Sets the score multiplier to the passed value
    LogMsg(0, "The difficulty is set to %d", penalty);
                                    //Sends a log message to the command window of
                                    //the current difficulty
}

/**
*
*
*/
