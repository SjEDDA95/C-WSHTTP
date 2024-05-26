#include "server.hpp"
#include "handler.hpp"
#include "utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <thread>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

Server::Server(const std::string &configFilePath)
{
    // Charger la configuration depuis le fichier JSON
    loadConfig(configFilePath);
}

void Server::start()
{
    // Initialiser le socket
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Créer le socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Attacher le socket au port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    std::cout << "Serveur démarré sur " << host << ":" << port << std::endl;

    // Boucle principale pour accepter les connexions
    while (true)
    {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
        {
            perror("accept");
            continue;
        }

        // Gérer chaque connexion dans un thread séparé
        std::thread(&Server::handleClient, this, new_socket).detach();
    }
}

void Server::loadConfig(const std::string &configFilePath)
{
    // Charger la configuration depuis un fichier JSON (implémentation simple)
    std::ifstream configFile(configFilePath);
    if (!configFile.is_open())
    {
        throw std::runtime_error("Impossible d'ouvrir le fichier de configuration");
    }

    // Parsing JSON (simplifié)
    // Vous pouvez utiliser une bibliothèque JSON pour C++ pour une implémentation plus robuste
    host = "0.0.0.0";
    port = 8080;
    rootDir = "static";
    logFile = "logs/server.log";
}

void Server::handleClient(int clientSocket)
{
    // Lire la requête du client
    char buffer[1024] = {0};
    read(clientSocket, buffer, 1024);

    // Déléguer le traitement de la requête à handler.cpp
    std::string request(buffer);
    std::string response = handleRequest(request);

    // Envoyer la réponse au client
    send(clientSocket, response.c_str(), response.size(), 0);

    // Fermer le socket client
    close(clientSocket);
}
