#include "temperatura.h"

double temperatura()
{
    unsigned char buf[6];                                           // buffer para bits de temperatura
    unsigned char i,reg;
    double temp=0,calc=0, temp_corporal;
	double temp_superficie = 0, temp_media;                         // temperatura da superfície da pele
	
    bcm2835_init();                                                 // inicialização do BCM2835
    bcm2835_i2c_begin();                                            // inicialização da comunicação I2C
    bcm2835_i2c_set_baudrate(25000);                                // taxa de comunicação de 25000 bits/segundo
  
	
    bcm2835_i2c_setSlaveAddress(0x5a);                              // selecionando o endereço do escravo MLX90614
 
    calc=0;
    reg=0x07;                                                       // endereço 0x07 da memória RAM referente a temperatura do corpo Tobj1
 
 // MEDIÇÃO DA TEMPERATURA DO CORPO
 
    for(i=0;i<N;i++)
	{
        bcm2835_i2c_begin();                                        // inicializa comunicação I2C
        bcm2835_i2c_write (&reg, 1);                                // indica o endereço na qual vai se comunicar
        bcm2835_i2c_read_register_rs(&reg,&buf[0],3);               // pega o valor do registrador e salva em buf o registrador que fornece a temperatura é de 16bits
        temp_superficie = (double) (((buf[1]) << 8) + buf[0]);      // desloca 8 bits para a esquerda e junta com buf[0] 16 bits
        temp_superficie = (temp_superficie * 0.02)-0.3;            // ele pega o resultado da RAM e converte para temperatura Kelvin
        temp_superficie = temp_superficie - 273.15;                 // converte a temperatura para celsius
		
	    //CALIBRAÇÃO DO SENSOR
	    temp_corporal = (0.0974*(temp_superficie*temp_superficie)) - (6.038*temp_superficie) + 129.07; 
		
        calc+=temp_corporal;                                        // acumula os valores da temperatura
		//delayMicroseconds(300000);                                  // tempo de amostragem de temperatura 300ms
    }
 
    temp_media=calc/N;                                              // média das N temperaturas medidas
    calc=0;
	
    return temp_media;
}
