#include "ftp.h"
    
void send_cmd_fork(int sockfd)
{
    char buff[BUFFSIZE];
    int len;
    pid_t pid;
    while( 1 )
    {
        memset(buff,'\0',BUFFSIZE);
        printf("ftp>>");
        fgets(buff,BUFFSIZE,stdin);
        if( strncmp(buff,"get",3) == 0 )
        {
            len = send(sockfd,buff,strlen(buff) - 1,0);
            if( len < 0 )
            {
                perror("client: send err\n");
                exit(EXIT_FAILURE);
            }
            if( (pid = fork()) == 0 )
            {
                create_file(sockfd);
            }
            else
            {
                wait();
            }
        }
        if( strncmp(buff,"ls",2) == 0 || strncmp(buff,"cat",3) == 0 )
        {
            len = send(sockfd,buff,strlen(buff) - 1,0);
            if( len < 0 )
            {
                perror("client: send err\n");
                exit(EXIT_FAILURE);
            }
            if( (pid = fork()) == 0 )
            {
                recv_cmd_fork(sockfd);
            }
            else
            {
                wait();
            }
        }
        if(  strncmp(buff,"quit",4) == 0 )
        {
            printf("i  will  quit\n");
            break;
        }
    }
}
