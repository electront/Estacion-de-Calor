/*
 * Banderas.h
 *
 * Created: 27/7/2025 18:48:50
 *  Author: Alvaro
 */ 


#ifndef BANDERAS_H_
#define BANDERAS_H_
#include <stdbool.h>

struct Banderas_S{
	bool SeleccionPot;//false Temoeratura true Aire..
	bool Estado;//false apagado true encendido..
	bool Inicio;
}Banderas;

void Banderas_Inicializar();

#endif /* BANDERAS_H_ */