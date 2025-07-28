/*
 * PWM0.c
 *
 * Created: 8/05/2022 18:40:31
 *  Author: carlo
 */ 

#include "PWM0.h"

void PWM0_init(void)
{
	// Modo Fast PWM
	TCCR0B &= ~(1<<WGM02);
	TCCR0A |= (1<<WGM01);
	TCCR0A |= (1<<WGM00);
	
	// Prescalador 64
	TCCR0B &= ~(1<<CS02);
	TCCR0B |= (1<<CS01);
	TCCR0B |= (1<<CS00);
	
	DDRD |= (1<<5);		//PD5 como Salida
	DDRD |= (1<<6);		//PD6 como Salida
}

void PWM0_dca(uint8_t dc, uint8_t modo)
{
	if(modo == 1)
	{
		TCCR0A |= (1<<COM0A1);
		TCCR0A &= ~(1<<COM0A0);
	}
	else
	{
		TCCR0A |= (1<<COM0A1);
		TCCR0A |= (1<<COM0A0);
		
	}
	OCR0A = (dc * 255) / 450;
}

void PWM0_dcb(uint8_t dc, uint8_t modo)
{
	if(modo == 1)
	{
		TCCR0A |= (1<<COM0B1);
		TCCR0A &= ~(1<<COM0B0);
	}
	else
	{
		TCCR0A |= (1<<COM0B1);
		TCCR0A |= (1<<COM0B0);
		
	}
	OCR0B = (dc * 255) / 100;
	
}