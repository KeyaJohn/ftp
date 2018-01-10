#include "ftp.h"

void create_file(int sockfd)
{
    int len;
    FILE * fp = NULL;
    char str[BUFFSIZE];
    char filename[30] ;
    memset(filename,'\0',30);

    recv(sockfd,filename,30,0);
    printf("recv filenem：%s\n",filename);
    if( ( fp = fopen(filename,"wa") ) ==  NULL )
    {
        perror("client : open file fail!\n");
        exit(EXIT_FAILURE);
    }
    while( 1 )
    {
        len = recv(sockfd,str,BUFFSIZE,0);
        if( strncmp(str,"quit",4) == 0 )
        {
            printf("recv file successfilly!\n");
            exit(EXIT_SUCCESS);
        }
        fputs(str,fp);
        if( len < 0 )
        {
            perror("client :recv err\n");
            exit(EXIT_FAILURE);
        }
        if( len == 0 )
        {
            break;
        }
        memset(str,'\0',BUFFSIZE);
    }
}
void recv_cmd_fork(int sockfd)
{
    char buff[BUFFSIZE];
    int len;
    pid_t pid;
    setbuf(stdout,NULL);
    unsigned int count = 0 ;

    FILE *fp;
    int  nZero = 1;
    //  setsockopt(sockfd,SOL_SOCKET,SO_RCVBUF,(char *)&nZero,sizeof(int));
    /*  if( strlen(filename) != 0 )
        {
        printf("dsfddsdafdfd");
        if( (pid = fork()) == 0 )
        {
        create_file(socket);
        }
        wait();
        }*/
    memset(buff,'\0',BUFFSIZE);
    fd_set rfds;
    struct timeval tv;
    int retval,maxfd = -1;

    while ( 1 )
    {
        memset(buff,'\0',BUFFSIZE);
        len = recv(sockfd,buff,BUFFSIZE,0);
        if( len  >  0 )
        {   
            if( strncmp(buff,"quit",4) == 0 )
            {
                printf("recv OK ,child process exit\n");
                exit(EXIT_SUCCESS);
            }
            printf("%s\n",buff);
        }
        else if ( 0 == len )
        {
            break;
        }
        else 
        {
            perror("recv err\n");
            break;
        }

    }
}
