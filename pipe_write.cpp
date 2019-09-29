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
  int fds[2] = {0};
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
  fds[1] = fd;

  pipe(fds);

  char buf[24];

  for(;;)
  {
    scanf("%s",buf);
    int n = write(fd,buf,strlen(buf));

    if(n < 0)
    {
      printf("write error\n");
      return -1;
    }

    printf("set msg %s\n",buf);
    memset(buf,0,sizeof(buf));
  }
  
  return 0;
}
