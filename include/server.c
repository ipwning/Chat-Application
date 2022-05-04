#include "server.h"

int validateArgv(int argc, const char* argv[]) {
    int ret = 0;
    int len;
    
    if(argc != 2) {
        ret = 1;
    } else if( (len = strlen(argv[1])) <= 0) {
        ret = 1;
    }
    else {
        for(int i = 0; i < len; i++) {
            if('9' < argv[1][i] || argv[1][i] < '0')
                ret = 1;
        }
    }
    return ret;
}

int getPort(int argc, const char* argv[]) {
    assert(!validateArgv(argc, argv));
    return strtoull(argv[1], NULL, 10);
}

void printAddrInfo(struct sockaddr_in *addr) {
    char ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(addr->sin_addr), ip, INET_ADDRSTRLEN);
    printf("[Connection from %s:%hu]\n", ip, ntohs(addr->sin_port));
}

int connectSocket(int port) {
    struct sockaddr_in addr;
    struct sockaddr_in client_addr;
    int client_addr_size;
    int sockfd;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    assert( ( sockfd = socket(AF_INET, SOCK_STREAM, 0) ) != -1 );
    assert( bind( sockfd, (struct sockaddr*)&addr, sizeof(addr) ) != -1  );
    assert( listen( sockfd, 5 ) != -1 );
    client_addr_size = sizeof(client_addr);
    assert( (sockfd = accept( sockfd, (struct sockaddr_in*)&client_addr, &client_addr_size ) ) != -1 );
    printAddrInfo(&client_addr);
    return sockfd;
}