#ifndef _DISTANCIA_H_
#define _DISTANCIA_H_

#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <time.h>

// Pinos da wiringPi

#define TRIG 5   //Pino x será a saída de trigger GPIO 18       
#define ECHO 4   //Pino x será a entrada de echo  GPIO 16

float distancia();         // função para medir distância
#endif  // _DISTANCIA_H_