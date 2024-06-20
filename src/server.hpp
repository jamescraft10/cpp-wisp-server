#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/ip.h>

class Server {
    public:
    const int PORT;
    const int BUFFER_SIZE = 1024;

    Server(int port, int bufferSize) : PORT{port}, BUFFER_SIZE{bufferSize} {
        // setup info
        serverInfo.sin_family = AF_INET;
        serverInfo.sin_port = htons(PORT);
        serverInfoLen = sizeof(serverInfo);
        clientInfoLen = sizeof(clientInfo);
        
        // setup socket
        sfd = socket(AF_INET, SOCK_STREAM, 0);
        if(0 > sfd)
            throw std::runtime_error("Couldn't create socket.");
        
        if(0 > bind(sfd, (sockaddr*)&serverInfo, serverInfoLen))
            throw std::runtime_error("Bind failed.\nTry changing the port.");

        if(0 > listen(sfd, 0))
            throw std::runtime_error("Couldn't listen.");

        std::cout << "Ready to start server\n";
    }

    void loop() {
        while(true) {
            int cfd = accept(sfd, &clientInfo, &clientInfoLen);
            if(0 > cfd)
                throw std::runtime_error("Failed to accept.\n");

            // received
            char buffer[BUFFER_SIZE];
            ssize_t received = recv(cfd, buffer, sizeof(buffer)-1, 0);
            std::string request = buffer; // make std::string for more functions

            std::string method;
            std::string path;
            if(received > 0) {
                request[received] = '\0';
                std::size_t firstSpace = request.find(' ');
                method = request.substr(0, firstSpace);
                std::size_t secondSpace = request.find("HTTP/1.1")-5;
                path = request.substr(firstSpace+1, secondSpace);
            }

            path = path.substr(1, path.length());
            client.request(path.c_str(), 443, "GET / HTTP/1.1\r\n\r\n");
            std::string content = client.buffer;
            client.buffer = "\0";
            std::string msg = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: "+std::to_string(strlen(content.c_str()))+"\r\n\r\n"+content;
            ssize_t sent = send(cfd, (void*)msg.c_str(), strlen(msg.c_str()), 0);
            close(cfd);
        }
    }

    private:
    sockaddr_in serverInfo = {0};
    sockaddr clientInfo = {0};
    socklen_t serverInfoLen;
    socklen_t clientInfoLen;
    int sfd;
    Client client;
};