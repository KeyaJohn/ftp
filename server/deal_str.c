#include "ftp.h"

char * deal_str(char buff[])
{
    char *cmd = (char *) malloc( sizeof(char) * 20);
    memset(cmd,'\0',sizeof(cmd));
    int i = 0,j = 0;
    while( buff[i] != ' ' )
    {
        i++;
    }
    i++;
    while( buff[i] != '\0' )
    {
        cmd[j] = buff[i];
        j++;i++;
    }
    return cmd;
}
