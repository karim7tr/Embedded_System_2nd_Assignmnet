/*
 * File:   state.c
 * Author: lenovo
 *
 * Created on 30 janvier 2024, 10:58
 */


#include "xc.h"
#include "Action.h" 
#include "main.h"
#include "PWM.h"

int move(int distance, int state) {
    int surge;
    int yaw_rate;
    
    if (state == STATE_MOVING){
//            moveForward(7200);
            
            
            if (distance <= MINTH)
            {
                surge = 0;
                yaw_rate = 100;
            }
            else if ((distance > MINTH) & (distance <= 20))
            {
                surge = 30;
                yaw_rate = 100;
            }
            
            else if ((distance > 20) & (distance <= 30))
            {
                surge = 80;
                yaw_rate = 40;
            }
            else if ((distance > 30) & (distance <= 40))
            {
                surge = 80;
                yaw_rate = 30;
            }
            else if ((distance > 40) & (distance <= 50))
            {
                surge = 100;
                yaw_rate = 20;
            }
            else if ((distance > 50) & (distance <= MAXTH))
            {
                surge = 100;
                yaw_rate = 0;
            }
            else 
            {
                surge = 100;
                yaw_rate = 0;
            }
            MotorControl(surge, yaw_rate);
            
            if (surge >= 50)
            {
                LED_BRAKES = 0;
                LED_LOW_INTENSITY = 0;
                LED_BEAM_HEADLIHT = 1;
            }
            if (surge <= 50)
            {
                LED_BRAKES = 1;
                LED_LOW_INTENSITY = 1;
                LED_BEAM_HEADLIHT = 0;
            }
            if (yaw_rate >= 15)
            {
                LED_RIGHT = 0; // INVERSER LES DEUX
            }
            if (yaw_rate <= 15)
            {
                LED_RIGHT = 0;
                LED_LEFT = 0;
            }
        }
        else if (state == STATE_WAIT_FOR_START) { //& (previous_state == STATE_MOVING)
            StopMotion();
            LED_BRAKES = 0;
            LED_LOW_INTENSITY = 0;
            LED_BEAM_HEADLIHT = 0;
        }
    return yaw_rate;
}

void blink (int state, int yaw_rate){
              
    LED1 = !LED1;
    if (state == STATE_WAIT_FOR_START){
        LED_RIGHT = !LED_RIGHT;
        LED_LEFT = LED_RIGHT;
    }
    else if (state == STATE_MOVING & yaw_rate >= 15){
        LED_LEFT = !LED_LEFT;
    }
}