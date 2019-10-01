
#include "define.h"

int main(int argc,char ** argv)
{
    if(argc < 2)
    {
        printf("set port\n");
        return -1;
    }
    int sfd = socket(AF_INET,SOCK_STREAM,0);
    if(sfd < 0)
    {
        error_handle("open error");
    }

    int on = 1;
    if(setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
    {
        error_handle("set sock opt");
    }

    struct sockaddr_in saddr;
    memset(&saddr,0,sizeof(saddr));

    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(atoi(argv[1]));
    saddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(bind(sfd,(struct sockaddr*)&saddr,sizeof(saddr)) < 0)
    {
        error_handle("bind error");
    }

    if(listen(sfd,5) < 0)
    {
        error_handle("listen error");
    }

    //client paras.
    sockaddr_in caddr;
    socklen_t len = sizeof(caddr);
    int cfd = accept(sfd,(struct sockaddr*)&caddr,&len);
    if(cfd < 0)
    {
        error_handle("accept error");
    }

    char * cip = inet_ntoa(caddr.sin_addr);
    printf("client ip is\t%s\n",cip);

    int bufSize = 12;
    char* buf = new char[bufSize];
    int readed = 0;
    int n = 0;
    while((n = read(cfd,buf + readed,bufSize - readed)) > 0)
    {
        readed += n;
    }

    printf("get msg\t%s\tlen is %d\n",buf,readed);

    close(cfd);
    delete[] buf;

    return 0;
}

