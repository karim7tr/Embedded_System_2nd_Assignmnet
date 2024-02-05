/*
 * File:   Timer.c
 * Author: bohle
 *
 * Created on 11 novembre 2023, 12:08
 */


#include <xc.h>
#include "Timer.h"

void tmr_setup_period(int timer, int ms){
    
    if (timer == TIMER1) {
        PR1 = (FCY / 256 * ((float) ms / 1000.0)); // 8 MHz / 256 / 10 < 65535!
        T1CONbits.TCKPS = 0x03; //set the prescaler as 1:256
        T1CONbits.TCS = 0x00; // Internal clock 
        TMR1 = 0; // reset timer counter
    } else if (timer == TIMER2) {
        PR2 = (FCY / 256 * ((float) ms / 1000.0)); // 8 MHz / 256 / 10 < 65535!
        T2CONbits.TCKPS = 0x03; //set the prescaler as 1:256
        T2CONbits.TCS = 0x00; // Internal clock 
        TMR2 = 0; // reset timer counter
    } else if (timer == TIMER3) {
        PR3 = (FCY / 256 * ((float) ms / 1000.0)); // 8 MHz / 256 / 10 < 65535!
        T3CONbits.TCKPS = 0x03; //set the prescaler as 1:256
        T3CONbits.TCS = 0x00; // Internal clock 
        TMR3 = 0; // reset timer counter
    } else if (timer == TIMER4) {
        PR4 = (FCY / 256 * ((float) ms / 1000.0)); // 8 MHz / 256 / 10 < 65535!
        T4CONbits.TCKPS = 0x03; //set the prescaler as 1:256
        T4CONbits.TCS = 0x00; // Internal clock 
        TMR4 = 0; // reset timer counter
    }
}

void tmr_wait_period(int timer){
    if (timer == TIMER1) {
        IFS0bits.T1IF = 0x00;
        T1CONbits.TON = 0x01; // set the timer ON
        while (IFS0bits.T1IF == 0x00);
        T1CONbits.TON = 0; // stop the timer!
    } else if (timer == TIMER2) {
        IFS0bits.T2IF = 0x00;
        T2CONbits.TON = 0x01; // set the timer ON
        while (IFS0bits.T2IF == 0x00);
        T2CONbits.TON = 0; // stop the timer!
    } else if (timer == TIMER3) {
        IFS0bits.T3IF = 0x00;
        T3CONbits.TON = 0x01; // set the timer ON
        while (IFS0bits.T3IF == 0x00);
        T3CONbits.TON = 0; // stop the timer!
    } else if (timer == TIMER4) {
        IFS1bits.T4IF = 0x00;
        T4CONbits.TON = 0x01; // set the timer ON
        while (IFS1bits.T4IF == 0x00);
        T4CONbits.TON = 0; // stop the timer!
    }
}

void tmr_wait_ms(int timer, int ms) {
    tmr_setup_period(timer, ms);
    tmr_wait_period(timer);
}