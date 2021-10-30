#ifndef _DISPLAY_LCD_H_
#define _DISPLAY_LCD_H_

#include <wiringPi.h>         
#include <lcd.h> 

// NUMERAÇÃO PINOS WIRINGPI
#define LCD_RS  25               //Register select pin (RS) GPIO 37
#define LCD_E   24               //Enable Pin               GPIO 35
#define LCD_D4  23               //Pino de dados 4          GPIO 33
#define LCD_D5  22               //Pino de dados 5          GPIO 31
#define LCD_D6  21               //Pino de dados 6          GPIO 29
#define LCD_D7  14               //Pino de dados 7          GPIO 23


void display_lcd(double temp_media, double limite,int modo);

#endif  // _DISPLAY_LCD_H_
