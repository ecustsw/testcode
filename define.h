#ifndef __MY_DEFINE_H_
#define __MY_DEFINE_H_

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define error_handle(msg)\
            perror(msg);return -1;

#define IPC_KEY 9999
#define MSGBUF_LEN 1024


#define MSG_HELLO 1
#define MSG_BYE 2
#define MSG_TALK 3

#define SHM_SIZE 1024

#define CREATE_MODE 0666
#define OPEN_FLAG O_CREAT|O_RDWR

#endif