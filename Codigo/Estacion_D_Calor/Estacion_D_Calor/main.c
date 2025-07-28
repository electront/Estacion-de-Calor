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
#include "Librerias/Ventanas/Ventanas.h"
#include "Librerias/Interrupciones/Interrupciones.h"

void Main_Estado();
void Main_Encender_Resistencia();
void Main_Apagar_Resistencia();
void Main_Encender_FAN();
void Main_Apagar_FAN();

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
	PID_Initialize();
	Interrupcion_Inicializar();
	Banderas_Inicializar();
	sei();
	
	SeletAire = 60;
	
    while (1) 
    {
		Main_Estado();
		TEMP = ADC_Leer_TEMP();
		
		if(!Banderas.SeleccionPot) SeletTEMP = ADC_Selet_TEMP();
		else SeletAire = ADC_Selet_AIRE();
		 
		if(Banderas.Estado){
		Main_Encender_FAN();
		Main_Encender_Resistencia();
		
		PID_SetInput(TEMP);
		PID_SetPoint(SeletTEMP);
		PID_SetOutputLimits((SeletTEMP - 10),(SeletTEMP + 10));
		PID_AutoTunings();
		PID_Compute();
		}
		else{
		
		Main_Apagar_Resistencia();
			if(TEMP > 80){
				PWM0_dcb(200 , 1);
			}else{
				Main_Apagar_FAN();
			}
		}
	Ventana_Principal();
    }
}

void Main_Estado(){
	if(!(PIND & (1<<2))){
		Banderas.Estado = false;
	}
	else{
		Banderas.Estado = true;
	}
}

void Main_Encender_Resistencia(){
	DDRD |= (1<< 6);	
	if(!Banderas.Inicio){
		PWM0_dca(50 , 1);
		Banderas.Inicio = true;
	}
}

void Main_Apagar_Resistencia(){
	DDRD &= ~ (1<< 6);	
	PORTD &= ~ (1<< 6);		
	Banderas.Inicio = false;
}


void Main_Encender_FAN(){
	PWM0_dcb(SeletAire , 1);
}

void Main_Apagar_FAN(){
	PWM0_dcb(0 , 1);
}