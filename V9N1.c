#include <sys/stat.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <sys/errno.h>
#include <sys/errno.h>
#include <sys/errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define SA struct sockaddr

int const PrintSize = 10;
int const Port = 9876;



int main(int argc, char const *argv[])
{
    int sockfd, connfd;
    struct sockaddr_in servaddr;
    char buff[PrintSize];
    // char buff;

    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        perror("socket error");
    int yes = 1;
    if ( setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1 )
    {
        perror("setsockopt");
    }


    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(Port);
    if ( bind(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0)
        perror("bind error");

    if (listen(sockfd, SOMAXCONN) < 0)
        perror("listen error");


    // Wait for connection
    // while (connfd == -1)
    //  {
    if ( (connfd = accept(sockfd, (SA *) NULL, NULL)) < 0)
    {
        if (errno != ECONNABORTED)
        {
            perror("accept error");
            printf("%i\n", errno);
            exit(1);
        }
    }
    // }
    //printf("%i\n", connfd);
    int i=1;
    for ( i = 1; i < 6; ++i)
    {
        snprintf(buff, sizeof(buff) - 1, "%i", i);
        if ( write(connfd, buff, strlen(buff) + 1) <0)
            perror("write error");
        sleep(1);

    }




    if ( close(connfd) < 0)
        perror("close error");
}
