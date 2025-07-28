/*
 * PWM1.h
 *
 * Created: 27/7/2025 21:16:24
 *  Author: Alvaro
 */ 


#ifndef PWM1_H_
#define PWM1_H_


#include <avr/io.h>

#define NO_INVERTING	1
#define INVERTING		0


void PWM1_init(void);
void PWM1_dca(uint8_t dc, uint8_t modo);
void PWM1_dcb(uint8_t dc, uint8_t modo);



#endif /* PWM1_H_ */