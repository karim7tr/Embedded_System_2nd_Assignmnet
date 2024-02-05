/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef ALGORITHM_H
#define	ALGORITHM_H

#include <xc.h> // include processor files - each processor file is guarded.  

void moveForward(int value);
void moveRight(int value);
void moveLeft(int value);
void moveBackward(int value);
void StopMotion(void);

int left_pwm(int surge, int yaw_rate);
int right_pwm(int surge ,int yaw_rate);

void MotorControl (int surgePercent, int yaw_ratePercent);

#endif	/* ALGORITHM_H */

