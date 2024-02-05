/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

#ifndef TIMER_H
#define	TIMER_H

#define TIMER1 1
#define TIMER2 2
#define TIMER3 3
#define TIMER4 4

#define Fosc 144000000
#define FCY (Fosc/2)

#include <xc.h> // include processor files - each processor file is guarded.  

void tmr_setup_period(int timer, int ms);
void tmr_wait_period(int timer);
void tmr_wait_ms(int timer, int ms);

#endif	/* TIMER_H */

