/*
 * ADC.c
 *
 * Created: 8/05/2022 18:51:01
 *  Author: Alvaro
 */ 

#include "ADC.h"


void ADC_init(void)
{
	ADMUX |=  (1<<REFS0);		//Seleccionar el voltaje de referencia
	ADMUX &=~ (1<<REFS1);
	
	ADMUX &=~ (1<<ADLAR);		//Ajustar el resultado

	ADCSRA &=~ (1<<ADPS0);		// divisor = 128  8000000/128 = 125 KHz
	ADCSRA |= (1<<ADPS1);
	ADCSRA |= (1<<ADPS2);
	
	ADCSRA |= (1<<ADEN);		// Encendemos en ADC
}


uint16_t ADC_read(uint8_t canal)
{
	canal&=0b00001111;				//Limitar la entrada a 5
	ADMUX = (ADMUX & 0xF0)|canal;  //Limpiar los últimos 4 bits de ADMUX, OR con ch
	ADCSRA|=(1<<ADSC);				//Inicia la conversión
	while((ADCSRA)&(1<<ADSC));		//Hasta que se complete la coversión
	return(ADC);					//devuelve el valor del adc
}


uint16_t ADC_Selet_AIRE(){
	uint16_t lectura = 0;
	for(uint8_t i = 0; i < CantMuestras; i++){
	lectura += ADC_Leer_Convertir_Escala(1,100);
	}
 return lectura/CantMuestras;
}

uint16_t ADC_Selet_TEMP(){
	uint16_t lectura = 0;
	for(uint8_t i = 0; i < CantMuestras; i++){
		lectura += ADC_Leer_Convertir_Escala(1,450);
	}
return lectura/CantMuestras;
}
	
float ADC_Leer_TEMP(){
	uint16_t lectura = 0;
	for(uint8_t i = 0; i < CantMuestras; i++){
		lectura += ADC_Leer_Convertir_Escala(0,500);
	}
return lectura/CantMuestras;
}

uint16_t ADC_Leer_Convertir_Escala(uint8_t canal_trabajo, uint16_t escala){
	uint16_t valor_leido = 0;
	valor_leido = ADC_read(canal_trabajo) * (((float) escala) / 1024);
	
	return valor_leido;
}