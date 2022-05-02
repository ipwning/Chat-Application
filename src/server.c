#include "../include/server.h"

int main (int argc, const char* argv[]) {
    int port;
    int fd;
    char *msg;
    checkArgument(argc, argv);
    port = getPort(argv[1]);
    fd = connectSocket(port);

    while(true) {
        sendMsg(fd, SENDER);
        recvMsg(fd);
    }
}