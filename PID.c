/*
 * PID.c
 *
 * Created: 12/11/2024 19:29:01
 *  Author: Alvaro
 */ 


#define F_CPU 32000000

#include <avr/io.h>
#include <string.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
#include <stdbool.h>
#include <stdio.h>
#include "PID.h"

//	Otras variables
//unsigned long millis = 0;
// Variables de trabajo.
//unsigned int lastTime;
double Input, Output, Setpoint;
double ITerm, lastInput;
double kp, ki, kd;
uint8_t SampleTime = 5; // Tiempo de muestreo 200 milisegundos.
double outMin, outMax;
bool inAuto = false;
#define MANUAL 0
#define AUTOMATIC 1
#define DIRECT 0
#define REVERSE 1
uint8_t controllerDirection = DIRECT;






//===================================================================================
//					PARAMETROS A CONFIGURAR											/
//																					/
//	Input:	Variable que se trata de controlar.										/
//	Output:	Variable que sera ajustada por el PID.									/
//	Setpint:Valor que quiero mantener.												/
//																					/
//	kp:Determina cuan agresivo es el PID y reacciona a la cantidad de error actual.	/
//	ki:Determina cuan agresivo es el PID y reacciona al error en el tiempo.			/
//	kd:Determina cuan agresivo reacciona el PID al cambio de error.					/
//===================================================================================



//===================================================================
//		Esta funcion realiza el Calculo para el PID.				/
//===================================================================
/*
void Compute()
{
	if(! inAuto) return;			
	unsigned int now = millis;		
	int timeChange = (now - lastTime) ;
	if(timeChange>=SampleTime)
	{
		// Calculamos todos los errores.
		double error = Setpoint - Input;
		ITerm+= (ki * error) ;
		if(ITerm> outMax) ITerm= outMax;
		else if(ITerm< outMin) ITerm= outMin;
		double dInput = (Input - lastInput) ;
		
		// Calculamos la función de salida del PID.
		Output = kp * error + ITerm- kd * dInput;
		if(Output > outMax) Output = outMax;
		else if(Output < outMin) Output = outMin;
		
		// Guardamos el valor de algunas variables para el próximo recálculo.
		lastInput = Input;
		lastTime = now;
	}
}*/

//en esta le desavilito la condicion de que solo se realize el calculo cuando ha pasado un tiempo ahora
//se realiza constantemente
void PID_Compute()
{
	if(! inAuto) return;
	else{
		// Calculamos todos los errores.
		double error = Setpoint - Input;
		ITerm+= (ki * error) ;
		if(ITerm> outMax) ITerm= outMax;
		else if(ITerm< outMin) ITerm= outMin;
		double dInput = (Input - lastInput) ;
		
		// Calculamos la función de salida del PID.
		Output = kp * error + ITerm- kd * dInput;
		if(Output > outMax) Output = outMax;
		else if(Output < outMin) Output = outMin;
		
		// Guardamos el valor de algunas variables para el próximo recálculo.
		lastInput = Input;
	}
}



//===================================================================================
//		Esta funcion varia en tiempo real los parametros de:						/
//	Kp:Determina cuan agresivo es el PID y reacciona a la cantidad de error actual.	/
//	Ki:Determina cuan agresivo es el PID y reacciona al error en el tiempo.			/
//	Kd:Determina cuan agresivo reacciona el PID al cambio de error.					/
//===================================================================================
void PID_SetTunings(double Kp, double Ki, double Kd)
{
	if (Kp<0 || Ki<0 || Kd<0) 
	return;
	
	double SampleTimeInSec = ((double) SampleTime) /1000;
	kp = Kp;
	ki = Ki * SampleTimeInSec;
	kd = Kd / SampleTimeInSec;
	if(controllerDirection == REVERSE)
	{
		kp = (0 - kp) ;
		ki = (0 - ki) ;
		kd = (0 - kd) ;
	}
}

//===============================================
//					AutoTunings					/
//===============================================

double aggKp = 4, aggKi = 0.2, aggKd = 1;
double consKp =1, consKi =0.05, consKd = 0.25;

void PID_AutoTunings(){
	double gap = abs(Setpoint - Input);
	
	if(gap<10)
	PID_SetTunings(consKp, consKi, consKd);
	else
	PID_SetTunings(aggKp, aggKi, aggKd);
}


//=======================================================================================
//		Esta funcion determina la frecuencia con la que se evalua el algorismo del PID.	/
//	NewSampleTime:Con que frecuencia en MS se evaluara el PID.							/
//=======================================================================================
void PID_SetSampleTime(int NewSampleTime)
{
	if (NewSampleTime > 0)
	{
		double ratio = (double) NewSampleTime / (double) SampleTime;
		ki *= ratio;
		kd /= ratio;
		SampleTime = (unsigned long) NewSampleTime;
	}
}


