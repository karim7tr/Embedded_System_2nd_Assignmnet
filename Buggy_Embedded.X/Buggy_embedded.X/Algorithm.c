/*
 * File:   Decision.c
 * Author: bohle
 *
 * Created on 15 décembre 2023, 12:15
 */


#include <xc.h>
#include "Algorithm.h"
#include "main.h"


void moveForward(int value)
{
    // number of TMR pulse for choose the frequency of PWM
    OC1R = 0; // motor left
    OC2R = value; // motor left
    OC3R = 0; // motor right
    OC4R = value; // motor right
}

void StopMotion(void)
{
    OC1R = 0; // motor left
    OC2R = 0; // motor left
    OC3R = 0; // motor right
    OC4R = 0; // motor right
}



void MotorControl (int surgePercent, int yaw_ratePercent)
{
    float factor = 1.0;
    int left_pwm_percent;
    int right_pwm_percent;
    int left_pwm;
    int right_pwm;
    
    left_pwm_percent = yaw_ratePercent + surgePercent;
    right_pwm_percent = surgePercent - yaw_ratePercent;
    
    //Scaled down value with a factor to stay in the range of [-100;100]]
    if (left_pwm_percent >100)
    {
        factor = left_pwm_percent/100.0;
    }
    else if(left_pwm_percent <-100)
    {
        factor = -left_pwm_percent/100.0;
    }
    left_pwm_percent = left_pwm_percent/factor;
    right_pwm_percent = right_pwm_percent/factor;
    factor = 1;
    
    if (right_pwm_percent >100)
    {
        factor = right_pwm_percent/100.0;
    }
    else if(right_pwm_percent <-100)
    {
        factor = -right_pwm_percent/100.0;
    }
    right_pwm_percent = right_pwm_percent/factor;
    left_pwm_percent = left_pwm_percent/factor;
    
    //conversion from percent to usable value
    left_pwm = (7200.0*right_pwm_percent/100.0);
    right_pwm = (7200.0*left_pwm_percent/100.0);
    
    //implemtation of motors value
    if (left_pwm >= 0)
    {
        OC1R = 0;
        OC2R = left_pwm;
    }
    else
    {
        OC1R = -left_pwm;
        OC2R = 0;
    }
    
    if (right_pwm >= 0)
    {
        OC3R = 0;
        OC4R = right_pwm;
    }
    else
    {
        OC3R = -right_pwm;
        OC4R = 0;
    }
}