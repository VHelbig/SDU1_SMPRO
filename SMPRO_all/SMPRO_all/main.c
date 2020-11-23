/*
 * SMPRO_all.c
 *
 * Created: 23.09.2020 15:16:03
 * Author : vince
 */ 


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
		
		speed=100; //Speed is the value received from slider on the display 
		if(speed!=oldspeed){ //Check whether the speed is updated
			oldspeed=speed;
			change_speed(speed-50); //Calls the change-speed function, which changes the speed to the new value.
			
		}
		if(speed!=50){ //so it doesn´t freeze the program.
			
			display_speed(average_speed_measure()*100);	//update displayed value
			//}else{
			//display_speed(0);
			
		}	
		
    }
	
}
