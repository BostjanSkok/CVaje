#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>



const int MaxLine = 128;
struct message
{
    long type;
    char text[MaxLine];
} msg;

int main(int argc, char const *argv[])
{
    int  qId;


    if ( (qId = msgget(ftok("/tmp", 'i') , 0644 | IPC_CREAT )) == -1)
    {
        perror("can't create que");
        exit(EXIT_FAILURE);
    }



    char  command[MaxLine];
    while ()
    {
        msg.type = 1;
        strcpy(msg.text, command);
        msgsnd( qId, (void *) &msg, sizeof(msg.text), IPC_NOWAIT);
        //printf("%s\n", "sent");
    }
    msgctl(qId, IPC_RMID, 0);

    exit(EXIT_SUCCESS);



}