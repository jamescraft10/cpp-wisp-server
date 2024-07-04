#include <iostream>
#include <stdexcept>
#include <crow_all.h>

#include "request.h"

constexpr int BUFFER_SIZE = 1024;
constexpr int PORT = 3000;

int main() {
    try {
        crow::SimpleApp app;

        CROW_ROUTE(app, "/index.html")([](const crow::request& req, crow::response& res){
            res.redirect("/static/index.html");
            res.end();
        });

        CROW_WEBSOCKET_ROUTE(app, "/ws")
        .onopen([&](crow::websocket::connection& conn){
                CROW_LOG_INFO << "new websocket connection";
        })

        .onclose([&](crow::websocket::connection& conn, const std::string& reason){
                CROW_LOG_INFO << "websocket connection closed: " << reason;
        })

        .onmessage([&](crow::websocket::connection& conn, const std::string& data, bool is_binary){
                if (is_binary)
                    conn.send_binary(data);
                else
                    conn.send_text(data);
        });

        app.port(3000)
            .multithreaded()
            .run();
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}