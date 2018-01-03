#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFSIZE 1024 

int main(int argc,char * argv[])
{
    struct sockaddr_in my_addr,their_addr;
    int sockfd,newfd;
    int len;
    pid_t pid;
    unsigned int port,listnum = 5;//端口号 服务器最大连接数
    char buff[BUFFSIZE];

    if( (sockfd = socket(AF_INET,SOCK_STREAM,0)) == -1 )//创建socket
    {
        perror("socket err\n");
        exit(EXIT_FAILURE);
    }
    
    memset(&my_addr,'\0',sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(atoi(argv[2]));//绑定端口号
    my_addr.sin_addr.s_addr = inet_addr(argv[1]);//绑定本地IP地址

    if ( bind(sockfd,(struct sockaddr *)& my_addr,sizeof(struct sockaddr)) == -1 )//进行绑定 
    {
        perror("bind  err\n");
        exit(EXIT_FAILURE);
    }

    if( listen(sockfd,listnum) == -1 )//监听网络
    {
        perror("listen err\n");
        exit(EXIT_FAILURE);
    }
    printf("wait for connect\n");
    len = sizeof(struct sockaddr);
    if( (newfd = accept(sockfd,(struct sockaddr*)&their_addr,&len)) == -1 )//在此阻塞，等待接受请求端请求
    {
        perror("accept err\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("accept success\n");
    }

    if(  (pid = fork()) < 0  )
    {
        perror("accept err\n");
        exit(EXIT_FAILURE);
    }
    else if( 0 == pid  )//创建子线程，用于数据发送
    {
        while( 1 )
        {
            memset(buff,'\0',BUFFSIZE);
            fgets(buff,BUFFSIZE,stdin);
            if( strncmp(buff,"quit",4) == 0 )
            {
                printf("i  will quit\n");
                break;
            }

            len = send(newfd,buff,strlen(buff),0);

            if( len < 0 )
            {
                printf("server : send err\n");
                break;
            }
            else if ( len == 0 )
            {
                break;
            }
        }
    }
    else
    {
        while( 1 )
        {
            memset(buff,'\0',BUFFSIZE);
            len = recv(newfd,buff,BUFFSIZE,0);
            printf("dfghjkl");
            if( len < 0 )
            {
                perror("recv err\n");
                exit(EXIT_FAILURE);
            }
            else if( 0 == len )
            {
                printf("the other one close input\n");
                break;
            }
            else
            {
                printf("recv message : %s\n",buff);
            }
        }
    }
    return 0;
}
    
