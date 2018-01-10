#ifndef _FTP_
#include <sys/types.h> 
#include <dirent.h>
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
#endif 

void send_cmd_fork(int sockfd,char buff[]);
void recv_cmd_fork(int sockfd);
char *deal_str(char buff[]);
