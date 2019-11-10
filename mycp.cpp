#include "define.h"



int main(int argc, char* argv[])
{
    if(argc < 3)
    {
        error_handle("bad argcs");
    }

    int rFd = -1;
    int wFd = -1;
    int readCount = -1;
    //int writeCount = -1;
    int opValue = -1;
    int totalFileSize = -1;

    //for file hole use begin
    char writeBuf[1204] = {0};
    int writeBufCount = 0;
    int seekCount = 0;
    //end

    rFd = open(argv[1],O_RDONLY);
    if(rFd < 0)
    {
        error_handle("open source file failed");
    }

    wFd = open(argv[2],OPEN_FLAG|O_TRUNC,CREATE_MODE);
    if(wFd < 0)
    {
        error_handle("open des file failed");
    }

    totalFileSize = lseek(rFd,0,SEEK_END);
    printf("source file size is %d\n",totalFileSize);
    lseek(rFd,0,SEEK_SET);

    char buf[1024] = {0};
    readCount = read(rFd,buf,sizeof(buf));
    printf("read %d bytes\n",readCount);
    while(readCount > 0)//for read,zero means end-of-file
    {
        buf[readCount] = 0;//replace the use of memset

        //implement one: write all byte begin;in this sitution,will write more than one byte compare to source file,donot know why..
        // while(writeCount < readCount)
        // {
        //     opValue = write(wFd,buf + writeCount,readCount - writeCount);
        //     writeCount += opValue;
        // }
        //end

        //implement two: only write non-null byte,deal with file hole begin
        for(int i = 0;i < readCount;i++)
        {
            if(buf[i] == 0)
            {
                //flush write buf
                if(writeBufCount > 0)
                {
                    writeBuf[writeBufCount] = 0;
                    opValue += write(wFd,writeBuf,writeBufCount);
                    writeBufCount = 0;
                    //writeBuf[writeBufCount] = 0;
                }
                seekCount++;
            }
            else
            {
                if(seekCount > 0)
                {
                    lseek(wFd,seekCount,SEEK_CUR);
                    seekCount = 0;
                }
                writeBuf[writeBufCount] = buf[i];
                writeBufCount++;
                if(writeBufCount == 1024)
                {
                    writeBuf[writeBufCount] = 0;
                    opValue += write(wFd,writeBuf,writeBufCount);
                    writeBufCount = 0;
                    //writeBuf[writeBufCount] = 0;
                }
            }
        }
        //end

        printf("write %d byte\n",opValue);
        //writeCount = 0;
        opValue = 0;
        readCount = read(rFd,buf,sizeof(buf));
        printf("read %d bytes\n",readCount);
    }

    //flush remain bytes
    if(writeBufCount > 0)
    {
        writeBuf[writeBufCount] = 0;
        opValue += write(wFd,writeBuf,writeBufCount);
        writeBufCount = 0;
        printf("write last %d byte\n",opValue);
        //writeBuf[writeBufCount] = 0;
    }

    close(rFd);
    close(wFd);
    return 0;
}