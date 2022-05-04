#include "../include/client.h"

int main (int argc, const char* argv[]) {
    const char* ip;
    int port;
    int fd;
    char *msg;
    setup();                            // Call setvbuf for all standard file.
    assert(!validateArgv(argc, argv));  // If does not fit argument, occured assert.
    ip = getIP(argv);
    port = getPort(argv);
    fd = connectSocket(ip, port);       // Connect socket by use ip and port.

    while(1) {
        if(recvMsg(fd, RECEIVER) == -1) {   // Receive first (wait for server's message)
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