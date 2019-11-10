

#include "define.h"


int main(int argc,char* argv[])
{
    int flag = 0;
    int wFd = -1;

    if(argc < 3)
    {
        char errMsg[] = "input ./exex filename mode\n";
        write(1,errMsg,strlen(errMsg));
        return -1;
    }

    if(argv[2][0] == 'a')
    {
        flag |= O_APPEND;
    }
    else if(argv[2][0] == 't')
    {
        flag |= O_TRUNC;
    }
    else
    {
        error_handle("non supported mode");
    }

    wFd = open(argv[1],flag|OPEN_FLAG|O_EXCL,CREATE_MODE);
    if(wFd < 0)
    {
        if((wFd = open(argv[1],flag|OPEN_FLAG,CREATE_MODE)) < 0)
        {
            error_handle("open file error");
        }
    }

    char buf[1024] = {0};
    while(scanf("%s",buf) > 0)
    {
        buf[strlen(buf)] = '\n';
        write(wFd,buf,strlen(buf));
        write(1,buf,strlen(buf));
        memset(buf,0,sizeof(buf));
    }

    close(wFd);

    return 0;
}