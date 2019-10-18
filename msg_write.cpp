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
    while(scanf("%s",buf))
    {
        if(curStatus == 0)
        {
            printf("say hello to remote");
            scanf("%s",buf);
            msgsnd(msgQueue, buf, strlen(buf), MSG_HELLO);
            msgrcv(msgQueue,mBuf,MSGBUF_LEN,MSG_HELLO,MSG_EXCEPT);
            if(mBuf->mtype == MSG_HELLO)
            {
                curStatus = MSG_HELLO;
                write(1,mBuf->mtext,strlen(mBuf->mtext));
            }
            else
            {
                printf("get wrong msg type,expect msg_hello\n");
            }
        }
        else 
        {
            printf("say content to talk with remote\n");
            scanf("%s",buf);
            if(strcmp(buf,"bye") == 0)
            {
                msgsnd(msgQueue, buf, strlen(buf), MSG_BYE);
            }
            else
            {
                msgsnd(msgQueue, buf, strlen(buf), MSG_TALK);
                write(1,mBuf->mtext,strlen(mBuf->mtext));
            }
        }
        memset(mBuf->mtext,0,MSGBUF_LEN);
        memset(buf,0,sizeof(buf));
    }

    free(mBuf);
    return 0;
}