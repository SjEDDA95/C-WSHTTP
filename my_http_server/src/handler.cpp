#include "handler.hpp"
#include "utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <string>

std::string handleRequest(const std::string &request)
{
    // Analyse de la requête HTTP (simple parsing)
    std::istringstream requestStream(request);
    std::string method;
    std::string path;
    std::string httpVersion;

    requestStream >> method >> path >> httpVersion;

    std::cout << "Requête reçue: " << method << " " << path << " " << httpVersion << std::endl;

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
    // Vérifier si le chemin est la racine
    std::string relativePath = path == "/" ? "/index.html" : path;
    std::string fullPath = "../static" + relativePath; // Chemin relatif à partir du répertoire de build

    std::cout << "Chemin complet: " << fullPath << std::endl;

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

std::unordered_map<std::string, std::string> parseHeaders(std::istringstream &requestStream)
{
    std::unordered_map<std::string, std::string> headers;
    std::string line;

    while (std::getline(requestStream, line) && line != "\r")
    {
        std::size_t colon = line.find(':');
        if (colon != std::string::npos)
        {
            std::string name = line.substr(0, colon);
            std::string value = line.substr(colon + 2); // Skip ": "
            headers[name] = value;
        }
    }

    return headers;
}

// Fonction pour obtenir le type MIME en fonction de l'extension de fichier
std::string getMimeType(const std::string &path)
{
    std::unordered_map<std::string, std::string> mimeTypes = {
        {".html", "text/html"},
        {".css", "text/css"},
        {".js", "application/javascript"},
        {".json", "application/json"},
        {".jpg", "image/jpeg"},
        {".jpeg", "image/jpeg"},
        {".png", "image/png"},
        // Ajoutez d'autres types MIME si nécessaire
    };

    std::string extension = path.substr(path.find_last_of("."));
    if (mimeTypes.find(extension) != mimeTypes.end())
    {
        return mimeTypes[extension];
    }
    return "text/plain";
}
