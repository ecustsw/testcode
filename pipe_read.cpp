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
  int fd = open(argv[1],O_RDONLY);
  if(fd < 0)
  {
    printf("open file error\n");
    return -1;
  }
  fds[0] = fd;

  pipe(fds);

  char buf[24];
  for(;;)
  {   
    int n = read(fd,buf,sizeof(buf));

    if(n < 0)
    {
      printf("read error\n");
      return -1;
    }

    printf("get msg %s\n",buf);
    memset(buf,0,sizeof(buf));
  }

  return 0;
}
