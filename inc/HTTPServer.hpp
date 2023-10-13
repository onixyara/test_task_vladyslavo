#pragma once

#include <string>
#include <map>
#include <iostream>

#include <netinet/in.h>

#include "HTTPRequest.hpp"
#include "HTTPResponce.hpp"

class HTTPServer {
public:
    HTTPServer() : serverSocket(-1) {}

    bool start(int port);

    void handleClientRequest(int clientSocket);
    void handleGet(const HTTPRequest& request, HTTPResponse& response);
    void handlePost(const HTTPRequest& request, HTTPResponse& response);
    void handleDelete(const HTTPRequest& request, HTTPResponse& response);
    void sendResponse(int clientSocket, const HTTPResponse& response);

    void run();

private:
    int serverSocket;
    struct sockaddr_in serverAddr;
    std::map<std::string, std::pair<std::string, std::string>> uriMap;
};