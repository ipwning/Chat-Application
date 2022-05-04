#include "chat.h"

/*
    definition for sender and receiver.
*/
#define SENDER      "Server"
#define RECEIVER    "Client"

/*
    function definition that used in src/server.c
*/
int getPort(int argc, const char* argv[]);
int connectSocket(int port);