#include "../include/chat.h"


void setup() {
    setvbuf(stdin, (char *)NULL, _IONBF, 0);        // flush the stdandard input, output, error buffer.
    setvbuf(stdout, (char *)NULL, _IONBF, 0);
    setvbuf(stderr, (char *)NULL, _IONBF, 0);
}

char* readBuf() {
    char *buf;
    char ch;
    int idx = 0;
    assert( (buf = calloc(1, sizeof(char) * 0x210) ) != NULL ); // Allocate empty buffer that sized 0x200.
    do {
        assert(read(0, &ch, 1) != -1);                          // Get input string for each byte.
        buf[idx++] = ch;
        if(idx % 0x200 == 0) { 
            assert( (buf = realloc(buf, sizeof(char) * (idx + 0x210))) != NULL );   // As the input size grows, the buffer is reallocated to a larger size.
        }
    } while(ch != '\n' && ch != '\0');                          // Until newline or NULL byte.
    if(buf[idx - 1] != '\n')                                    // if last byte is not newline, change the byte to newline and put in NULL byte in next. 
        buf[idx - 1] = '\n';
    buf[idx] = '\0';
    return buf;
}

int sendMsg(int fd, const char* sender) {
    char *msg = NULL;
    int err;
    int ret = 0;
    printf("%s: ", sender);                             // print the sender.
    msg = readBuf();                                    // get message from keyboard.
    assert(send(fd, msg, strlen(msg), 0) != -1);        // if error while sending, occured assert. 
    if(strlen(msg) == 5 && !strcmp(msg, "QUIT\n")) {    // if sender msg is "QUIT", then close socket and return -1
        close(fd);
        ret = -1;
    }
    free(msg);                                          // free the memory.
    return ret;
}

int recvMsg(int fd, const char* receiver) {
    int err;
    int idx = 0;
    int ret = 0;
    char ch;
    char *msg;

    assert( (msg = calloc(1, sizeof(char) * 0x210) ) != NULL ); // receive msg routine is liked readBuf. 
    do {
        assert( (err = recv(fd, (char*)&ch, 1, 0) ) >= 0 );     // if error while receving, occured assert.
        if(err == 0) {
            ret = -1;                                           // if EOF while receiving, ret will change -1
            break;
        }
        msg[idx++] = ch;
        if(idx % 0x200 == 0) { 
            assert( (msg = realloc(msg, sizeof(char) * (idx + 0x210))) != NULL );
        }
    } while(ch != '\n');
    if(!ret) printf("%s: %s", receiver, msg);                   // print the receiver and message.
    if(strlen(msg) == 5 && !strcmp(msg, "QUIT\n") ) {           // if receiver msg is "QUIT", then close socket and return -1
        ret = -1;
    }
    if(ret) close(fd);
    return ret;
}