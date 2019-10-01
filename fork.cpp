#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>


#include "define.h"

int main(int argc,char** argv)
{   
    int status = 0;
    struct rusage rusg;
    memset(&rusg,0,sizeof(rusg));

    int fds[2] = {0};

    if(pipe(fds) < 0)
    {
        error_handle("fork error");
    }

    int pid = fork();//after the pipe

    if(0 == pid)
    {
        printf("this is child process\n");
        //sleep(10);
        close(fds[1]);
        char buf[32] = {0};
        while(read(fds[0],buf,sizeof(buf)) > 0)
        {
            printf("get msg from parent\t%s\n",buf);
            if(strncmp(buf,"exit",4) == 0)
            {
                break;
            }
            memset(buf,0,sizeof(buf));
        }
        sleep(5);
        close(fds[0]);
        printf("child exited\n");
        exit(0);//effect the status when use wait4.
    }
    else if(pid > 0)
    {
        //printf("this is parent process\n");   
        close(fds[0]);
        char buf[32] = {0};
        while(read(STDIN_FILENO,buf,sizeof(buf)) > 0)
        {
            if(buf[0] == '\n')
                continue;

            write(fds[1],buf,strlen(buf));
            if(strncmp(buf,"exit",4) == 0)//strcmp has problem.
            {
                break;
            }
            memset(buf,0,sizeof(buf));
        }
        close(fds[1]);
    }
    else
    {
        error_handle("fork error");
    }

    printf("waiting for child %d to exit\n",pid);

    pid = wait4(pid,&status,WUNTRACED,&rusg);

    printf("main thread exited,child %d status is %d\n",pid,status);

    return 0;
}