#include <iostream>
#include <string>
#include <stdexcept>
#include <curl/curl.h>

class Client {
    public:
    Client() {
        curl = curl_easy_init();
        if(!curl) {
            throw new std::runtime_error("Couldn't init curl.");
        }
    }

    void request(const char *host, const int port, const char *message) {
        curl_easy_setopt(curl, CURLOPT_URL, host);
        curl_easy_setopt(curl, CURLOPT_PORT, port);
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, message);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }

    std::string buffer;

    private:
    CURL *curl;
    CURLcode res;

    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    }
};