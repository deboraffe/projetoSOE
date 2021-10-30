
#include <pthread.h>
#include "distancia.h"
#include "temperatura.h"
#include "display_lcd.h"
#include <wiringPi.h>         


// botões para escolha de temperatura limite por interrupção
// Numeração da WiringPI

#define btn_verde    6             // pino 22 GPIO 25
#define btn_vermelho 27            // pino 36 GPIO 16

//Protótipos de funções
void incrementa_limite();             // incrementa limite de temperatura do sistema
void decrementa_limite();             // decrementa limite de temperatura do sistema
void arquivo_temperatura(double temp);// cria arquivo para escrever o valor da temperatura
void* envio_email();                  // thread para envio do e-mail
 

double valor_temp = 0;       // variável global para temperatura 
double limite_temp = 36.5;   // limite de temperatura para ser considerado com febre
//int modo = 0;              // alteração do modo  "0" -> mensagem "1" -> configuração limite de temperatura
int sem_mascara = 0;

int main()
{	
	wiringPiSetup();                                               // inicializando a wiringPi
	pinMode(btn_verde, INPUT);                                     // botão verde (incrementa)/e entrada digital
	pinMode(btn_vermelho, INPUT);                                  // botão vermelho
	wiringPiISR(btn_verde,INT_EDGE_RISING, &incrementa_limite);    // interrupção icrementa valor limite para a temperatura para que comparar com a temperatura corporal
	wiringPiISR(btn_vermelho,INT_EDGE_RISING, &decrementa_limite); // interrupção decrementa valor limite para a temperatura para que comparar com a temperatura corporal
	
	pthread_t thread_id1;                                          // cria um indentificador para a thread
	pthread_t thread_id2;                                          // cria um indentificador para a thread
	pthread_create(&thread_id1, NULL, &envio_email, NULL);         // cria a thread que executara em paralelo a função envio_email
	pthread_create(&thread_id1, NULL, &envio_email, NULL);         // cria a thread que executara em paralelo a função envio_email
	while(1)
	{
		
	  if((distancia()) <= 3.5)                  // se a distância do pulso da pessoa estiver proximo ao sensor mlx90614
	  {
		
		valor_temp = temperatura();                          // retorna o valor da temperatura
		sem_mascara = display_lcd(valor_temp,limite_temp,0); //mostrar temperatura no display
		system("sudo ./detec_hc");                          //Verifica se a pessoa está sem máscara
		//delayMicroseconds(100000);                       // tempo de amostragem de temperatura 100ms
	  }
	  else
	  {
	    printf("pulso nao detectado\n");
	  }
	  
	  delayMicroseconds(1000000);             // taxa de atualização de 1 segundos para verificar a distância do pulso
	}
	
 return 0;
}


void arquivo_temperatura(double temp)                             // cria arquivo para escrever o valor da temperatura
{
  char string[30] = {'\0'};                                       // variável para armazenar a temperatura no formato string
  
  int fd = open("temperatura.txt", O_WRONLY | O_CREAT, S_IRWXU); // abre o arquivo como escrita e leitura e cria ele caso não exista
 
	if(fd==-1)
	{
		exit(-1);                                // erro na abertura do arquivo
	}
	
    sprintf(string,"Temperatura = %.2fC\n",temp);// escreve em string o texto no formato indicado
	
	
	for(int i=0; string[i] != '\0'; i++)
	{
	   write(fd, &(string[i]), 1);              // escreve caracter por caracter no arquivo.
	}
	
	close(fd);                                  // fecha arquivo
}

void incrementa_limite()
{
  limite_temp+=0.5;
  
  if(limite_temp>37.5)
  {
    limite_temp = 37.5;
  }
  
  display_lcd(0,limite_temp,1);         //mostrar temperatura limite no display
  while(digitalRead(btn_verde)== HIGH); // espera o botão ser solto

}

void decrementa_limite()
{
  limite_temp-=0.5;
  
  if(limite_temp<35.5)
  {
    limite_temp = 35.5;
  }
  display_lcd(0,limite_temp,1);            //mostrar temperatura limite no display
  while(digitalRead(btn_vermelho)== HIGH); // espera o botão ser solto
}

void* envio_email()                    // thread que executa em paralelo com a main para envio de e-mail
{
  while(1)
  { 
    //delayMicroseconds(100000);           // tempo de amostragem de temperatura 100ms
    if(valor_temp>=limite_temp | sem_mascara==1)         
    {
      system("raspistill -q 100 -o foto.jpg");
      arquivo_temperatura(valor_temp);// coloca o valor de temperatura dentro de um arquivo txt
      system("./email_anexo.sh");     //executa comando do terminal para enviar e-mail 
      valor_temp= 0;
      limite_temp=36.5;
      sem_mascara=0;
    }
  }
    return NULL;
}
