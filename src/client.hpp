#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <openssl/ssl.h>

std::string httpsRequestTCP(const char *serverIp, int port, const char *msg) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in addr = {
        AF_INET,
        htons(port),
        htonl(0x08080808)
    };

    connect(sockfd, (sockaddr*)&addr, sizeof(addr));

    SSL_CTX* ctx = SSL_CTX_new(TLS_method());
    SSL* ssl = SSL_new(ctx);
    SSL_set_fd(ssl, sockfd);
    SSL_connect(ssl);
    SSL_write(ssl, msg, strlen(msg));
    char buffer[1024] = {0};
    SSL_read(ssl, buffer, 1023);
    return buffer;
}