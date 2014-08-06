#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <stdlib.h>
#include <stdio.h>

union semun
{
    int val;
    struct semid_ds *buf;
    ushort *array;
} argument;


int main(int argc, char const *argv[])
{
    int semId;


    argument.val = 1;

    if ( (semId = semget(ftok("/tmp", 's'), 1, 0664 | IPC_CREAT)) == -1)
    {
        perror("napaka pri ustvarjanju semaforja");
        exit(EXIT_FAILURE);
    }

    if ( (semId = semctl(semId, 0, SETVAL, argument)) == -1)
    {
        perror("napaka pri semctl");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);


}