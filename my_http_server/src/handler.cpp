#include "handler.hpp"
#include "utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

std::string handleRequest(const std::string &request)
{
    // Analyse de la requête HTTP (simple parsing)
    std::istringstream requestStream(request);
    std::string method;
    std::string path;
    std::string httpVersion;

    requestStream >> method >> path >> httpVersion;

    // Logique de traitement de la requête en fonction de la méthode
    if (method == "GET")
    {
        return handleGetRequest(path);
    }
    else
    {
        return "HTTP/1.1 501 Not Implemented\r\n\r\n";
    }
}

std::string handleGetRequest(const std::string &path)
{
    // Serveur de fichiers statiques
    std::string fullPath = "static" + path;
    std::string fileContent = readFile(fullPath);

    if (fileContent.empty())
    {
        return "HTTP/1.1 404 Not Found\r\n\r\n";
    }

    std::string response = "HTTP/1.1 200 OK\r\n";
    response += "Content-Length: " + std::to_string(fileContent.size()) + "\r\n";
    response += "Content-Type: text/html\r\n"; // Simplifié pour les fichiers HTML
    response += "\r\n";
    response += fileContent;

    return response;
}
