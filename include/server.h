#include "chat.h"

#define SENDER      "Server"
#define RECEIVER    "Client"

int getPort(int argc, const char* argv[]);
int connectSocket(int port);