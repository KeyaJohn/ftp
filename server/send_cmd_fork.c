#include "ftp.h"


void send_ls(int sockfd,char * p)
{
    DIR * dp;
    int len;
    unsigned int count = 0;
    struct dirent *dirp;
    if( (dp = opendir(".")) == NULL )
    {
        perror("opendir err\n");
        return ;
    }
    while( ( dirp = readdir(dp)) != NULL )
    {
        //printf("%s\n",dirp->d_name);
        if( strncmp(dirp->d_name,".",1) != 0 )
        {
            len = send(sockfd,dirp->d_name,strlen(dirp->d_name),0);
            usleep(800);
            fflush(fdopen(sockfd,"w"));
            if( len < 0 )
            {
                perror("server : send fail!\n");
                exit(EXIT_FAILURE);
            }
            count ++;
        }
    }
    len = send(sockfd,"quit",4,0);
    if( len < 0 )
    {
            perror("server : send fail!\n");
            exit(EXIT_FAILURE);
    }
    printf("send successfully file count:%d\n",count);
}


void send_cat(int sockfd,char buff[])
{
    FILE* fp;
    int len;
    char str[BUFFSIZE];
    char* cmd  = deal_str(buff);
    if( (fp = fopen(cmd,"rb")) ==  NULL )
    {
        perror("server : fopen fail\n");
        return ;
    }
    
    while ( fgets(str,BUFFSIZE,fp) != NULL )
    {
        len = send(sockfd,str,strlen(str),0);
        usleep(200);
        if( len < 0 )
        {
            perror("server: send fail\n");
            return ;
        }
        if( 0 == len)
        {
            break;
        }
        memset(str,'\0',BUFFSIZE);
    }
    len = send(sockfd,"quit",4,0);
    if( len < 0 )
    {
            perror("server : send fail!\n");
            exit(EXIT_FAILURE);
    }
    printf("send successfully file!\n");

}

void send_get(int sockfd,char buff[])
{
    FILE * fp = NULL;
    char * cmd = deal_str(buff);
    char str[BUFFSIZE] = "";
    int len ;

    if( (fp = fopen(cmd,"r")) == NULL )
    {
        perror("server : fopen file fail\n");
        exit(EXIT_FAILURE);
    }
    len = send(sockfd,cmd,strlen(cmd),0);//首先发送文件名给客户端，即直到传送文件。
    usleep(400);
    if( len < 0 )
    {
        perror("server: send fail\n");
        return ;
    }
    printf("send successfully filename :%s\n",cmd);
   
    while ( fgets(str,BUFFSIZE,fp) != NULL )
    {
        len = send(sockfd,str,strlen(str),0);
        usleep(200);
      //  printf("%s\n",str);
        if( len < 0 )
        {
            perror("server: send fail\n");
            return ;
        }
        if( 0 == len)
        {
            break;
        }
        memset(str,'\0',BUFFSIZE);
    }
    send(sockfd,"quit",4,0);
    printf("send file successfully\n");
}
void send_cmd_fork(int sockfd,char buff[])
{
    if( strncmp(buff,"ls",2) == 0 )
    {
        send_ls(sockfd,"ls");
    }
    else if( strncmp(buff,"cat",3) == 0 )
    {
        send_cat(sockfd,buff);
    }
    else if ( strncmp(buff,"get",3) == 0 )
    {
        send_get(sockfd,buff);
    }
    return ;
}
