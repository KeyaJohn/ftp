#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "ftp.h"
#define BUFFSIZE 1024 

int main(int argc ,char * argv[])
{
    struct sockaddr_in dest;
    pid_t pid ;
    int sockfd,len;
    char buff[BUFFSIZE];

    if( argc != 3 )
    {
        perror("argument err\n");
        exit(EXIT_FAILURE);
    }

    if( (sockfd = socket(AF_INET,SOCK_STREAM,0)) == -1 )
    {
        perror("socket  err\n");
        exit(EXIT_FAILURE);
    }
    printf("socket  create success\n");

    memset(&dest,'\0',sizeof(dest));
    dest.sin_family = AF_INET;
    dest.sin_addr.s_addr =inet_addr(argv[1]);
    dest.sin_port = htons(atoi(argv[2]));

    if( connect(sockfd,(struct sockaddr*)&dest,sizeof(dest)) == -1 )
    {
        perror("connetc  err\n");
        exit(EXIT_FAILURE);
    }
    printf("connect success\n");
    int j=0;
    while( 1 )
    {
        if( j == 4 )
        {
            printf("login num too much,quit\n");
            exit(1);
        }
       if( login(sockfd) )
       {
           break;
       }
       j++;
    }

/*    if( (pid = fork()) < 0  )
    {
        perror("fork  err\n");
        exit(EXIT_FAILURE);
    }
    else if( 0 == pid )
    {   
        recv_cmd_fork(sockfd);
    }
    else*/
    {
        send_cmd_fork(sockfd);
    }
    
    return 0;
}
