# Instructions ETNA

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

# Pour lancer le projet <==>

- mkdir build
- cd build
- cmake ..
- make
- ./my_http_server
- ==> http://localhost:8080


# Récap des requetes testées et testables 

- **# Requête GET**
curl -X GET http://localhost:8080/custom

- **# Requête POST**
curl -X POST http://localhost:8080/custom -d "name=value"

- **# Requête PUT**
curl -X PUT http://localhost:8080/custom -d "name=value"

- **# Requête DELETE**
curl -X DELETE http://localhost:8080/custom

- **# Requête HEAD**
curl -I http://localhost:8080/custom

- **# Requête GET pour un fichier statique**
curl -X GET http://localhost:8080/

- **# Requête GET pour un autre fichier statique**
curl -X GET http://localhost:8080/style.css


# Todo next steps (implémentations manquantes)

- [x] Comprendre comme il faut les sockets - le protocole TCP - et ce qu'est un webserver HTTP

- [x] Revoir structure de projet (CMakeLists - dossier de tests - dossier pour serve - et src)

- [ ] Implémenter un test unitaire sur une requête

- [ ] Gestion des requêtes invalides ou incomplètes
Assurez-vous que le serveur renvoie des réponses HTTP appropriées pour les requêtes invalides, telles que `400 Bad Request`.

- [ ] Listage du contenu d'un dossier
Implémentez une fonctionnalité permettant de lister le contenu d'un répertoire. Cette fonctionnalité peut être ajoutée à la méthode `handleGetRequest`.

- [ ] Démonstration des fonctionnalités CRUD
Implémentez et testez les fonctionnalités CRUD pour certaines URL spécifiques. Assurez-vous que ces fonctionnalités sont opérationnelles et bien testées.

- [ ] Réduction du temps de réponse pour les requêtes récurrentes
Ajoutez des mécanismes de mise en cache pour améliorer les performances des requêtes récurrentes.

- [ ] Optimisation des opérations I/O
Utilisez des techniques d'I/O non bloquantes et/ou des pools de threads pour améliorer les performances des opérations I/O.

- [ ] Conformité à la spécification HTTP/1.1
Vérifiez que le parsing des headers et la génération des réponses sont conformes à la spécification HTTP/1.1 (RFC2616).

