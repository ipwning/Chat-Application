#include "../include/server.h"

int main (int argc, const char* argv[]) {
    int port;
    int fd;
    char *msg;
    setup();                        // Call setvbuf for all standard file.
    port = getPort(argc, argv);     // Get port number.
    fd = connectSocket(port);       // Make socket and accpet client connection.

    while(1) {
        if(sendMsg(fd, SENDER) == -1) { // Send first, then wait for client message
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