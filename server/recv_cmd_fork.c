#include "ftp.h"

void  send_login(int sockfd)
{
    int len;
    char buff[40];
    setbuf(stdout,NULL);
    recv(sockfd,buff,40,0) ;
    if( strncmp(buff,"kaye",4) == 0 )
    {
        send(sockfd,"ok",2,0);
        recv(sockfd,buff,sizeof(buff),0) ;
        printf("login message:%s byte: %d\n",buff,len);
        if( strncmp(buff,"jingtikai",9) == 0 )
        {
            send(sockfd,"ok",2,0);
        }
        else
        {
            send(sockfd,"fail",4,0);
            return ;
        }
    }
    else
    {
        send(sockfd,"fail",4,0);
        return ;
    }
}

void recv_cmd_fork(int sockfd)
{   
    char buff[BUFFSIZE];
    int len ;
    pid_t pid;
    while( 1 )
    {
        memset(buff,'\0',BUFFSIZE);
        len = recv(sockfd,buff,BUFFSIZE,0);
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
            printf("recv message:%s byte: %d\n",buff,len);
            
            if( strncmp(buff,"ls",2) == 0 )
            {
                send_cmd_fork(sockfd,buff);//没有考虑到遇到前面空格的情况 后期需要维护
            }
            else if (strncmp(buff,"get",3) == 0 )
            {
                send_cmd_fork(sockfd,buff);//传数组，一般形式都是 get filename 来获得文件其中有空格分离 需要整体
            }
            else if( strncmp( buff,"cat",3) == 0 )
            {
                send_cmd_fork(sockfd,buff);
            }
            else if( strncmp(buff,"quit",4) == 0 )
            {
                break;
            }
            else if( strncmp(buff,"name",4) == 0 )
            {
                send_login(sockfd);
            }
            else
            {
                printf("%s:command not found\n",buff);
                continue;
            }
        }
    }
}
