#include <sys/ipc.h>
#include <sys/shm.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "define.h"


int main(int argc, char const *argv[])
{
    char buf[32] = {0};
    char opBuf[32] = {0};
    int lastReadPos = 0;
    int usedSize = 0;
    int shmKey = shmget(IPC_KEY,SHM_SIZE,0666|IPC_CREAT);
    if(shmKey < 0)
    {
        error_handle("get shm error");
    }

    char * shmAddr = (char*)shmat(shmKey,0,0666);
    if(shmAddr == NULL)
    {
        error_handle("attach shm error");
    }

    while(1)
    {
        scanf("%s",buf);
        if(strncmp(buf,"read",4) == 0)
        {
            memcpy(opBuf,shmAddr + lastReadPos,sizeof(opBuf) - 1);
            lastReadPos += strlen(opBuf);
            usedSize = strlen(shmAddr);
            printf("read data %s\tcur read pos is %d\ttotal used size is %d\n",opBuf,lastReadPos,usedSize);
        }
        else if(strncmp(buf,"write",5) == 0)
        {
            printf("input write data to apppen to shm\n");
            scanf("%s",opBuf);
            int len = strlen(shmAddr);
            memcpy(shmAddr + len,opBuf,strlen(opBuf));
            usedSize = strlen(shmAddr);
            printf("used shm size is %d\n",usedSize);
        }
        else if(strncmp(buf,"bye",3) == 0)
        {
            if(shmdt(shmAddr) < 0)
            {
                perror("shmdt error");
            }
            break;
        }
        else if(strncmp(buf,"reset",5) == 0)
        {
            char* pBuf = buf + 5;
            if(*pBuf != '-')
            {
                printf("reset-r or reset-w is required\n");
            }
            pBuf++;
            if(*pBuf == 'r')
            {
                lastReadPos = 0;
            }
            else if(*pBuf == 'w')
            {
                memset(shmAddr,0,strlen(shmAddr));
                lastReadPos = 0;//also reset readpos.
            }
            else
            {
                printf("reset-r or reset-w is required\n");
            }
        }
        else
        {
            printf("unrecognized operation\n");
        }
        memset(opBuf,0,sizeof(opBuf));
        memset(buf,0,sizeof(buf));
    }

    if(shmctl(shmKey,IPC_RMID,NULL) < 0)//decrease refrence count of shmKey
    {
        perror("remove shm error");
    }
    return 0;
}