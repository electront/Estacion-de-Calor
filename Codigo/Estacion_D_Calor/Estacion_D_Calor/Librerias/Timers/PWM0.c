/*
 * PWM0.c
 *
 * Created: 8/05/2022 18:40:31
 *  Author: carlo
 */ 

#include "PWM0.h"

void PWM1_init(void)
{
	// Modo Fast PWM
	TCCR1B &= ~(1<<WGM02);
	TCCR1A |= (1<<WGM01);
	TCCR1A |= (1<<WGM00);
	
	// Prescalador 64
	TCCR1B &= ~(1<<CS02);
	TCCR1B |= (1<<CS01);
	TCCR1B |= (1<<CS00);
}

void PWM1_dca(uint8_t dc, uint8_t modo)
{
	if(modo == 1)
	{
		TCCR1A |= (1<<COM1A1);
		TCCR1A &= ~(1<<COM1A0);
	}
	else
	{
		TCCR1A |= (1<<COM1A1);
		TCCR1A |= (1<<COM1A0);
		
	}
	OCR1A = (dc * 255) / 100;
}

void PWM1_dcb(uint8_t dc, uint8_t modo)
{
	if(modo == 1)
	{
		TCCR1A |= (1<<COM1B1);
		TCCR1A &= ~(1<<COM1B0);
	}
	else
	{
		TCCR1A |= (1<<COM1B1);
		TCCR1A |= (1<<COM1B0);
		
	}
	OCR1B = (dc * 255) / 100;
	
}