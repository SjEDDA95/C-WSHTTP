#include "server.hpp"
#include "handler.hpp"
#include "utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <thread>
#include <vector>

Server::Server(const std::string &configFilePath)
{
    // Load configuration from JSON file
    loadConfig(configFilePath);
}

void Server::start()
{
    // Initialize and start the server
    std::cout << "Starting server on " << host << ":" << port << std::endl;
    // Implementation of server start logic
}

void Server::loadConfig(const std::string &configFilePath)
{
    // Load configuration from a JSON file
    std::ifstream configFile(configFilePath);
    if (!configFile.is_open())
    {
        throw std::runtime_error("Could not open config file");
    }

    // Parse JSON (simple manual parsing or use a JSON library)
    // This is a placeholder for configuration loading
    host = "0.0.0.0";
    port = 8080;
    rootDir = "static";
    logFile = "logs/server.log";
}
