#include "toralize.h"

sReq *request(struct sockaddr_in *addr) {
    sReq *req;

    req = malloc(sizeof(struct proxy_request));
    req->vn = 4;
    req->cd = 1;
    req->dstport = addr->sin_port;
    req->dstip = addr->sin_addr.s_addr;
    strncpy(req->userid, USERNAME, 7);

    return req;
}

int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {      
    int s;
    struct sockaddr_in sock;
    sReq *req;
    sRep *rep;
    char buf[sizeof(struct proxy_reply)];
    int success;
    int (*p)(int, const struct sockaddr*, socklen_t);

    p = dlsym(RTLD_NEXT, "connect");
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    sock.sin_family = AF_INET;
    sock.sin_port = htons(PROXY_PORT);
    sock.sin_addr.s_addr = inet_addr(PROXY);

    if (p(s, (struct sockaddr *)&sock, sizeof(sock))) {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    req = request((struct sockaddr_in *)addr);
    write(s, req, sizeof(struct proxy_request));

    memset(buf, 0, sizeof(struct proxy_reply));

    if (read(s, buf, sizeof(struct proxy_reply)) < 1) {
        perror("read");
        free(req);
        close(s);

        exit(EXIT_FAILURE);
    }

    rep = (sRep *)buf;
    success = (rep->cd == 90);
    if (!success) {
        fprintf(stderr, "Unable to traverse" 
            " the proxy, error code: %d", rep->cd);

            close(s);
            free(req);

            exit(EXIT_FAILURE);
    }

    printf("Connected through the proxy.\n");

    dup2(s, sockfd);
    free(req);

    return EXIT_SUCCESS;
}
