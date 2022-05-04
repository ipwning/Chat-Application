#include "../include/client.h"

int main (int argc, const char* argv[]) {
    const char* ip;
    int port;
    int fd;
    char *msg;
    setup();
    assert(!validateArgv(argc, argv));
    ip = getIP(argv);
    port = getPort(argv);
    fd = connectSocket(ip, port);

    while(1) {
        if(recvMsg(fd, RECEIVER) == -1) {
            puts("[Disconnected]");
            break;
        }
        if(sendMsg(fd, SENDER) == -1) {
            puts("[Disconnected]");
            break;

        }
    }
    return 0;
}