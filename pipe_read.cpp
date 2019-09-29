#include <sys/wait.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

    
      
int  main(int argc, char *argv[])
{
  //int fds[2] = {0};
  if(argc < 2)
  {
    printf("bad arguments\n");
    return -1;
  }
  int fd = open(argv[1],O_RDONLY|O_CREAT);
  if(fd < 0)
  {
    printf("open file error\n");
    return -1;
  }
  //fds[0] = fd;

  //pipe(fds);  seem no use.

  char buf[24] = {0};
  // for(;;)
  // {   
  //   memset(buf,0,sizeof(buf));
  //   int n = read(fd,buf,sizeof(buf));

  //   if(n < 0)
  //   {
  //     printf("read error\n");
  //     close(fd);
  //     return -1;
  //   }

  //   printf("get msg %s\tsize is%d-%d\n",buf,strlen(buf),n);
  //   //memset(buf,0,sizeof(buf));//initialize must put at beginnig of loop
  // }
  int n = 0;
  while((n = read(fd,buf,sizeof(buf))) > 0)
  {
    printf("get msg %s\tsize is%d-%d\n",buf,strlen(buf),n);
    memset(buf,0,sizeof(buf));
  }

  printf("reader closed\n");
  close(fd);
  return 0;
}
