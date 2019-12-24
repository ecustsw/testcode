

#include <errno.h>
#include <signal.h>
#include "define.h"

int wFd = -1;
void handler(int sig)
{
    perror("sigint handler");

    //do not close the open file descriptor,when control return back to programe,can continue to write to this file.
    // if(wFd >= 0)
    // {
    //     close(wFd);
    // }
}

int main(int argc,char* argv[])
{
    int flag = 0;
    setvbuf(stdout,NULL,_IONBF,0);//no buffer standard output

    signal(SIGINT, handler);//add interupt handler for resume after been interrupted.

    if(argc < 3)
    {
        char errMsg[] = "input ./exex filename mode\n";
        write(1,errMsg,strlen(errMsg));
        return -1;
    }

    write(1,argv[2],strlen(argv[2]));

    if(strcmp(argv[2],"a") == 0)
    {
        flag |= O_APPEND;
    }
    else if(strcmp(argv[2],"t") == 0)
    {
        flag |= O_TRUNC;
    }
    else
    {
        error_handle("non supported mode");
    }

    wFd = open(argv[1],flag|O_RDWR,CREATE_MODE);
    if(wFd < 0)
    {
        if((wFd = open(argv[1],flag|OPEN_FLAG,CREATE_MODE)) < 0)
        {
            error_handle("open file error");
        }
    }

    char buf[1024] = {0};
    int lenRead = 0;
    while((lenRead = read(0,buf,sizeof(buf))) > 0)
    {
        if(write(wFd,buf,strlen(buf)) != lenRead)
        {
            printf("write output file error,read data is %s length is %d\n",buf,lenRead);
            break;
        }
        write(1,buf,strlen(buf));
        memset(buf,0,sizeof(buf));
    }

    if(wFd > 0)
    {
        close(wFd);
    }
    printf("exit\n");

    return 0;
}