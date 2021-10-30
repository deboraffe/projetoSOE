#ifndef _TEMPERATURA_H_
#define _TEMPERATURA_H_

#include <stdio.h>
#define BCM2835_NO_DELAY_COMPATIBILITY 
#include <bcm2835.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

#define N 1   // médias de amostras

double temperatura();

#endif  // _TEMPERATURA_H_