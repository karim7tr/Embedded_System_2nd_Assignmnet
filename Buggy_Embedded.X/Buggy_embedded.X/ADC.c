/*
 * File:   ADC.c
 * Author: lenovo
 *
 * Created on 11 novembre 2023, 12:45
 */


#include <xc.h>
#include "ADC.h"

void InitADC(){
    AD1CON3bits.ADCS = 14; // 14*T_CY
    AD1CON1bits.ASAM = 1; // automatic sampling start
    AD1CON1bits.SSRC = 7; // automatic conversion
    AD1CON3bits.SAMC = 16; // sampling lasts 16 Tad
    AD1CON2bits.CHPS = 0; // use CH0 2-channels sequential sampling mode
    AD1CON1bits.SIMSAM = 0; // sequential sampling
	// Scan mode specific configuration
	AD1CON2bits.CSCNA = 1; // scan mode enabled
    AD1CSSLbits.CSS11 = 1;   // scan for AN11 battery
    AD1CSSLbits.CSS14 = 1;   // scan for AN15 ir sensor
	AD1CON2bits.SMPI = 1; // N-1 channels
	
    AD1CON1bits.ADON = 1; // turn on ADC
    
}
