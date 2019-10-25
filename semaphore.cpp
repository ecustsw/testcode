#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "define.h"


int main(int argc,char ** argv)
{
    char buf[124] = {0};
    char * pBuf = NULL;
    int semid = -1;
    struct sembuf sops[1];

    semid = semget(IPC_KEY,1,IPC_CREAT|0666);
    if(semid < 0)
    {
        error_handle("get sem error");
    }

    //initialize semaphore
    if(semctl(semid,0,SETVAL,0) < 0)
    {
        error_handle("reset sem error");
    }

    while(1)
    {
        scanf("%s",buf);
        pBuf = buf;
        if(strncmp(pBuf,"get",3) == 0)
        {
            pBuf += 3;
            if(*pBuf != '-')
            {
                printf("get must followed by a num\n");
            }
            else
            {
                pBuf++;
                int num = atoi(pBuf);
                if(num < 0)
                {
                    printf("please input digit smaller than zero\n");
                }
                else
                {
                    sops[0].sem_num = 0;
                    sops[0].sem_op = num;
                    //sops[0].sem_flg = IPC_NOWAIT;
                    sops[0].sem_flg = 0;
                    if(semop(semid,sops,1) < 0)
                    {
                        perror("semop error");
                    }
                }
            }
        }
        else if(strncmp(pBuf,"set",3) == 0)
        {
            pBuf += 3;
            if(*pBuf != '-')
            {
                printf("set must followed by a num\n");
            }
            else
            {
                pBuf++;
                int num = atoi(pBuf);
                if(num > 0)
                {
                    printf("please input digit bigger than zero\n");
                }
                else
                {
                    sops[0].sem_num = 0;
                    sops[0].sem_op = num;
                    //sops[0].sem_flg = IPC_NOWAIT;
                    sops[0].sem_flg = 0;
                    if(semop(semid,sops,1) < 0)
                    {
                        perror("semop error");
                    }
                }
            }
        }
        else if(strncmp(pBuf,"bye",3) == 0)
        {
            printf("bye\n");
            break;
        }
        else
        {
            printf("please input the set,get and bye\n");
        }
        memset(buf,0,sizeof(buf));
    }

    semctl(semid,0,IPC_RMID,0);

    return 0;
}