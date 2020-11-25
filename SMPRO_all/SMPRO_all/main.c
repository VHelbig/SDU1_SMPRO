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
#include "usart.h"
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
	
	while(1){
		for(int i=0;i<4;i++){
			int distance=-1;
			int time=-1;
			read_one_value(&distance,&time);
			read_one_value(&distance,&time);
			printf("distance:%d",distance);
			printf("time:%d",time);
		}
		printf("page0.n0.val=-12%c%c%c",0xFF,0xFF,0xFF);
    }
	
}
/*settings_t fill_array(void)
{
	settings_t temp_setting; 
	
	temp_setting.distance = get_distance(); 
	temp_setting.time = get_time(); 
	return (temp_setting); 
}*/
void read_one_value(int *distance, int *time){
	char readBuffer[100];
	for (int i=0;i<100;i++){
		readBuffer[i]=0;
	}
	int identifier_received=0;
	int i=-1;
	while (!identifier_received) //wait for a identifier
	{
		i++;

		readBuffer[i]=uart_getchar(stdin);
		
		if(readBuffer[i] == 0x71){ //A number is arriving
			int old_i=i; //pointing to first element of array
			while(i<old_i+7){
				i++;
				readBuffer[i]=uart_getchar(stdin);
			}
			identifier_received=3;
			if(readBuffer[old_i]==0x71 && readBuffer[old_i+5]==0xFF && readBuffer[old_i+6]==0xFF && readBuffer[old_i+7]==0xFF){ //Check format
				if(readBuffer[old_i+1] == 0x10 && readBuffer[old_i+2] == 0x27 && readBuffer[old_i+3] == 0x00 && readBuffer[old_i+4] == 0x00){ //first identifier
					identifier_received=1;
				}else if(readBuffer[old_i+1] == 0x20 && readBuffer[old_i+2] == 0x4E && readBuffer[old_i+3] == 0x00 && readBuffer[old_i+4] == 0x00){ //second identifier
					identifier_received=2;
				}
			}
		}
	}
	if(identifier_received){
		int number_received=0;
		while (!number_received)
		{
			readBuffer[i]=uart_getchar(stdin);
			if(readBuffer[i]== 0x71){ //A number is arriving
				number_received=1;
			}
			i++;
		}
		int old_i=i-1; //pointing to first element of array
		for(i;i<old_i+7+1;i++){
			readBuffer[i]=uart_getchar(stdin);;
		}
		if(readBuffer[old_i]==0x71 && readBuffer[old_i+5]==0xFF && readBuffer[old_i+6]==0xFF && readBuffer[old_i+7]==0xFF){ //Check format
			uint32_t readValue = readBuffer[old_i+1] | (readBuffer[old_i+2] << 8) | (readBuffer[old_i+3] << 16)| (readBuffer[old_i+4] << 24);
			if(identifier_received==1){
				*distance=readValue;
			}else if (identifier_received==2){
				*time=readValue;
			}
		}
	}
}