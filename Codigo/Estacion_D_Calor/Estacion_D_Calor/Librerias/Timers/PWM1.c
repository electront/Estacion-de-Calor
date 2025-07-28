/*
 * PWM1.c
 *
 * Created: 27/7/2025 21:16:34
 *  Author: Alvaro
 */ 


#include "PWM1.h"

void PWM1_init(void)
{
	// Modo Fast PWM
	TCCR1B &= ~(1<<WGM12);
	TCCR1A |= (1<<WGM11);
	TCCR1A |= (1<<WGM10);
	
	// Prescalador 64
	TCCR1B &= ~(1<<CS12);
	TCCR1B |= (1<<CS11);
	TCCR1B |= (1<<CS10);
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