//===================================================================
//	Esta funcion realiza para limitar el rango de salida.			/
//	Minimo															/
//	Maximo															/
//===================================================================
void PID_SetOutputLimits(double Min, double Max)
{
	if(Min > Max) return;
	outMin = Min;
	outMax = Max;
	if(Output > outMax) Output = outMax;
	else if(Output < outMin) Output = outMin;
	if(ITerm> outMax) ITerm= outMax;
	else if(ITerm< outMin) ITerm= outMin;
}




//===================================================================
//	Esta funcion especifica si el PID deveria estar.				/
//	MANUAL----Apagado 												/
//	AUTOMATIC-Encendido												/
//===================================================================

void PID_SetMode(int Mode)
{
	bool newAuto = (Mode == AUTOMATIC) ;
	if(newAuto && ! inAuto)
	{ // Para cambiar de manual a automático, inicializamos algunos parámetros.
		PID_Initialize();
	}
	inAuto = newAuto;
}

void PID_Initialize()
{
	lastInput = Input;
	ITerm = Output;
	if(ITerm> outMax) ITerm= outMax;
	else if(ITerm< outMin) ITerm= outMin;
}


//===================================================================
//	Esta funcion especifica que tipo de proceso se conecta al PID.	/
//	Si mi entrada esta por encima del SetPoint:						/
//	DIRECT---cuando la salida debe disminuir para el ajuste.		/
//	REVERSE--cuando la salida debe aumentar para el ajuste.			/
//===================================================================
void PID_SetControllerDirection(int Direction)
{
	controllerDirection = Direction;
}




//===================================================================
//		Esta funcion es para ver valores de las variables 			/
//===================================================================

double PID_GetOutput(){
return Output;
}

void PID_SetInput(double input){
Input = input;
}

void PID_SetPoint(double setpoint){
	Setpoint = setpoint;
}



//===================================================================
//		Configurando un timer para hacer de contador				/
/*
ISR(TCD0_OVF_vect){
	millis++;
}
*/

//===================================================================
//		Esta funcion es un Filtro PasaBajos							/
//===================================================================

// Variables Para el Filtro Pasa Bajos
float alpha = 0.1;
float previousOutput = 0;

float PID_LowPassFilter(float input){
	
	float output = alpha * input + (1-alpha) * previousOutput;
	previousOutput = output;
	
	return output;
}



void PID_Control_Potencia(){
	//esta funcion realiza un calculo de potencia teniendo como dato variable el Vdir
	//y dando asi su valor en porcentaje
	if(PTT_Estado==PTT_ON){
		if(Banderas.RF_Activa){	//solo comienza a trabajar cuando detecta que hay RF
			
			//========================================================
			PORTA.DIRSET = PIN1_bm; //esto es para saber el tiempo de respuesta del PID
			PORTA.OUTSET = PIN1_bm;	//quitar solo prueba
			//========================================================
			
			PID_SetInput(Potencia.promedio1_200);
			
			switch(Potencia_Porcentaje){
				case PORCENTAJE_30:
				//le impongo limites de +-5W
				PID_SetOutputLimits((POTENCIA_30_PORCIENTO - 0.005),(POTENCIA_30_PORCIENTO + 0.005));
				//declaro la potencia que quiero que se mantenga
				PID_SetPoint(POTENCIA_30_PORCIENTO);
				//se realiza un calculo para buscar los coeficientes de (ki,kp,kd)
				PID_AutoTunings();
				//se realiza el calculo del PID
				PID_Compute();
				//le mando a la salida del DAC el voltaje que calculo anteriormente
				//DAC_Ganancia(((61.012486*pow(PID_GetOutput(), 0.428139))/1000)-0.064);
				DAC_Ganancia(PID_GetOutput());
				break;
				
				case PORCENTAJE_60:
				PID_SetOutputLimits((POTENCIA_60_PORCIENTO - 0.005),(POTENCIA_60_PORCIENTO + 0.005));
				PID_SetPoint(POTENCIA_60_PORCIENTO);
				PID_AutoTunings();
				PID_Compute();
				//DAC_Ganancia(((61.012486*pow(PID_GetOutput(), 0.428139))/1000)-0.09);
				DAC_Ganancia(PID_GetOutput());
				break;
				
				case PORCENTAJE_100:
				PID_SetOutputLimits((POTENCIA_100_PORCIENTO - 0.005),(POTENCIA_100_PORCIENTO - 0.005));
				PID_SetPoint(POTENCIA_100_PORCIENTO);
				PID_AutoTunings();
				PID_Compute();
				//DAC_Ganancia(((61.012486*pow(PID_GetOutput(), 0.428139))/1000)-0.114);
				DAC_Ganancia(PID_GetOutput());
				break;
			}//fin del switch
			
			PORTA.OUTCLR = PIN1_bm;	//con esto termino la respuesta del pid--quitar solo prueba
		}//fin del 2do if
	}//fin del 1er if
}


