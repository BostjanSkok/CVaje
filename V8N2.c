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
double const  e = 0.0001;

int const N = 100; //Poskusi

pthread_mutex_t lock ;//= PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t pogoj ;//= PTHREAD_COND_INITIALIZER;

int piFound = 0;

void *funkcija_niti(void *arg)
{
    int n = 0;
    int z = 0;
    double piP = 0;

    while (1)
    {
        int i;
        for ( i = 0; i < N; ++i)
        {
            double x = ((double) rand()) / RAND_MAX;
            double y = ((double) rand()) / RAND_MAX;
            if ((pow(x, 2) + pow(y, 2)) <= 1)
                z++;
            n++;
        }



        pthread_mutex_lock(&lock);
        if (piFound == 1)
        {
            pthread_mutex_unlock(&lock);
            pthread_exit(NULL);

        }
        Ns += n;
        Zs += z;
        piP = (4 * Zs) / Ns;
        if ( piFound == 0 && fabs(M_PI - piP) <= e)
        {
            piFound = 1;
            printf("Pi found \n");
            fflush(0);
            pthread_cond_signal(&pogoj);
            pthread_mutex_unlock(&lock);
            pthread_exit(NULL);
        }
        pthread_mutex_unlock(&lock);

    }
pthread_exit(NULL);

}

void *funkcija_B(void *arg)
{
    pthread_mutex_lock(&lock);
    pthread_cond_wait(&pogoj, &lock);
    printf("B wakes up \n");
    printf("%f\n", (4 * Zs) / Ns);
    pthread_mutex_unlock(&lock);

    pthread_exit(NULL);

}

int main(int argc, char const *argv[])
{
    srand(time(NULL));

    /* if (pthread_cond_init(&barrierCount, NULL) != 0)
     {
         perror("pthread_cond_init() error");
         exit(1);
     }
     if (pthread_cond_init(&bbc, NULL) != 0)
     {
         perror("pthread_cond_init() error");
         exit(1);
     }*/
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&pogoj, NULL);
    pthread_t A[N_THR];
    pthread_t B;
    int i;
    int ret;

    ret = pthread_create(&B, NULL, funkcija_B, (void *)0);
    if (ret)
    {
        printf("Napaka (%d)\n", ret);
        exit(1);
    }


    for ( i = 0; i < N_THR; i++)
    {
        ret = pthread_create(&A[i], NULL, funkcija_niti, (void *)i);
        if (ret)
        {
            printf("Napaka (%d)\n", ret);
            exit(1);
        }



    }

    ret = pthread_create(&B, NULL, funkcija_B, (void *)0);
    if (ret)
    {
        printf("Napaka (%d)\n", ret);
        exit(1);
    }

    pthread_join(B, NULL);
    printf("Thread B returned \n");
    for ( i = 0; i < N_THR; ++i)
    {
        pthread_join(A[i], NULL);
        printf("Thread A[%i] returned \n", i);
        fflush(0);

    }
    //printf("Caki B");

    pthread_join(B, NULL);
    printf("Thread B returned \n");

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&pogoj);


}

