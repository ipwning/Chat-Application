#include "client.h"

int validateArgv(int argc, const char* argv[]) {
    int ret = 0;
    int len;
    
    if(argc != 3) {
        ret = 1;
    } else if (strlen(argv[1]) <= 0) {
        ret = 1;
    } else if( (len = strlen(argv[2])) <= 0) {
        ret = 1;
    } else {
        for(int i = 0; i < len; i++) {
            if('9' < argv[2][i] || argv[2][i] < '0') 
                ret = 1;
        }
    }
    return ret;
}

const char* getIP(const char* argv[]) {
    return argv[1];
}

int getPort(const char* argv[]) {
    return strtoull(argv[2], NULL, 10);
}

int connectSocket(const char* ip, int port) {
    struct sockaddr_in addr;
    int fd;

    addr.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &(addr.sin_addr));
    addr.sin_port = htons(port);
    assert( ( fd = socket(AF_INET, SOCK_STREAM, 0) ) != -1 );
    assert(connect(fd, (struct sockaddr*)&addr, sizeof(addr)) != -1 );
    puts("[Connected]");
    return fd;
}