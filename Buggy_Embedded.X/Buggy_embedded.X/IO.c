/*
 * File:   IO.c
 * Author: lenovo
 *
 * Created on 3 janvier 2024, 10:57
 */


#include <xc.h>
#include "IO.h"

void initIO()
{
    ANSELA = ANSELB = ANSELC = ANSELD = ANSELE = ANSELG = 0x0000; 
    // IMPORTANT : désactiver les entrées analogiques, sinon on perd les entrées numériques
    
    // Potentiometre on clicker 2
    TRISBbits.TRISB3 = 0; // pin EN of potentiometre as output
    LATBbits.LATB3 = 1; // pin EN of potentiometre put at High to enable the module
    ANSELBbits.ANSB5 = 1; //analog pin pin VO of potentiometre as input
    
    // IF captor on microbus 2
//    TRISBbits.TRISB9 = 0; // pin EN of IR captor as output
//    LATBbits.LATB9 = 1; // pin EN of IR captor put at High to enable the module //or A3 for microbus 1
    TRISBbits.TRISB9 = 0; // pin EN of IR captor as output
    LATBbits.LATB9 = 1; // pin EN of IR captor put at High to enable the module //or A3 for microbus 1
    TRISBbits.TRISB14 = 1; // pin EN of IR captor as input
    ANSELBbits.ANSB14 = 1; //analog pin // analog pin VO of IR captor as input //or B15 for microbus1
//    TRISBbits.TRISB15 = 1;
//    ANSELBbits.ANSB15 = 1; 
    
    
    // RE8 is RPI88 remappage of pin for button
    RPINR0bits.INT1R = 0x59; // 0x59 is 88 in hex
    INTCON2bits.GIE = 1; // set global interrupt
    INTCON2bits.INT1EP = 0; // interrupt on positive edge
    IFS1bits.INT1IF = 0; // Clear Interrupt Flag
    IEC1bits.INT1IE = 1; // Enable Interrupt Flag
    
    // Battery sensed
    TRISBbits.TRISB11 = 1; // pin EN of Battery sensed as input
    ANSELBbits.ANSB11 = 1; //analog pin // analog pin VO of Battery sensed as input
    // Leds
    _TRISA0 = 0; // LED 1 as output
    _TRISG9 = 0; // LED 2 as output
    _TRISE8 = 1; // button as input
    
    _TRISF1 = 0; // LED right as output
    _TRISB8 = 0; // LED left as output
    _TRISF0 = 0; // LED brakes as output
    _TRISG1 = 0; // LED low intensity as output
    _TRISA7 = 0; // LED bream headlight as output
}
