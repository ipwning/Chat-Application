#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

void setup();
char* readBuf();
int sendMsg(int fd, const char* sender);
int recvMsg(int fd, const char* receiver);