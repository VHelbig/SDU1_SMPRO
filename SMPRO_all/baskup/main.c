/*
 * SMPRO_all.c
 *
 * Created: 23.09.2020 15:16:03
 * Author : vince
 */ 
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <stdio.h>
#include "smpro_all_libs.h"



int main(void)
{	
	pwm_init();
	lcd_init();
	op_init();
	
	int speed=0;
	int oldspeed=-1;
	
    while (1) 
    {
		speed=get_wspeed();
		if(speed!=oldspeed){
			oldspeed=speed;
			change_speed(speed-50);
			
			if((speed-50)!=0){
				display_speed(single_speed_measurement(9)*100);		
			}else{
				display_speed(0);		
			}
		}
    }
	
}
