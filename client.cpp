#include "define.h"

int main(int argc,char ** argv)
{
    if(argc < 4)
    {
        printf("please set server's port:argv[1] and ip:argv[2] msg:argv[3]\n");
        return -1;
    }
    int cfd = socket(AF_INET,SOCK_STREAM,0);
    if(cfd < 0)
    {
        error_handle("open error");
    }

    int on = 1;
    if(setsockopt(cfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on) ) < 0)
    {
        error_handle("set sock opt");
    }

    struct sockaddr_in saddr;
    memset(&saddr,0,sizeof(saddr));

    //server paras.
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(atoi(argv[1]));
    saddr.sin_addr.s_addr = inet_addr(argv[2]);

    char* buf = new char[strlen(argv[3]) + 1];
    memcpy(buf,argv[3],strlen(argv[3]));

    if(connect(cfd,(struct sockaddr*)&saddr,sizeof(saddr)) < 0)
    {
        error_handle("connect error");
    }

    int sizeWrite = write(cfd,buf,strlen(buf));

    printf("set msg\t%s\t%d\n",buf,sizeWrite);

    close(cfd);
    delete[] buf;

    return 0;
}

