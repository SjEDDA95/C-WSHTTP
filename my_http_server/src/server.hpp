#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>

class Server
{
public:
    Server(const std::string &configFilePath);
    void start();

private:
    void loadConfig(const std::string &configFilePath);

    std::string host;
    int port;
    std::string rootDir;
    std::string logFile;
};

#endif // SERVER_HPP
