/*
 * SMPRO_all.c
 *
 * Created: 23.09.2020 15:16:03
 * Author : vince
 */ 

#include <avr/io.h>
#include <stdio.h>
#include "usart.h"
#include "i2cmaster.h"
#include "PCA9685_SPRO1MC.h"
#include "optocoupler.h"

#define F_CPU 16000000UL 



int main(void)
{
    /* Replace with your application code */
	uart_init(); // open commection with computer
	io_redirect(); // redirect computer input to microcontroller
	//i2c_init();
	
	OPinit();
	
    while (1) 
    {
		//PCA9685_init_pwm(50);
		//PCA9685_set_pwm(SERVO1,0,10);
		printf("%d\n",is_active());
    }
}

