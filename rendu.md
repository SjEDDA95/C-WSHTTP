# Instructions etna fdp

# Communiquer avec des clients

La logique de communication des clients est effectuée :

- Protocol TCP : (OK) ==> server.cpp => ligne 19 - ligne 33 (socket) - ligne 73(thread) et ligne 92 pour le handleClient

-Todo : ajouter epoll pour la mise en queue des clients
==> Vous devez donc mettre au point une stratégie 
    pour permettre à votre serveur de continuer à 
    servir d'autres requêtes, même lorsqu'il 
    attend que des données arrivent sur une socket.

# Implémenter le protocole HTTP

Vous devez implémenter les opérations basiques telles que:
- Le parsing du header (OK) ==> handler.cpp => ligne 31
- Les méthodes: (OK) ==> handler.cpp => ligne 50
    - GET (OK) ==> handler.cpp => ligne 87
    - HEAD (OK) ==> handler.cpp => ligne 111
    - POST (OK) ==> handler.cpp => ligne 134
    - PUT (OK) ==> handler.cpp => ligne 151
    - DELETE (OK) ==> handler.cpp => ligne 168
- La génération des réponses appropriées 
    ==> handleRequest 50 ==> Ligne 59
    
    Par exemple : Requête reçue: **GET /script.js HTTP/1.1**

# Servir des fichiers 

- Tous les fichiers sont présents dans /my_http_server/static

  Les serve de fichiers sont principalement effectués ici : (OK) ==> handler.cpp => ligne 10 ==> getMimeType
- Des fichiers texte (OK) ==> handler.cpp => ligne 87 ==> handleGetRequest
- Des fichiers HTML (OK) ==> handler.cpp => ligne 87 ==> handleGetRequest
- Des fichiers JSON (OK) ==> handler.cpp => ligne 87 ==> handleGetRequest
- Different types d'images, comme des JPEG ou PNG (OK) ==> handler.cpp => ligne 87 ==> handleGetRequest

# Générer des réponses customisables

- /custom:  output hello world et retourne OK 200

Mise en place d'un chemin /custom pour les implémentations des méthodes CRUD ==> handler.cpp ==> ligne 62
Ajout d'un if global pour /custom pour éviter redondance

Todo : HEAD, POST, DELETE, PUT ==> Donc pour chaque, une méthode spécifique


# Tests Unitaires et Tests fonctionnels

Garnir le CMakeLists



# Todo next steps

- [/] Revoir le code avec Karim
- [ ] Revoir toutes les fonctions avec CHATGPT
- [ ] Essaye de refaire les handler.hpp et handler.cpp avec le main.cpp
- [ ] Implémenter un test unitaire sur une requête
- [ ] Revoir toutes les fonctions avec CHATGPT