#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <stdlib.h>
#include <stdio.h>



int main(int argc, char const *argv[])
{
    int semId;
    struct sembuf sops[1];
    sops[0].sem_num = 0;        /* Operate on semaphore 0 */
    sops[0].sem_op = -1;         /* Wait for value to equal 0 */
    sops[0].sem_flg = 0;


    if ( (semId = semget(ftok("/tmp", 's'), 1, 0)) == -1)
    {
        perror("napaka pri povezovanju na semafor");
        exit(EXIT_FAILURE);
    }
    if (semop(semId, sops, 1) == -1)
    {
        perror("semop");
        exit(EXIT_FAILURE);
    }

    printf("%s\n", "got semafor" );
    getchar();

    sops[0].sem_op = 1;
    if (semop(semId, sops, 1) == -1)
    {
        perror("semop");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);

}