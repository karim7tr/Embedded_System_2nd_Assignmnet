/*
 * File:   PWM.c
 * Author: bohle
 *
 * Created on 14 décembre 2023, 15:26
 */


#include <xc.h>
#include "PWM.h"

void InitPWM(){

    //setting PWM

    
    // clear all register for Output compare 1 2 3 and 4 (OC1, OC2, OC3, OC4)
    OC1CON1 = OC1CON2 = OC2CON1 = OC2CON2 = OC3CON1 = OC3CON2 = OC4CON1 = OC4CON2 = 0;
    
    //setting
    OC1CON1bits.OCTSEL = 7; // select input clock for the OC1 module
    OC1CON1bits.OCM = 0b110;// Edge-Aligned
    OC1CON2bits.SYNCSEL = 0x1F;
    
    //setting
    OC2CON1bits.OCTSEL = 7; // select input clock for the OC1 module
    OC2CON1bits.OCM = 0b110;// Edge-Aligned
    OC2CON2bits.SYNCSEL = 0x1F;
    
    //setting
    OC3CON1bits.OCTSEL = 7; // select input clock for the OC1 module
    OC3CON1bits.OCM = 0b110;// Edge-Aligned
    OC3CON2bits.SYNCSEL = 0x1F;
    
    //setting
    OC4CON1bits.OCTSEL = 7; // select input clock for the OC1 module
    OC4CON1bits.OCM = 0b110;// Edge-Aligned
    OC4CON2bits.SYNCSEL = 0x1F;

    // Remappe pins
    RPOR0bits.RP65R = 0b010000; // RD1 is RP65
    RPOR1bits.RP66R = 0b010001; // RD2 is RP66
    RPOR1bits.RP67R = 0b010010; // RD3 is RP67
    RPOR2bits.RP68R = 0b010011; // RD4 is RP68
    
    OC1RS = OC2RS = OC3RS = OC4RS = 7200; // number of TMR pulse for choose the frequency of 10kHz
    /* because Tpwm/Tcy = 7200 with Tpwm = 1/10kHz */
}
