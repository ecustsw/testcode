#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "define.h"

/*                 
sequence； say hello -> wait for response hello -> talking ...>bye --> go back to say hello
                                                                   --> exit
           say exit
*/

int main(int argc,char** argv)
{
    int msgQueue = msgget(IPC_KEY,0666|IPC_CREAT);
    if(msgQueue < 0)
    {
        error_handle("get msg error");
    }

    printf("msg queue is %d\n",msgQueue);

    int curStatus = 0;

    char buf[32] = {0};
    struct msgbuf* mBuf = (struct msgbuf*)malloc(sizeof(struct msgbuf) + MSGBUF_LEN);
    while(1)
    {
        if(curStatus == 0)
        {
            printf("say hello to remote or print exit to exit");
            scanf("%s",buf);
            if(strcmp(buf,"exit") == 0)
            {
                mBuf->mtype = MSG_BYE;
                strcpy(mBuf->mtext,buf);
                msgsnd(msgQueue, mBuf, strlen(mBuf->mtext), MSG_BYE);
                curStatus = 0;
                exit(0);
            }
            mBuf->mtype = MSG_HELLO;
            strcpy(mBuf->mtext,buf);
            msgsnd(msgQueue, mBuf, strlen(mBuf->mtext), 0);
            msgrcv(msgQueue,mBuf,MSGBUF_LEN,MSG_HELLO,0);
            if(mBuf->mtype == MSG_HELLO)
            {               
                printf("get hello msg %s\n",mBuf->mtext);
                curStatus = MSG_HELLO;
            }
            else
            {
                printf("get wrong msg type,expect msg_hello\n");
            }
        }
        else 
        {
            printf("talking with remote,input content...\n");
            scanf("%s",buf);
            if(strcmp(buf,"bye") == 0)
            {
                mBuf->mtype = MSG_BYE;
                strcpy(mBuf->mtext,buf);
                msgsnd(msgQueue, mBuf, strlen(mBuf->mtext), MSG_BYE);
                curStatus = 0;
            }
            else
            {
                mBuf->mtype = MSG_TALK;
                strcpy(mBuf->mtext,buf);
                msgsnd(msgQueue, mBuf, strlen(mBuf->mtext), MSG_TALK);
            }
        }
        memset(mBuf->mtext,0,MSGBUF_LEN);
        memset(buf,0,sizeof(buf));
    }

    error_handle("send msg error");
    free(mBuf);
    return 0;
}