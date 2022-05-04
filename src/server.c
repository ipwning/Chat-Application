#include "../include/server.h"

int main (int argc, const char* argv[]) {
    int port;
    int fd;
    char *msg;
    setup();
    port = getPort(argc, argv);
    fd = connectSocket(port);

    while(1) {
        if(sendMsg(fd, SENDER) == -1) {
            puts("[Disconnected]");
            break;

        }
        if(recvMsg(fd, RECEIVER) == -1) {
            puts("[Disconnected]");
            break;
        }
    }
    return 0;
}