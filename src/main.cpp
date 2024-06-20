#include <iostream>
#include <string>
#include <stdexcept>
#include "client.hpp"
#include "server.hpp"

int main(int argc, char** argv) {
    try {
        // Client client;
        // client.request("https://www.google.com", 443, "GET /search?q=a HTTP/1.1\r\n\r\n");
        // std::cout << client.buffer << '\n';
        Server server{3000, 1024};
        server.loop();
    } catch(const std::exception& e) {
        std::cout << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}