#include "handler.hpp"
#include "utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>

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

std::string handleRequest(const std::string &request)
{
    logRequest(request);
    std::istringstream requestStream(request);
    std::string method, path, httpVersion;
    requestStream >> method >> path >> httpVersion;

    std::unordered_map<std::string, std::string> headers = parseHeaders(requestStream);

    std::cout << "Requête reçue: " << method << " " << path << " " << httpVersion << std::endl;
    // requête custom avec retour de hello world : curl -X GET  http://localhost:8080/custom
    // CRUD FOR CUSTOM PATH
    if (path == "/custom")
    {
        if (method == "GET")
        {
            return handleCustomRequest();
        }
        else if (method == "HEAD") // todo not implemented yet handleCustomHeadRequest
        {
            return handleCustomRequest();
        }
        else if (method == "POST") // todo not implemented yet handleCustomPostRequest
        {
            return handleCustomRequest();
        }
        else if (method == "PUT") // todo not implemented yet handleCustomPutRequest
        {
            return handleCustomRequest();
        }
        else if (method == "DELETE") // todo not implemented yet handleCustomDeleteRequest
        {
            return handleCustomRequest();
        }
    }

    if (method == "GET")
    {
        return handleGetRequest(path);
    }
    else if (method == "HEAD")
    {
        return handleHeadRequest(path);
    }
    else if (method == "POST")
    {
        return handlePostRequest(path, requestStream);
    }
    else if (method == "PUT")
    {
        return handlePutRequest(path, requestStream);
    }
    else if (method == "DELETE")
    {
        return handleDeleteRequest(path);
    }
    else
    {
        return "HTTP/1.1 501 Not Implemented\r\n\r\n";
    }
}

std::string handleCustomRequest()
{
    // Retour Hello World ou bien un appel a une fonction externe custom(path)
    std::cout << "Hello World " << std::endl;
    std::string response = "HTTP/1.1 200 OK\r\n";
    response += "\r\n";

    return response;
}

std::string handleGetRequest(const std::string &path)
{
    std::string relativePath = path == "/" ? "/index.html" : path;
    std::string fullPath = "../static" + relativePath; // Chemin relatif à partir du répertoire de build

    std::cout << "Chemin complet: " << fullPath << std::endl;

    std::string fileContent = readFile(fullPath);

    if (fileContent.empty())
    {
        return "HTTP/1.1 404 Not Found\r\n\r\n";
    }

    std::string mimeType = getMimeType(relativePath);
    std::string response = "HTTP/1.1 200 OK\r\n";
    response += "Content-Length: " + std::to_string(fileContent.size()) + "\r\n";
    response += "Content-Type: " + mimeType + "\r\n";
    response += "\r\n";
    response += fileContent;

    return response;
}

std::string handleHeadRequest(const std::string &path)
{
    std::string relativePath = path == "/" ? "/index.html" : path;
    std::string fullPath = "../static" + relativePath; // Chemin relatif à partir du répertoire de build

    std::cout << "Chemin complet: " << fullPath << std::endl;

    std::string fileContent = readFile(fullPath);

    if (fileContent.empty())
    {
        return "HTTP/1.1 404 Not Found\r\n\r\n";
    }

    std::string mimeType = getMimeType(relativePath);
    std::string response = "HTTP/1.1 200 OK\r\n";
    response += "Content-Length: " + std::to_string(fileContent.size()) + "\r\n";
    response += "Content-Type: " + mimeType + "\r\n";
    response += "\r\n";

    return response; // Ne pas ajouter le contenu du fichier
}

std::string handlePostRequest(const std::string &path, std::istringstream &requestStream)
{
    // Logique pour gérer la requête POST
    std::string body;
    std::string line;
    while (std::getline(requestStream, line))
    {
        body += line + "\n";
    }

    std::cout << "Body de la requête POST: " << body << std::endl;

    // Ajoutez votre logique de traitement ici

    return "HTTP/1.1 200 OK\r\n\r\n";
}

std::string handlePutRequest(const std::string &path, std::istringstream &requestStream)
{
    // Logique pour gérer la requête PUT
    std::string body;
    std::string line;
    while (std::getline(requestStream, line))
    {
        body += line + "\n";
    }

    std::cout << "Body de la requête PUT: " << body << std::endl;

    // Ajoutez votre logique de traitement ici

    return "HTTP/1.1 200 OK\r\n\r\n";
}

std::string handleDeleteRequest(const std::string &path)
{
    // Logique pour gérer la requête DELETE
    std::cout << "Requête DELETE pour le chemin: " << path << std::endl;

    // Ajoutez votre logique de traitement ici

    return "HTTP/1.1 200 OK\r\n\r\n";
}
