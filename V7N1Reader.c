#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <string.h>
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



    int e = -1;
    while (e != 0)
    {
        if (msgrcv( qId, (void *) &msg, sizeof(msg.text), 0, 0) <= 0)
        {
            perror("msgrcv error");
            exit(EXIT_FAILURE);
        }
        // printf("%i\n",e);


        printf("%s\n", msg.text );

    }
    exit(EXIT_SUCCESS);



}