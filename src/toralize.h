#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <arpa/inet.h>

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

#ifdef _WIN32
    // TODO: Support for Windows
    #include <windows.h>
    #include <winsock2.h> 
    #include <ws2tcpip.h>
    #include <Ws2ipdef.h>   

    #define WIN32_LEAN_AND_MEAN
    #define close closesocket
    #define dup2 _dup2

    #pragma comment(lib, "ws2_32.lib")

    //----------------------
    // Initialize Winsock
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR) {
        wprintf(L"WSAStartup function failed with error: %d\n", iResult);
        return 1;
    }
    //----------------------
    // Create a SOCKET for connecting to server
    SOCKET ConnectSocket;
    ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ConnectSocket == INVALID_SOCKET) {
        wprintf(L"socket function failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

#else 
    #include <unistd.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <dlfcn.h> 

#endif