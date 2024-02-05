/* 
 * File:   
 * Author: Chloe Dina Karim
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef MAIN_H
#define	MAIN_H

#include <xc.h> // include processor files - each processor file is guarded.  

/*// oscillator configuration already did by bootloader
    PLLFBD = 6; // M = 8
    CLKDIVbits.PLLPOST = 0x00; // N1 = 2
    CLKDIVbits.PLLPRE = 0x00; // N2 = 2
    RCONbits.SWDTEN = 0; // Disable Watch Dog Timer
    while (OSCCONbits.LOCK != 1);*/

#define STATE_WAIT_FOR_START 1
#define STATE_MOVING 2

#define LED1 LATAbits.LATA0
#define LED2 LATGbits.LATG9

#define LED_RIGHT LATFbits.LATF1
#define LED_LEFT LATBbits.LATB8
#define LED_BRAKES LATFbits.LATF0
#define LED_LOW_INTENSITY LATGbits.LATG1
#define LED_BEAM_HEADLIHT LATAbits.LATA7

#define TPMW TCY
#define FPWM 1/TPMW

#define MINTH 10
#define MAXTH 150

extern int state;
//extern int previous_state;
//extern _Bool StateLED1 ;

#endif	/* MAIN_H */

