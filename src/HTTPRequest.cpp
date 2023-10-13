#include "../inc/HTTPRequest.hpp"

#include <iostream>
#include <sstream>

void HTTPRequest::parse(const std::string& request) 
{
        std::istringstream stream(request);
        stream >> method >> uri >> version;
        parseHeaders(stream);
        parseBody(stream);
}

void HTTPRequest::parseHeaders(std::istringstream& stream)
{
    std::string line;

    while (std::getline(stream, line) && !line.empty())
    {
        size_t pos = line.find(':');
        if (pos != std::string::npos)
        {
            std::string headerName = line.substr(0, pos);
            std::string headerValue = line.substr(pos + 2); // Skip the ': ' part
            headers[headerName] = headerValue;
            if (headerName == "Content-Length")
            {
                break;
            }
        }
    }
}

void HTTPRequest::parseBody(std::istringstream& stream)
{

    std::stringstream bodyStream;
    bodyStream << stream.rdbuf();
    body = bodyStream.str();
}
