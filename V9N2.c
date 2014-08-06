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

int const PrintSize = 512;
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
    int n = 1;
    while ((n = read(connfd, buff  , sizeof(buff))) > 0)
    {

        int var1 = atoi(strtok(buff, " "));
        printf("Read1 %i\n", var1 );

        char *op =  strtok(NULL, " ");
        printf("Read2 %s\n", op);

        int var2 = atoi(strtok(NULL, " "));
        printf("Read3 %i\n", var2);

        int res = 0 ;

        switch (op[0])
        {
        case '+':
            res = var1 + var2;
            break;
        case '-':
            res = var1 - var2;
            break;
        case '*':
            res = var1 * var2;
            break;
        case '/':
            if (var2 += 0)
                res = var1 / var2;
            else
                res = -1;
            break;
        }

        snprintf(buff, sizeof(buff) - 1, "%i", res);

        //printf("Read %i\n", n );
        if ( write(connfd, &res, sizeof(res)) < 0 )
            perror("write error");

        //printf("Read %i\n", n );

        // printf("%s\n", recvBuff );
        /*if (fputs(recvBuff, stdout) == EOF)
        {
            perror("\n Error : Fputs error\n");
        }*/
    }




    if ( close(connfd) < 0)
        perror("close error");
}
