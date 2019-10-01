#ifndef __MY_DEFINE_H_
#define __MY_DEFINE_H_

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define error_handle(msg)\
            perror(msg);return -1;

#endif