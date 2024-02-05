/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */
 
#ifndef UART_H
#define	UART_H

#define Fosc 144000000
#define FCY (Fosc/2)
#define TCY (1/FCY)
#define BaudR 9600
#define BRGVAL FCY/(16.0*BaudR) - 1

#include <xc.h> // include processor files - each processor file is guarded.  

void InitUART(void);
void sendUARTbuff(char buffer[]);

#endif	/* UART_H */

