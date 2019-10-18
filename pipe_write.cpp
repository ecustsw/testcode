#include <sys/wait.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

  
int  main(int argc, char *argv[])
{
  //int fds[2] = {0};
  if(argc < 2)
  {
    printf("bad arguments\n");
    return -1;
  }
  int fd = open(argv[1],O_WRONLY);
  if(fd < 0)
  {
    printf("open file error\n");
    return -1;
  }
  //fds[1] = fd;

  //pipe(fds);seem no use

  char buf[24] = {0};

  // for(;;)
  // {
  //   memset(buf,0,sizeof(buf));
  //   scanf("%s",buf);
  //   int n = write(fd,buf,strlen(buf));

  //   if(n < 0)
  //   {
  //     printf("write error\n");
  //     close(fd);
  //     return -1;
  //   }

  //   printf("set msg %s\tsize is%d-%d\n",buf,strlen(buf),n);
  //   //memset(buf,0,sizeof(buf));
  // }
  int n = 0;
  while(scanf("%s",buf) > 0)
  {
    if((n = write(fd,buf,strlen(buf))) < 0)
    {
      break;
    }
    printf("set msg %s\tsize is%d-%d\n",buf,(int)strlen(buf),n);
  }
  
  printf("writer closed\n");
  close(fd);
  return 0;
}
