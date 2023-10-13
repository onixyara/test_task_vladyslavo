#include "../inc/HTTPServer.hpp"

#include <sys/socket.h>
#include <unistd.h>

bool HTTPServer::start(int port)
{
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket < 0)
    {
        std::cerr << "Error in socket" << std::endl;
        return false;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
    {
        std::cerr << "Error in binding" << std::endl;
        return false;
    }

    if (listen(serverSocket, 10) == 0)
    {
        std::cout << "Listening on port " << port << "..." << std::endl;
        return true;
    }
    else
    {
        std::cerr << "Error in listening" << std::endl;
        return false;
    }
}

void HTTPServer::handleClientRequest(int clientSocket)
{
    char buffer[1024] = {0};
    recv(clientSocket, buffer, sizeof(buffer), 0);

    HTTPRequest request;
    request.parse(buffer);

    HTTPResponse response;

    if (request.method == "GET")
    {
        handleGet(request, response);
    }
    else if (request.method == "POST")
    {
        handlePost(request, response);
    }
    else if (request.method == "DELETE")
    {
        handleDelete(request, response);
    }
    else
    {
        response.status = 405;
        response.statusText = "Method Not Allowed";
    }

    sendResponse(clientSocket, response);
    close(clientSocket);
}

void HTTPServer::handleGet(const HTTPRequest& request, HTTPResponse& response)
{
    if (uriMap.find(request.uri) != uriMap.end())
    {
        const auto& [contentType, body] = uriMap[request.uri];
        response.status = 200;
        response.statusText = "OK";
        response.headers["Content-Type"] = contentType;
        response.body = body;
    }
    else
    {
        response.status = 404;
        response.statusText = "Not Found";
    }
}

void HTTPServer::handlePost(const HTTPRequest& request, HTTPResponse& response)
{
    uriMap[request.uri] = std::make_pair(request.headers.at("Content-Type"), request.body);
    response.status = 200;
    response.statusText = "OK";
}

void HTTPServer::handleDelete(const HTTPRequest& request, HTTPResponse& response)
{
    if (uriMap.find(request.uri) != uriMap.end())
    {
        uriMap.erase(request.uri);
        response.status = 200;
        response.statusText = "OK";
    }
    else
    {
        response.status = 404;
        response.statusText = "Not Found";
    }
}

void HTTPServer::sendResponse(int clientSocket, const HTTPResponse& response)
{
    std::string responseStr = response.toString();
    send(clientSocket, responseStr.c_str(), responseStr.size(), 0);
}

void HTTPServer::run()
{
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);

    while (true)
    {
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
        if (clientSocket < 0)
        {
            std::cerr << "Error in accepting" << std::endl;
            continue;
        }

        handleClientRequest(clientSocket);
    }
}