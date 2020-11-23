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
#include <util/delay.h> 

typedef struct
{
	int distance; 
	int time; 
	}settings_t;
	
settings_t fill_array(void); 

int main(void)
{	
	pwm_init();
	lcd_init();
	op_init();
	
	settings_t settings[11];
	
	//int speed=0;
	//int oldspeed=-1;
	
	for (int i=0; i<11;i++)
		{
			settings[i].distance=0;
			settings[i].time=0;
		}
		
    while (1) 
    {
		change_speed(0);
		
		//int i=0;
		
	/*while(get_setting()<11)
		{
			if(get_setting()==(i+1))
			{
				settings[i]=fill_array();
				_delay_ms(100);
			}else if(get_setting()>(i+1)){
				i++;
			}else{
				break;
			}
		}*/
		
		
		while(get_setting()<11)
		{
			
		for(int i=0; i<11; i++)
		{
			if(get_setting()==(i+1))
			{
				settings[i-1]=fill_array(); 
			}
		}
		
		
		for (int i=0; i<11;i++)
		{
			printf("distance %d, time %d\n", settings[i].distance, settings[i].time); 
		}
		}
		
		/*speed=get_wspeed(); //Speed is the value received from slider on the display 
		if(speed!=oldspeed){ //Check whether the speed is updated
			oldspeed=speed;
			change_speed(speed-50); //Calls the change-speed function, which changes the speed to the new value.
			
			if(speed!=50){ //so it doesn´t freeze the program. 
				display_speed(average_speed_measure(9,3)*100);	//update displayed value	
			}else{
				display_speed(0);		
			}
		}*/
		
		
    }
	
}
settings_t fill_array(void)
{
	settings_t temp_setting; 
	
	temp_setting.distance = get_distance(); 
	temp_setting.time = get_time(); 
	return (temp_setting); 
}