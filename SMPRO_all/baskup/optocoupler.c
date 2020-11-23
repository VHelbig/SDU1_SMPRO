/*
 * optocoupler.c
 *
 * Created: 05.10.2020 14:23:43
 *  Author: vince
 */ 

#include <avr/io.h>

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