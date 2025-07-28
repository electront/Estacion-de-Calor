/*
 * PID.h
 *
 * Created: 12/11/2024 19:28:44
 *  Author: Alvaro
 */ 


//Sistema de control PID

#ifndef PID_H_
#define PID_H_

#include <stdlib.h>
#include "../POTENCIA/POTENCIA.h"
#include "../PTT/PTT.h"
#include "../BANDERAS/BANDERAS.h"
#include "../ADC/ADC.h"


void PID_Compute();
void PID_SetTunings(double Kp, double Ki, double Kd);
void PID_AutoTunings();
void PID_SetSampleTime(int NewSampleTime);
void PID_SetOutputLimits(double Min, double Max);
void PID_Initialize();
void PID_SetMode(int Mode);
void PID_SetControllerDirection(int Direction);

void PID_Control_Potencia();

void PID_TimerPID();
float PID_LowPassFilter(float input);


double PID_GetOutput();
void PID_SetInput(double input);
void PID_SetPoint(double setpoint);


#endif /* PID_H_ */