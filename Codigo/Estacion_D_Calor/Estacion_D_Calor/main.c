/*
 * Estacion_D_Calor.c
 *
 * Created: 27/7/2025 11:15:53
 * Author : Alvaro
 */ 
#define F_CPU 8000000UL

#include <avr/io.h>             // para GPIO
#include <avr/sleep.h>          // para los modos de sueño
#include <avr/interrupt.h>      // para las interrupciones
#include <util/delay.h>         // para los retrasos
#include <stdio.h>

#include "Librerias/LCD/lcd.h"
#include "Librerias/ADC/ADC.h"
#include "Librerias/PID/PID.h"
#include "Librerias/Timers/PWM0.h"
#include "Librerias/BADNERAS/Banderas.h"
#include "Librerias/Interrupciones/Interrupciones.h"

char str[5];
volatile uint16_t SeletAire, SeletTEMP, TEMP;

ISR(PCINT2_vect){
	if((PIND & (1<<2))==0){
		Banderas.Estado = false;
	}
	else{
		Banderas.Estado = true;
	}
}

ISR(INT1_vect){//Boton selector para saber 
	if(Banderas.SeleccionPot){
		Banderas.SeleccionPot = false;
	}
	else{
		Banderas.SeleccionPot = true;
	}
}

int main(void)
{
	cli();
    lcd_init();
	ADC_init();
	PWM0_init();
	PID_SetMode(1);
	Interrupcion_Inicializar();
	Banderas_Inicializar();
	
	sei();
	
    while (1) 
    {
		TEMP = ADC_Leer_TEMP();
		
		if(!Banderas.SeleccionPot) SeletTEMP = ADC_Selet_TEMP();
		else SeletAire = ADC_Selet_AIRE();
		 
		if(Banderas.Estado){
		PWM0_dca(SeletTEMP , 1);	
		PWM0_dcb(SeletAire , 1);
		
			
			
			
		}
		lcd_clear();	
		lcd_gotorc(1,1);
		sprintf(str, "T:%i", SeletAire);
		lcd_puts(str);
	
		_delay_ms(100);	
    }
}

