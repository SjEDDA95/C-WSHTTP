#include "server.hpp"

int main(int argc, char *argv[])
{
    // Créer une instance de Server avec le chemin relatif du fichier de configuration
    Server server("../config/server_config.json");

    // Démarrer le serveur
    server.start();

    return 0;
}
