#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/shm.h>
#include <sys/fcntl.h>
#include <unistd.h>



const int MaxLine = 128;


int main(int argc, char const *argv[])
{
    int smId;
    char buff[MaxLine];
     void* smOut;

    if ( (smId = shmget(ftok("/tmp", 's'), sizeof(buff), 0644 | IPC_CREAT)) == -1)
    {
        perror("napaka pri povezovanju na skupen pomninik");
        exit(EXIT_FAILURE);
    }
    if ((smOut=shmat(smId, NULL, 0)) == -1)
    {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

     printf("%s\n",(char*)smOut);

 
  if(shmdt(smOut)<1)
  {
       perror("ReadError");
        exit(EXIT_FAILURE);
  }
    exit(EXIT_SUCCESS);
}