#include "../include/chat.h"


void setup() {
    setvbuf(stdin, (char *)NULL, _IONBF, 0);
    setvbuf(stdout, (char *)NULL, _IONBF, 0);
    setvbuf(stderr, (char *)NULL, _IONBF, 0);
}

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

int sendMsg(int fd, const char* sender) {
    char *msg = NULL;
    int err;
    int ret = 0;
    printf("%s: ", sender);
    msg = readBuf();
    assert(send(fd, msg, strlen(msg), 0) != -1);
    if(strlen(msg) == 5 && !strcmp(msg, "QUIT\n")) {
        close(fd);
        ret = -1;
    }
    free(msg);
    return ret;
}

int recvMsg(int fd, const char* receiver) {
    int err;
    int idx = 0;
    int ret = 0;
    char ch;
    char *msg;

    assert( (msg = calloc(1, sizeof(char) * 0x210) ) != NULL );
    do {
        assert( (err = recv(fd, (char*)&ch, 1, 0) ) >= 0 );  // ERROR
        if(err == 0) {
            ret = -1;                                       // EOF
            break;
        }
        msg[idx++] = ch;
        if(idx % 0x200 == 0) { 
            assert( (msg = realloc(msg, sizeof(char) * (idx + 0x210))) != NULL );
        }
    } while(ch != '\n');
    if(!ret) printf("%s: %s", receiver, msg);
    if(strlen(msg) == 5 && !strcmp(msg, "QUIT\n") ) {
        ret = -1;
    }
    if(ret) close(fd);
    return ret;
}