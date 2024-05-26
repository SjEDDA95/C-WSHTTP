#include "utils.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

std::string readFile(const std::string &filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "Impossible d'ouvrir le fichier: " << filePath << std::endl;
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void logRequest(const std::string &request)
{
    std::ofstream logFile("../logs/server.log", std::ios_base::app); // Chemin relatif au répertoire de build
    if (!logFile.is_open())
    {
        std::cerr << "Impossible d'ouvrir le fichier de log: ../logs/server.log" << std::endl;
        return;
    }
    logFile << request << std::endl;
}