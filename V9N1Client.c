#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

int const PrintSize = 512;
int const Port = 9876;


int main(int argc, char *argv[])
{
    int sockfd = 0, n = 0;
    //char recvBuff[PrintSize];
    char recvBuff[PrintSize];


    struct sockaddr_in servaddr;




    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("\n Error : Could not create socket \n");
        exit(1);
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(Port);



    if ( connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("\n Error : Connect Failed \n");
        exit(1);
    }

    while ((n = read(sockfd, recvBuff  , sizeof(recvBuff))) >0)
    {
        printf("Read %i\n", n );
        printf("%s\n", recvBuff );
      //  sleep(10);

        /*if (fputs(recvBuff, stdout) == EOF)
        {
            perror("\n Error : Fputs error\n");
        }*/
    }
    printf("Read %i\n", n );


    if ( close(sockfd) < 0)
        perror("close error");
    exit(0);
}