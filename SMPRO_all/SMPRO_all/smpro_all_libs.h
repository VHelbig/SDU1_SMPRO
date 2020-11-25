/*
 * smpro_all_libs.h
 *
 * Created: 05.11.2020 14:47:01
 *  Author: vince
 */ 


#ifndef SMPRO_ALL_LIBS_H_
#define SMPRO_ALL_LIBS_H_

//optocoupler functions:
void op_init(void); // initialize optocoupler
int is_none_hole(void); // is some in front of the optocoupler
float average_speed_measure();
float single_speed_measurement(int hole_no);

//lcd functions:
void lcd_init(void); // initialize lcd
void display_speed(int speed); // display speed on lcd
int get_distance(void); // ask for new speed from lcd slider
int get_time(void);
int get_setting(void); 

//pwm board functions:
void pwm_init(void); // initialize i2c and pwm connection
void change_speed(int speed);// send new speed to pwm board


#endif /* SMPRO_ALL_LIBS_H_ */