/*
 * usb_dis_con.c
 *
 * Created: 30.09.2020 11:52:37
 *  Author: vince
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "usart.h"
#include <util/delay.h> //here the delay functions are found
#include "usb_dis_con.h"

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