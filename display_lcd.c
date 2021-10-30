#include "display_lcd.h"

void display_lcd(double temp_media, double limite,int modo)
{
    int lcd;               
    wiringPiSetup();        
    lcd = lcdInit (2, 16, 4, LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7, 0, 0, 0, 0);  // modo de inicialização do LCD 2 linhas 16 colunas modo de 4 bits
	
	if(modo==0)
	{
	   if(temp_media<limite) //( acrescentar condição da máscara)
	   {	
           lcdPosition(lcd,0,0);                // posiciona texto na linha 0 e a parti da coluna 1           
           lcdPuts(lcd, "Acesso Liberado!");    //imprime acesso liberado quando a pessoa está com temperatura normal
	   }else
	    {
           lcdPosition(lcd,0,0);                // posiciona texto na linha 0 e a parti da coluna 1           
	       lcdPuts(lcd, "Acesso Negado!");      // imprime acesso negado quando a pessoa está com temperatura febril
	    }
	  
	    lcdPosition(lcd,0,1);                   // posiciona texto na linha 0 e a parti da coluna 1  
        lcdPrintf(lcd, "Temp: %.2f C",temp_media);	
	  
	}else // modo == 1 modo de configuração
	 {
	      lcdPosition(lcd,5,0);                 // posiciona texto na linha 0 e a parti da coluna 1           
          lcdPuts(lcd, "AJUSTE!");              //imprime acesso liberado quando a pessoa está com temperatura normal
	      lcdPosition(lcd,0,1);                 // posiciona texto na linha 0 e a parti da coluna 1  
          lcdPrintf(lcd, "Temp: %.2f C",limite);	
	 }
		
}