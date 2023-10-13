#include "inc/HTTPServer.hpp"

constexpr int PORT = 8080;

int main()
{
    HTTPServer server;
    if (server.start(PORT))
    {
        server.run();
    }
    
    return 0;
}