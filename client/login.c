#include "login.h"

int login(int sockfd)
{
    char buff[10];
    char name[20],*passwd;
    char pass[40];
    char slat[2];
    memset(name,'\0',sizeof(name));
    memset(passwd,'\0',sizeof(passwd));

    setbuf(stdout,NULL);
   
    int len = send(sockfd,"name",4,0);
    printf("please input your name:");
    fgets(name,sizeof(name),stdin);
    printf("name %s\n",name);
    usleep(400);
    if( len < 0 )
    {
        perror("err\n");
        return 0;
    }
    
    len = send(sockfd,name,sizeof(name),0);
    usleep(200);
    if( len < 0 )
    {
        perror("send err\n");
        return 0;
    }
    len = recv(sockfd,buff,sizeof(buff),0);
    printf("%s\n",buff);
    if( strncmp(buff,"ok",2) == 0 )
    {
        passwd = getpass("please input your password:");
        slat[0] = passwd[0];
        slat[1] = passwd[1];
        //strcpy(pass,crypt(passwd,slat));
        len = send(sockfd,passwd,strlen(passwd),0);
        usleep(400);
        if( len < 0 )
        {
            perror("send err\n");
            return 0;
        }
        memset(buff,'\0',sizeof(buff));
       recv(sockfd,buff,sizeof(buff),0);
       if( strncmp(buff,"ok",2) == 0 )
       {
            puts("login successfully!");
            return 1;
       }
       else
       {
            puts("your passwd false!");
            return 0;
       }
        
    }
    else
    {
        puts("having no the name !\n");
        return 0;
    }
    
}
