/*
 * PWM.c
 *
 * Created: 05.10.2020 15:16:56
 *  Author: vince
 */ 
#include <avr/io.h>
#include <stdio.h>
#include "i2cmaster.h"
#include "PCA9685_SPRO1MC.h"

void pwm_init(void){
	i2c_init();
	PCA9685_init_pwm(PWM_FREQUENCY_50);
}

void change_speed(int speed){
	int zeroSignal=298;
	PCA9685_set_pwm(SERVO1,0,zeroSignal+speed);
}