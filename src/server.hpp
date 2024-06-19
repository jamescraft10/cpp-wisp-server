#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/ip.h>

class Server {
    public:
    const int PORT = 443;
    const int BUFFER_SIZE = 1024;
    const int threads = 1;

    void init();
    void serverLoop();
    private:
};