#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>


int main(int argc, char **argv)
{

    if (argc != 2)
    {
        fprintf(stderr, "Not enough params\n");
        exit(EXIT_FAILURE);
    }

    char *sourceFile = argv[1];

    int sFd; //source file

    sFd = open(sourceFile, O_RDONLY);
    if (sFd == -1) //open readonly
    {
        perror("open sourceFile");
        exit(EXIT_FAILURE);
    }



    char ReadChar [128];

    if (read(sFd, &ReadChar,128 ) == -1)
    {
        perror("Read next char from source");
        exit(EXIT_FAILURE);
    }
    printf(" rez %s\n", ReadChar);


    close(sFd);


    exit(EXIT_SUCCESS);

}