#pragma once

#include <string>
#include <map>

class HTTPRequest {
public:
    std::string method;
    std::string uri;
    std::string version;
    std::map<std::string, std::string> headers;
    std::string body;

public:
    void parse(const std::string& request);

private:
    void parseHeaders(std::istringstream& stream);

    void parseBody(std::istringstream& stream);
};
