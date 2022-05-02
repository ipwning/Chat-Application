#include "../include/chat.h"

char* readBuf() {
    char *buf;
    char ch;
    int idx = 0;
    assert( (buf = calloc(1, sizeof(char) * 0x210) ) != NULL );
    do {
        assert(read(0, &ch, 1) != -1);
        buf[idx++] = ch;
        if(idx % 0x200 == 0) { 
            assert( (buf = realloc(buf, sizeof(char) * (idx + 0x210))) != NULL );
        }
    } while(ch != '\n' && ch != '\0');
    if(buf[idx - 1] != '\n') 
        buf[idx - 1] = '\n';
    buf[idx] = '\0';
    return buf;
}

void sendMsg(int fd, const char* sender) {
    char *msg = NULL;
    int err;
    printf("%s: ", sender);
    msg = readBuf();
    assert(send(fd, msg, strlen(msg), 0) != -1);
    free(msg);
}

int recvMsg(int fd, const char* receiver) {
    int err;
    char ch;
    char ret = 0;
    printf("%s: ", receiver);
    do {
        assert( (err = recv(fd, (char*)&ch, 1, 0) ) < 0 );  // ERROR
        if(err == 0) {
            ret = -1;                                       // EOF
            break;
        }
        putchar(ch); 
    } while(ch != '\n');
    return ret;
}