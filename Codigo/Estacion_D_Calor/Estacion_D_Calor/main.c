/*
 * Estacion_D_Calor.c
 *
 * Created: 27/7/2025 11:15:53
 * Author : Alvaro
 */ 
#define F_CPU 8000000
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "Librerias/LCD/lcd.h"
#include "Librerias/ADC/ADC.h"

char str[5];

int main(void)
{
	cli();
    lcd_init();
	sei();

    while (1) 
    {
		
			uint16_t aire = ADC_read(2);//ADC_Leer_POT_AIRE();
			uint16_t temp = ADC_read(1);//ADC_Leer_POT_TEMP();
			
			
			lcd_gotorc(3,1);
			lcd_puts("TEST");
			
			
			lcd_gotorc(1,1);
			sprintf(str, "%i", aire);
			lcd_puts(str);
			
			lcd_gotorc(2,1);
			sprintf(str, "%i", temp);
			lcd_puts(str);
			
    }
}

