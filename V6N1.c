#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    int fd[2];
    char buf[512];
    if (pipe(fd) == -1)
    {
        perror("pipe call error");
        exit(EXIT_FAILURE);
    }
    pid_t pid = fork();
    if (pid == 0)
    {
        char *cmd[] = { "grep", "student", (char *)0 };
        if (close(fd[1]) < 0)
        {
            perror("Otrok:");
            exit(EXIT_FAILURE);

        }
        if (dup2(fd[0], 0) == -1)
        {
            perror("Otrok:");
            exit(EXIT_FAILURE);

        }
        execv ("/bin/grep", cmd);
        perror("Otrok:");
        exit(EXIT_FAILURE);

        // n = read(fd[0], buf, 512);
        //printf("Otrok: %s", buf);
        return (1);
    }
    else
    {
        char *cmd[] = { "ps", "-ef", (char *)0 };

        if (close(fd[0]) < 0)
        {
            perror("Mati:");
            exit(EXIT_FAILURE);

        }
        //write(fd[1], "Hej, mali!\n", 512);

        if (dup2(fd[1], 1) == -1)
        {
            perror("Otrok:");
            exit(EXIT_FAILURE);

        }
        execv ("/bin/ps", cmd);
        perror("m");
        exit(EXIT_FAILURE);


        wait(NULL);
        exit(EXIT_SUCCESS);
    }

    return 0;
}