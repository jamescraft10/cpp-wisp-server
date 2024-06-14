#include <iostream>
#include <string>
#include "client.hpp"

#define BUFFER_SIZE 1024

int main() {
    std::cout << httpsRequestTCP("google.com", 443, "GET / HTTP/1.1\r\n\r\n") << '\n';
    return 0;
}