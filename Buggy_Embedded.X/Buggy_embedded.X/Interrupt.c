/*
 * File:   Interrupt.c
 * Author: bohle
 *
 * Created on 11 novembre 2023, 12:30
 */


#include <xc.h>
#include "Interrupt.h"
#include "main.h"


void __attribute__((__interrupt__, __auto_psv__))_INT1Interrupt(){
    IEC1bits.INT1IE = 0; // Desenable Interrupt Flag
    IFS1bits.INT1IF = 0; // Clear Interrupt Flag
    T2CONbits.TON = 1; // start timer2
}

// pour l'interruption des deux boutons, il nous faut remapper les pins des boutons sur des pins des interrupts

void __attribute__((__interrupt__, __auto_psv__))_T2Interrupt() { // timer 2 is used for unboucing of bouton
    T2CONbits.TON = 0; // stop timer2
    IFS0bits.T2IF = 0; //reset the flag
    TMR2 = 0x00; //reset timer2
    
    // if the button is released
    if (PORTEbits.RE8 == 1) {
        if (state == STATE_WAIT_FOR_START){
            state = STATE_MOVING;
        }
        else if (state == STATE_MOVING) {
            state = STATE_WAIT_FOR_START;
        }
        IEC1bits.INT1IE = 1; // Enable Interrupt Flag
    }
}

//void __attribute__((__interrupt__, __auto_psv__))_T1Interrupt() { // timer 1 is used for unboucing of bouton
//    IFS0bits.T1IF = 0; //reset the flag
//    TMR1 = 0x00; //reset timer1
////    StateLED1=!StateLED1;
//    LATAbits.LATA0 = 1;
//}

/*
void __attribute__((__interrupt__, __auto_psv__)) _U2RXInterrupt() {
    IFS1bits.U2RXIF = 0; // Flag d'interruption RX UART
    char receivedData = U2RXREG;
    add_to_buffer(receivedData);
}*/


