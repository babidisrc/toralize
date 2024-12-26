#include "toralize.h"

sReq *request(const char *dstip, const int dstport) {
    sReq *req;

    req = malloc(sizeof(struct proxy_request));
    req->vn = 4;
    req->cd = 1;
    req->dstport = htons(dstport);
    req->dstip = inet_addr(dstip);
    strncpy(req->userid, USERNAME, 7);

    return req;
}

int main(int argc, char *argv[]) {
    char *host;
    int port, s;
    struct sockaddr_in sock;
    sReq *req;
    sRep *rep;
    char buf[sizeof(struct proxy_reply)];
    int success;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <host> <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    host = argv[1];
    port = atoi(argv[2]); // string -> int

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    sock.sin_family = AF_INET;
    sock.sin_port = htons(PROXY_PORT);
    sock.sin_addr.s_addr = inet_addr(PROXY);

    if (connect(s, (struct sockaddr *)&sock, sizeof(sock))) {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    printf("Connected to proxy\n");
    req = request(host,port);
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
            "the proxy, error code: %d", rep->cd);

            close(s);
            free(req);

            exit(EXIT_FAILURE);
    }

    printf("Successfully connected through the proxy to "
            "%s:%d\n", host, port);

    close(s);
    free(req);

    return EXIT_SUCCESS;
}