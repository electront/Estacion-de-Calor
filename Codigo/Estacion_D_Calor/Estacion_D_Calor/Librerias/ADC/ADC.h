/*
 * ADC.h
 *
 * Created: 8/05/2022 18:50:39
 *  Author: carlo
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>

#define CantMuestras 10


void ADC_init(void);
uint16_t ADC_read(uint8_t canal);

uint8_t ADC_Leer_POT_TEMP();
uint8_t ADC_Leer_POT_AIRE();
float ADC_Leer_TEMP();



#endif /* ADC_H_ */