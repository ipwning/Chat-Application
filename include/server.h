#include "chat.h"

#define SENDER      "Server"
#define RECEIVER    "Client"

void checkArgument(int argc, const char* argv[]);
int getPort(int argc, const char* argv[]);
int connectSocket(int port);