#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include <vector>
#include <map>
#include <sys/select.h>
#include "HTTPRequest.hpp"
#include "HTTPResponse.hpp"

class Server {
public:
    Server(const std::map<std::string, std::string>& config);
    void run();

private:
    std::map<std::string, std::string> config;
    fd_set master_set, read_set;
    int max_fd;
    std::vector<int> listen_fds;

    void init();
    void createSocket(int port);
    void handleRequest(int client_fd);
    void handleCGI(int client_fd, const std::string& scriptPath, const HTTPRequest& request);
    bool isMethodAllowed(const std::string& uri, const std::string& method);
    std::string getRequestedPath(const std::string& uri);
    void serveFile(int client_fd, const std::string& path);
    void sendErrorResponse(int client_fd, int status_code, const std::string& status_message);
    void sendDirListing(int client_fd, const std::string& uri, const std::string& path);
    std::string getMimeType(const std::string& path);
    std::string readFile(const std::string& path);
    std::string intToString(int num);
};

#endif
