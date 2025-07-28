/*
 * Interrupciones.c
 *
 * Created: 27/7/2025 19:01:18
 *  Author: Alvaro
 */ 
#include "Interrupciones.h"

void Interrupcion_Inicializar(){
		DDRD &= ~(1<<2);		//PD2 como entrada
		PORTD |= (1<< 2);		//PD2 con pull up
		
		DDRD &= ~(1<<3);		//PD2 como entrada
		PORTD |= (1<< 3);		//PD2 con pull 
		
		PCMSK2 |= (1<<2); //PCINT18
		PCICR |= (1<<2);
		
		EICRA = 0b00001010;		//Interrupción externa por flanco de bajada en INT0
		EIMSK = 0b00000011;		//Habilita interrupción externa INT0
		EIFR = 0b00000000;		//SU BIT 0 A 0 PARA DETECTAR LAS INTERUPCIONES
}




	
	