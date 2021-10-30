all: main.o temperatura.o distancia.o display_lcd.o
	gcc $(CFLAGS) -o main main.o temperatura.o distancia.o display_lcd.o -lwiringPi -lwiringPiDev -l bcm2835 -lpthread
main.o: main.c temperatura.h distancia.h display_lcd.h
	gcc $(CFLAGS) -c main.c -lwiringPi -lwiringPiDev -l bcm2835 -lpthread
temperatura.o: temperatura.c temperatura.h
	gcc $(CFLAGS) -c temperatura.c -l bcm2835 
distancia.o: distancia.c distancia.h
	gcc $(CFLAGS) -c distancia.c -lwiringPi -lwiringPiDev
display_lcd.o: display_lcd.c display_lcd.h
	gcc $(CFLAGS) -c display_lcd.c -lwiringPi -lwiringPiDev
clean:
	rm -f *.out *.o *.bin *.txt *.html
