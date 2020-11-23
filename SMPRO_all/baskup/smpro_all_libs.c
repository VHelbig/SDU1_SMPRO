/*
 * smpro_all_libs.c
 *
 * Created: 05.11.2020 14:52:10
 *  Author: vince
 */ 
//definitions:

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#ifndef BAUD
#define BAUD 9600
#endif
#include <util/setbaud.h>

#ifndef NUMBER_STRING
#define NUMBER_STRING 1001
#endif
//includes:

#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "usart.h"
#include <util/delay.h> 
#include "smpro_all_libs.h"
#include "i2cmaster.h"
#include "PCA9685_SPRO1MC.h"

//optocoupler functions:
void op_init(void){
	DDRD = 0b00000000;
	PORTD = 0b11111111;
}

int is_active(void){
	if(PIND & 0b10000000){
		return 0;
		}else{
		return 1;
	}
}

float average_speed_measure(int hole_no,int presision){
	float sum=0;
	for(int i=0;i<presision;i++){
		sum=sum+single_speed_measurement(hole_no);
	}
	return sum/presision;
}

float single_speed_measurement(int hole_no)
{
	int timecounter=0;
	int counter=0;
	int oldvalue=0;
	while(!is_active()){}
	while(counter!=hole_no+1)
	{
		int active=is_active();
		if(oldvalue==1 && active==0)
		{
			counter++;
			//printf("%d", counter);
		};
		timecounter++;
		
		oldvalue=active;
		_delay_ms(1);
		
		
	}
	//printf("%d\n",timecounter);
	int rotation=360/(hole_no*40);
	float time=((timecounter)/1000.0);
	return rotation/time;
}


//lcd functions:

void lcd_init(void){ // initializes connection with display over uart and initializes display.
	uart_init();//initialize communication with PC - debugging
	io_redirect();//redirect printf function to uart, so text will be shown on PC
	
	printf("page 0%c%c%c",255,255,255);//init at 9600 baud.
	_delay_ms(20);
}

void display_speed(int speed){
	printf("page0.x0.val=%d%c%c%c", speed, 255,255,255);
}

int get_wspeed(void){
	char readBuffer[100];
	uint32_t readValue = 0;
	printf("get page0.h0.val%c%c%c",255,255,255);	//sends "get page0.n0.val"
	int typeExpected = 0;
	
	for(int i = 0; i<8;i++)
	{
		scanf("%c", &readBuffer[i]);
		if(readBuffer[i] == 0x71)//Expect number string
		{
			typeExpected = NUMBER_STRING;
			readBuffer[0] = 0x71;//Move indicator to front, just to keep the nice format
			break;
			}else if(readBuffer[i] == 0x1A){//some error occurred - retrieve the 0xFF commands and start over
			scanf("%c", &readBuffer[i]);
			scanf("%c", &readBuffer[i]);
			scanf("%c", &readBuffer[i]);
			continue;
		}
	}
	if(typeExpected == NUMBER_STRING)
	{
		for(int i = 1; i<8; i++)
		{
			scanf("%c", &readBuffer[i]);
		}

		if(readBuffer[0] == 0x71 && readBuffer[5] == 0xFF && readBuffer[6] == 0xFF && readBuffer[7] == 0xFF)//This is a complete number return
		{
			readValue = readBuffer[1] | (readBuffer[2] << 8) | (readBuffer[3] << 16)| (readBuffer[4] << 24);
		}
	}
	return (int)readValue;
}

//pwm functions:

void pwm_init(void){
	i2c_init();
	PCA9685_init_pwm(PWM_FREQUENCY_50);
}

void change_speed(int speed){
	int zeroSignal=298;
	PCA9685_set_pwm(SERVO1,0,zeroSignal+speed);
}
