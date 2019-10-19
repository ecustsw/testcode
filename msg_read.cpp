#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>


#include "define.h"

/*
sequence； wait hello -> response hello -> talking(bye/exit)
*/


int main(int argc,char** argv)
{
    int curStatus = MSG_BYE;
    char buf[32] = {0};
    int recvMsgType = 0;

    struct msgbuf* mBuf = (struct msgbuf*)malloc(sizeof(struct msgbuf) + MSGBUF_LEN);
    int msgSize = -1;

    int msgQueue = msgget(IPC_KEY,0666|IPC_CREAT);
    if(msgQueue < 0)
    {
        error_handle("get msg error");
    }

    printf("msg queue is %d\n",msgQueue);

    while(1)
    {
        msgSize = msgrcv(msgQueue,mBuf,MSGBUF_LEN,recvMsgType,0);
        if(msgSize < 0)
        {
            break;
        }

        if(mBuf->mtype == MSG_BYE)
        {
            if(strcmp(mBuf->mtext,"exit") == 0)
            {
                printf("exit\n");
                if(msgQueue >= 0)
                {
                    msgctl(msgQueue,IPC_RMID,0);
                }               
                exit(0);
            }
            curStatus = MSG_BYE;
            printf("bye...\n");
        }
        else if(mBuf->mtype == MSG_HELLO)
        {
            if(curStatus == MSG_BYE)
            { 
                printf("get hello msg  %s\n",mBuf->mtext);
                printf("say hello to remote\n");
                scanf("%s",buf);
                mBuf->mtype = MSG_HELLO;
                strcpy(mBuf->mtext,buf);
                msgsnd(msgQueue, mBuf, strlen(mBuf->mtext), 0);
                curStatus = MSG_HELLO;
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
                printf("get talk msg  %s\tmsgtype is %d\n",mBuf->mtext,(int)mBuf->mtype);
            }
            else
            {
                printf("please say hello first\n");
            }
        }

        //memset(buf,0,sizeof(buf));
        memset(mBuf->mtext,0,MSGBUF_LEN);
    }

    error_handle("recv msg error");
    free(mBuf);
    return 0;
}