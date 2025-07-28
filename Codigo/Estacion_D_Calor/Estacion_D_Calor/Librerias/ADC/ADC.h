/*
 * ADC.h
 *
 * Created: 8/05/2022 18:50:39
 *  Author: Alvaro
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>

#define CantMuestras 10


void ADC_init(void);
uint16_t ADC_read(uint8_t canal);

uint16_t ADC_Selet_AIRE();
uint16_t ADC_Selet_TEMP();

float ADC_Leer_TEMP();
uint16_t ADC_Leer_Convertir_Escala(uint8_t canal_trabajo, uint16_t escala);



#endif /* ADC_H_ */