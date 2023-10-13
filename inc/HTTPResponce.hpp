#pragma once

#include <string>
#include <map>
#include <sstream>

class HTTPResponse
{
public:
    int status;
    std::string statusText;
    std::map<std::string, std::string> headers;
    std::string body;

    std::string toString() const
    {
        std::ostringstream response;
        response << "HTTP/1.1 " << status << " " << statusText << "\r\n";
        for (const auto& pair : headers)
        {
            response << pair.first << ": " << pair.second << "\r\n";
        }
        response << "\r\n";
        response << body; // Include the response body
        return response.str();
    }
};
