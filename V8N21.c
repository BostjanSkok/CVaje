#include <sys/stat.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>

int const N_THR = 10;
double Ns = 0;
double Zs = 0;
double const  e = 0.001;

int const N = 10000; //Poskusi