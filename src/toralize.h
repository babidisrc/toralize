#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <dlfcn.h>

#define PROXY "127.0.0.1"
#define PROXY_PORT 9050
#define USERNAME "toraliz"

typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned int int32;

typedef struct proxy_request {
    int8 vn;
    int8 cd;
    int16 dstport;
    int32 dstip;
    int8 userid[8];
} sReq;

typedef struct proxy_reply {
    int8 vn;
    int8 cd;
    int16 dstport; // não importante
    int32 dstip; // não importante
} sRep;

sReq *request(struct sockaddr_in*);
int connect(int, const struct sockaddr*, socklen_t);       