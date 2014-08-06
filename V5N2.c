#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

int sigR = 0;
void signalC(int arg)
{
    printf("%s\n", "signal recived" );
    sigR = 1;
}
int main(int argc, char const *argv[])
{
	printf("%s\n","Lovim signal SIGINT ..." );
    signal(SIGINT, signalC);
    sleep(3);
    if (sigR == 0)
        printf("%s\n", "Ni bilo signala SIGINT v zadnjih 3 sekundah." );
    printf("%s\n", "Naslednje 3 sekunde ignoriram signal SIGINT ..." );
    signal(SIGINT, SIG_IGN);
    sleep(3);
    printf("%s\n", "Privzeta funkcija za SIGINT ..." );
    signal(SIGINT, SIG_DFL);
    sleep(3);

    printf("%s\n", "Ni bilo signala SIGINT v zadnjih 3 sekundah, zakljucujem." );

    return 0;
}