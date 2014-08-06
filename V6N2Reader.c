#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <string.h>
#include <sys/wait.h>

#define PERMS 0666
#define FIFO1 "./fifo.1"
extern int errno;
const int MaxLine = 128;


int main(int argc, char const *argv[])
{
    int readfd;


    if ( (mkfifo(FIFO1, S_IFIFO | 0666) < 0) && (errno != EEXIST))
    {
        perror("can't create fifo 1");
        exit(EXIT_FAILURE);
    }


    readfd = open(FIFO1, O_RDONLY);
    if ( readfd < 0)
    {
        perror("can't open write fifo");
        exit(EXIT_FAILURE);
    }
    char  command[MaxLine];
    int e=-2;
    while (e!=0)
    {
        e = read(readfd,&command,MaxLine);

        if(e==0)
            break;
        printf("%s\n",command );

    }
    close(readfd);
    unlink(FIFO1);
    exit(EXIT_SUCCESS);


    
}