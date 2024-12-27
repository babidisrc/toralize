#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <dlfcn.h> 
#include <netdb.h>
#include <sys/types.h>

#define PROXY "127.0.0.1"
#define PROXY_PORT 9050
#define USERNAME "toraliz"

typedef uint8_t int8;
typedef uint16_t int16;
typedef uint32_t int32;

typedef int (*connect_t)(int, const struct sockaddr*, socklen_t);

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

static sReq *request(struct sockaddr_in*);
int connect(int, const struct sockaddr*, socklen_t); 