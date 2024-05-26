#include "server.hpp"

int main(int argc, char *argv[])
{
    Server server("config/server_config.json");
    server.start();
    return 0;
}