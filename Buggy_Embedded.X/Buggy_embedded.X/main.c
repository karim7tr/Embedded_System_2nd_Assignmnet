/*
 * File:   main.c
 * Authors: 
 * Chloe Bohler S6528470
 * Karim Triki S5528602
 * Dina Boutemeur S6580883
 *
 * Created on 3 janvier 2024, 10:57
 */
// DSPIC33EP512MU810 Configuration Bit Settings

// 'C' source line config statements

// FGS
#pragma config GWRP = OFF               // General Segment Write-Protect bit (General Segment may be written)
#pragma config GSS = OFF                // General Segment Code-Protect bit (General Segment Code protect is disabled)
#pragma config GSSK = OFF               // General Segment Key bits (General Segment Write Protection and Code Protection is Disabled)

// FOSCSEL
#pragma config FNOSC = PRI              // Initial Oscillator Source Selection Bits (Primary Oscillator (XT, HS, EC))
#pragma config IESO = ON                // Two-speed Oscillator Start-up Enable bit (Start up device with FRC, then switch to user-selected oscillator source)

// FOSC
#pragma config POSCMD = XT              // Primary Oscillator Mode Select bits (XT Crystal Oscillator Mode)
#pragma config OSCIOFNC = OFF           // OSC2 Pin Function bit (OSC2 is clock output)
#pragma config IOL1WAY = ON             // Peripheral pin select configuration (Allow only one reconfiguration)
#pragma config FCKSM = CSDCMD           // Clock Switching Mode bits (Both Clock switching and Fail-safe Clock Monitor are disabled)

// FWDT
#pragma config WDTPOST = PS32768        // Watchdog Timer Postscaler Bits (1:32,768)
#pragma config WDTPRE = PR128           // Watchdog Timer Prescaler bit (1:128)
#pragma config PLLKEN = ON              // PLL Lock Wait Enable bit (Clock switch to PLL source will wait until the PLL lock signal is valid.)
#pragma config WINDIS = OFF             // Watchdog Timer Window Enable bit (Watchdog Timer in Non-Window mode)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable bit (Watchdog timer enabled/disabled by user software)

// FPOR
#pragma config FPWRT = PWR128           // Power-on Reset Timer Value Select bits (128ms)
#pragma config BOREN = ON               // Brown-out Reset (BOR) Detection Enable bit (BOR is enabled)
#pragma config ALTI2C1 = OFF            // Alternate I2C pins for I2C1 (SDA1/SCK1 pins are selected as the I/O pins for I2C1)
#pragma config ALTI2C2 = OFF            // Alternate I2C pins for I2C2 (SDA2/SCK2 pins are selected as the I/O pins for I2C2)

// FICD
#pragma config ICS = PGD1               // ICD Communication Channel Select bits (Communicate on PGEC1 and PGED1)
#pragma config RSTPRI = PF              // Reset Target Vector Select bit (Device will obtain reset instruction from Primary flash)
#pragma config JTAGEN = OFF             // JTAG Enable bit (JTAG is disabled)

// FAS
#pragma config AWRP = OFF               // Auxiliary Segment Write-protect bit (Auxiliary program memory is not write-protected)
#pragma config APL = OFF                // Auxiliary Segment Code-protect bit (Aux Flash Code protect is disabled)
#pragma config APLK = OFF               // Auxiliary Segment Key bits (Aux Flash Write Protection and Code Protection is Disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include "main.h"
#include "Timer.h"
#include "Interrupt.h"
#include "UART.h"
#include "PWM.h"
//#include "Buffer.h"
#include "ADC.h"
#include "Algorithm.h"
#include "IO.h"
#include "Action.h"

int state = STATE_WAIT_FOR_START;
int previous_state;
int count_1Hz;
int count_10Hz;
int yaw_rate = 0;

char buff[50];
char buff2[22];
char buf[3];

int main(void) {
    
    initIO();
    InitUART();
    InitADC();
    InitPWM();
    
    LED2 = 1;
    
    tmr_setup_period(TIMER1, 1); // timer 1 setup at 1 kHz
    
    tmr_setup_period(TIMER2, 20); // timer 2 for button unbouncing
    IEC0bits.T2IE = 0x01; // enable timer2 interrupt
    
    state = STATE_WAIT_FOR_START;
    previous_state = STATE_WAIT_FOR_START;
    count_1Hz = 0;
    count_10Hz = 0;
    
    while(1){ // Loop at 1kHz
        
        tmr_wait_ms(TIMER1, 1); // Wait for sampling time (10us) //why did we put it at 10 ?
        
        while (!AD1CON1bits.DONE){}; // Wait for the conversion to complete
        
        // IR sensor
        float adc_ir = ADC1BUF1; 
        float v = 3.3 * adc_ir / 1024;
        int distance = 100*(2.34 - 4.74*v + 4.06*v*v - 1.60 *v*v*v + 0.24*v*v*v*v); //distance in cm 
        
        // Battery calculation  
        float v_battery =(3.3 * ((float)ADC1BUF0 / 1024.0));
        
        yaw_rate = move(distance, state);
        
        count_10Hz = count_10Hz ++; // Count for 10Hz
        
        if (count_10Hz >= 100){  // frequence at 10Hz
            count_10Hz = 0;
            sprintf(buff, " $dist,%d *$MPWM %d,%d,%d,%d*", distance, OC1R, OC2R, OC3R, OC4R); // convert distance in characters chains
            count_1Hz = count_1Hz ++;
            
            if (count_1Hz == 5){ // frequence to blink the led at 1Hz, so every 500ms
                blink (state, yaw_rate);
            }
            if (count_1Hz >= 10){ // frequence at 1Hz
                count_1Hz = 0;
                
                blink (state, yaw_rate);
                
                sprintf(buff, " $BATT,%.2f* ", (double)(3*v_battery)); // convert voltage in characters chains 
                } 
            sendUARTbuff(buff);
            
        }
    }
    
    return 0;
}