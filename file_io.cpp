#include "define.h"


int main(int argc,char* argv[])
{
    if(argc < 3)
    {
        error_handle("bad argumnets");
    }

    int fd = -1;
    char * buf = NULL;
    int opLen = -1;
    int opRet = -1;
    fd = open(argv[1],OPEN_FLAG,CREATE_MODE);
    if(fd < 0)
    {
        error_handle("open file error");
    }

    for(int i = 2; i < argc;i++)
    {
        switch(argv[i][0])
        {
            buf = NULL;
            opLen = -1;
            opRet = -1;

            case 'r':
            case 'R':
                opLen = atoi(argv[i] + 1);
                if(opLen > 0)
                {
                    buf = (char*)malloc(opLen);
                    opRet = read(fd,buf,opLen);
                    if(opRet >= 0)
                    {
                        //printf("%s %s\n",argv[i],buf);//distinguish with printable and non-printable character
                        for(int j = 0; j < opRet;j++)
                        {
                            if(argv[i][0] == 'r')
                            {
                                if(isPrintable(buf[j]))
                                {
                                    printf("%c",buf[j]);
                                }
                                else
                                {
                                    printf("%c",'?');
                                }
                            }
                            else
                            {
                                printf("%02x ",buf[j]);
                            }
                        }
                        printf("\n");
                    }
                    else
                    {
                        printf("read failed %d\n",opLen);
                        perror("");
                    }                    
                    free(buf);
                }
                else
                {
                    printf("can not read less than zero\n");
                }
                break;
            case 'w':
            case 'W':
                opLen = strlen(argv[i] + 1);
                if(opLen >= 0)
                {
                    buf = (char*)malloc(opLen + 1);
                    memcpy(buf,argv[i] + 1,opLen);
                    opRet = write(fd,buf,opLen);
                    if(opRet > 0)
                    {
                        printf("%s %d\n",argv[i],opRet);
                    }
                    else
                    {
                        printf("write failed %d\n",opLen);
                        perror("");
                    }    
                    free(buf);               
                }
                else
                {
                    printf("can not write less than zero\n");
                }
                break;
            case 'l':
                opLen = atoi(argv[i] + 1);
                opRet = lseek(fd,opLen,SEEK_SET);
                if(opRet >= 0)
                {
                    printf("%s %d\n",argv[i],opRet);
                }
                else
                {
                    printf("lseek failed %d\n",opLen);
                    perror("");
                }
                break;
            default:
                printf("bad cmd\n");
                break;
        }
    }

    if(close(fd) < 0)
    {
        error_handle("close file failed");
    }
    return 0;
}