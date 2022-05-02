#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <assert.h>

char* readBuf();
void sendMsg(int fd, const char* sender);
int recvMsg(int fd, const char* receiver);
void checkArgument(int argc, char* argv[]);