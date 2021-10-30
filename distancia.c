#include "distancia.h"

float distancia()
{
   float dist_cm;             //Variável que armazena o valor da distância em centímetros
  
   wiringPiSetup();         // inicializa wiringPi
   pinMode(TRIG, OUTPUT);   //Pino de trigger será saída digital
   pinMode(ECHO, INPUT);    //Pino de echo será entrada digital
  
   digitalWrite(TRIG, LOW); //Saída trigger inicia em nível baixo
  
   //GERA PULSO DE 10ms do TRIGER
  
   digitalWrite(TRIG, HIGH);  //Pulso de trigger em nível alto
   delayMicroseconds(10);     //duração de 10 micro segundos
   digitalWrite(TRIG, LOW);   //Pulso de trigge em nível baixo
	
	 
   while(digitalRead(ECHO) == LOW);         //Espera inicio do ECHO (ele sair de nivel lógico baixo) 
	  
   //OBTEM A DURAÇÃO DO PULSO DE ECHO
   float startTime = micros();              // pega tempo atual
   while(digitalRead(ECHO) == HIGH);        // fica aqui enquanto o pulso do echo estiver em 1
   float temp_pulse = micros() - startTime; // calcula duração do pulso em nível 1 alto
	 
   dist_cm = temp_pulse/58.82;              //Valor da distância em centímetros
  
  /* 340m/s                                // velocidade do som
     34000cm/s 
  
     100000 us - 17000 cm/s   -- 34000/2 por causa da ida e da volta da distancia percorrida
          x us - 1cm
			 
           1E6
      x = -----
          17E3
  */
  
    return dist_cm;
}