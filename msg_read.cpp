#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>


#include "define.h"


int main(int argc,char** argv)
{
    int msgQueue = msgget(IPC_KEY,IPC_CREAT);
    if(msgQueue < 0)
    {
        error_handle("get msg error");
    }

    printf("msg queue is %d\n",msgQueue);

    int curStatus = 0;
    char buf[32] = {0};

    struct msgbuf* mBuf = (struct msgbuf*)malloc(sizeof(struct msgbuf) + MSGBUF_LEN);

    while(msgrcv(msgQueue,mBuf,MSGBUF_LEN,0,MSG_EXCEPT) < 0)
    {
        if(mBuf->mtype == MSG_BYE)
        {
            curStatus = MSG_BYE;
            printf("bye...\n");
        }
        else if(mBuf->mtype == MSG_HELLO)
        {
            if(curStatus == MSG_BYE)
            {
                curStatus = MSG_HELLO;
                write(1,mBuf->mtext,strlen(mBuf->mtext));
                printf("say hello to remote\n");
                scanf("%s",buf);
                msgsnd(msgQueue, buf, strlen(buf), MSG_HELLO);
            }
            else if(curStatus == MSG_HELLO)
            {
                printf("please do not say hello again\n");
            }
            else
            {
                printf("please say bye before say hello\n");
            }
        }
        else if(mBuf->mtype == MSG_TALK)
        {
            if(curStatus == MSG_HELLO || curStatus == MSG_TALK)
            {
                curStatus = MSG_TALK;
                write(1,mBuf->mtext,strlen(mBuf->mtext));
                scanf("%s",buf);
                msgsnd(msgQueue, mBuf, strlen(mBuf->mtext), MSG_TALK);
            }
            else
            {
                printf("please say hello first\n");
            }
        }

        memset(buf,0,sizeof(buf));
        memset(mBuf->mtext,0,MSGBUF_LEN);
    }

    free(mBuf);
    return 0;
}