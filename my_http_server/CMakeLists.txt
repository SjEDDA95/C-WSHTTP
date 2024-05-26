cmake_minimum_required(VERSION 3.10)
project(MyHTTPServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Ajouter les sources
set(SOURCES
    src/main.cpp
    src/server.cpp
    src/handler.cpp
    src/utils.cpp
)

# Inclure les en-têtes
include_directories(src)

# Générer l'exécutable
add_executable(my_http_server ${SOURCES})

