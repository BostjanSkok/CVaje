#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

const int MaxArgs = 10;
const int MaxLine = 128;
//int used=0;
void PrintTable(char *args[])
{
    for (int i = 0; i < MaxArgs; i++)
    {
        printf("print i %i\n", i );
        if (args[i] == NULL)
            return;
        printf("%s\n", args[i] );
    }
}


int main(int argc, char const *argv[])
{


    int status;

    char *args[MaxArgs];
    char *seps   = ",";
    char *token;
    int n;
    int pid = -1;
    char  command[MaxLine];

    while ((n = read(0, command, MaxLine)) > 0)
    {
        int i = 0;
        // printf("%s\n",command );

        for (int i = 0; i < MaxLine; i++)
        {
            if (command[i] == '\n')
            {
                command[i] = '\0';
                break;
            }
            if (command[i] == ' ')
                command[i] = '\0,';
        }
        token = strtok( command, seps);
        // printf("c2 %s\n",command );
        while ( token != NULL && i < (MaxArgs - 1))
        {

            // strncpy(str, token, sizeof(tokens));
            // printf( "token: %i\n", sizeof(token));
           // printf( "token: %s\n", token );

            args[i] = token;
            // args[i] = token;
            i++;


            // printf( "token: %s\n", token );
            token = strtok( NULL, seps );
           // printf("next token %s\n",token );
        }
        args[i] = NULL;
        //args[i] = '\0';
        // PrintTable(args);
        pid = fork();
        if (pid == 0)
        {
         //   printf("args[0] %s\n", args[0]);
         //   printf("args[1] %s\n", args[1]);
        //    printf("args[2] %s\n", args[2]);
//

            if (execvp(args[0], args) == -1)
                // if(execl("/bin/ls", "ls", NULL)==-1)
                perror("Execvp returned ");
            //printf("Execvp returned: %i\n",errno);
            //exit(0);
        }
        else
        {
            waitpid(pid, NULL, 0);
        }



        /*     pid = fork();
              if (pid == 0)
              {
                  execv(".", command);
                  exit(0);
              }
        */


    }


    return 0;
}