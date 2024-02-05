/*
 * File:   UART.c
 * Author: 
 *
 * Created on 15 novembre 2023, 15:50
 */


#include <xc.h>
#include "UART.h"



void InitUART(void) {
    
    // remappable pin
    RPOR0bits.RP64R = 0x03; // Map UART 2 TX to pin RD0 which is RP64
    RPINR19bits.U2RXR = 0x4B; // Map UART 2 RX to pin RD11 which is RPI75 (0x4B = 75)
    
    // config & enable UART
    U2BRG = BRGVAL; // BAUD Rate Setting 9600 =  Fcy / (16* (UXBRG + 1)) // UXBRG = 4000000/(16*9600) - 1
    //U2STAbits.UTXISEL0 = 0; // Interrupt after one Tx character is transmitted
    //U2STAbits.UTXISEL1 = 0;
    U2STAbits.URXISEL = 0; // Interrupt after one RX character is received
    
    U2MODEbits.UARTEN = 1; // Enable UART
    U2STAbits.UTXEN = 1; // Enable UART Tx (must be after UARTEN)
}  

void sendUARTbuff(char buffer[]) {
    // CHECK THE BUFFER ISNT FULL
    int j = 0;
    while(buffer[j] != '\0'){
        while (U2STAbits.UTXBF != 1 && buffer[j] != '\0' ){ //check if the transmit buffer is not full
        U2TXREG = buffer[j];
        j++;
        }
    }
}

