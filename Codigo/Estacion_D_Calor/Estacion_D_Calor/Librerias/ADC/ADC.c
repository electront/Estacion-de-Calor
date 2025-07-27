/*
 * ADC.c
 *
 * Created: 8/05/2022 18:51:01
 *  Author: carlo
 */ 

#include "ADC.h"


void ADC_init(void)
{
	ADMUX |=  (1<<REFS0);		//Seleccionar el voltaje de referencia
	ADMUX &=~ (1<<REFS1);
	ADMUX &=~ (1<<ADLAR);		//Ajustar el resultado

	//ADCSRA |= (1<<ADPS0);		// divisor = 128  8000000/128 = 125 KHz
	ADCSRA |= (1<<ADPS1);
	ADCSRA |= (1<<ADPS2);
	ADCSRA |= (1<<ADEN);		// Encendemos en ADC
	
	//ADCSRA|=(1<<ADSC);				//Inicia la conversión
}


uint16_t ADC_read(uint8_t canal)
{
	canal&=0b00001111;				//Limitar la entrada a 5
	ADMUX = (ADMUX & 0xF0)|canal;  //Limpiar los últimos 4 bits de ADMUX, OR con ch
	ADCSRA|=(1<<ADSC);				//Inicia la conversión
	while((ADCSRA)&(1<<ADSC));		//Hasta que se complete la coversión
	return(ADC);					//devuelve el valor del adc
}


uint8_t ADC_Leer_POT_TEMP(){
uint16_t lectura = 0;
	
	for(uint8_t i = 0; i < CantMuestras; i++){
	lectura += ADC_read(7)*(100/1024);
	}
	
 return (lectura/CantMuestras);
}
	
uint8_t ADC_Leer_POT_AIRE(){
uint16_t lectura = 0;
	
	for(uint8_t i = 0; i < CantMuestras; i++){
	lectura += ADC_read(6)*(100/1024);
	}
	
 return (lectura/CantMuestras);
}

float ADC_Leer_TEMP(){
	
	
}