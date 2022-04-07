#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

// Port d'écoute de la socket
#define PORT 8080
// Adresse d'écoute (toutes les adresses)
#define IP INADDR_ANY
// Taille de la file d'attente
#define BACKLOG 3
// Nombre de connexions clients
#define NB_EVENTS 2
// Taille du tampon de lecture des messages
#define BUFFER_LEN 200
// Commande pour arrêter le serveur
#define EXIT_WORD "exit"

void initAdresse(struct sockaddr_in * adresse);
int initSocket(struct sockaddr_in * adresse);
int waitForClient(int * serverSocket);
void addClientToTab(int * epfd, int * clientSocket);
void manageClient(int * epfd, int * clientSocket);
void addEpollEvent(int * epfd, int * socket);
void delEpollEvent(int * epfd, int * socket);

int main(void) {
	// Création du descripteur EPOLL
	int epfd = epoll_create1(0);
	// Structure contenant les événements EPOLL
	struct epoll_event events[NB_EVENTS];
	// Structure contenant l'adresse
	struct sockaddr_in adresse;
	initAdresse(&adresse);
	// Descripteur de la socket du serveur
	int serverSocket = initSocket(&adresse);
	addEpollEvent(&epfd, &serverSocket);
	int clientSocket;
	while (1) {
		int nfds = epoll_wait(epfd, events, NB_EVENTS, -1);
		for (int i = 0; i < nfds; i++) {
			if (events[i].data.fd == serverSocket) {
				if ((clientSocket = waitForClient(&serverSocket)) != -1) {
					// On ajoute le nouveau client au tableau des descripteurs
					addClientToTab(&epfd, &clientSocket);
				}
			} else if (events[i].events & EPOLLIN) {
				// On a reçu quelque chose
				manageClient(&epfd, &events[i].data.fd);
			}
		}
	}
	close(serverSocket);
	return EXIT_SUCCESS;
}
// Initialisation de la structure sockaddr_in
void initAdresse(struct sockaddr_in * adresse) {
	(*adresse).sin_family = AF_INET;
	(*adresse).sin_addr.s_addr = IP;
	(*adresse).sin_port = htons( PORT);
}
// Démarrage de la socket serveur
int initSocket(struct sockaddr_in * adresse) {
	// Descripteur de socket
	int fdsocket;
	// Nombre d'options
	int opt = 1;
	// Création de la socket en TCP
	if ((fdsocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		printf("Echéc de la création: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	printf("Création de la socket\n");
	// Paramètrage de la socket
	if (setsockopt(fdsocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
			sizeof(opt)) != 0) {
		printf("Echéc de paramètrage: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	printf("Paramètrage de la socket\n");
	// Attachement de la socket sur le port et l'adresse IP
	if (bind(fdsocket, (struct sockaddr *) adresse, sizeof(*adresse)) != 0) {
		printf("Echéc d'attachement: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	printf("Attachement de la socket sur le port %i\n", PORT);
	// Passage en écoute de la socket
	if (listen(fdsocket, BACKLOG) != 0) {
		printf("Echéc de la mise en écoute: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	printf("Mise en écoute de la socket\n");
	return fdsocket;
}
// Attente de connexion d'un client
int waitForClient(int * serverSocket) {
	int clientSocket;
	// Structure contenant l'adresse du client
	struct sockaddr_in clientAdresse;
	int addrLen = sizeof(clientAdresse);
	if ((clientSocket = accept(*serverSocket, (struct sockaddr*) &clientAdresse,
			(socklen_t*) &addrLen)) != -1) {
		// Convertion de l'IP en texte
		char ip[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &(clientAdresse.sin_addr), ip, INET_ADDRSTRLEN);
		printf("Connexion de %s:%i\n", ip, clientAdresse.sin_port);
		// Passage en mode non bloquant
		int opt = 1;
		setsockopt(clientSocket, SOL_SOCKET, SO_KEEPALIVE, &opt, sizeof(1));
	}
	return clientSocket;
}
// Ajoute les clients au tableau
void addClientToTab(int * epfd, int * clientSocket) {
	addEpollEvent(epfd, clientSocket);
	// Nouvelle connexion, envoie du message de bienvenu
	send(*clientSocket, "Entrez 'exit' pour quitter\n",
			strlen("Entrez 'exit' pour quitter\n"), MSG_DONTWAIT);
}
// On traite l'input des clients
void manageClient(int * epfd, int * clientSocket) {
	// Création d'un tampon pour stocker les messages des clients dans la heap
	static char buffer[BUFFER_LEN + 1];
	int len = recv(*clientSocket, buffer, BUFFER_LEN, MSG_DONTWAIT);
	// Booléen pour suivre l'état de la socket
	int isClosed = 0;
	if (len == -1 && errno != EAGAIN) {
		// Une erreur est survenue
		printf("Errno [%i] : %s\n", errno, strerror(errno));
		isClosed = 1;
	} else if (len == 0) {
		// Le client s'est déconnecté (extrémité de la socket fermée)
		isClosed = 1;
	} else if (len > 0) {
		// Ajout du terminateur de chaîne
		buffer[len] = '\0';
		if (strncmp(buffer, EXIT_WORD, 4) == 0) {
			// Le client veut se déconnecter
			send(*clientSocket, "Bye\n", strlen("Bye\n"), 0);
			isClosed = 1;
		} else {
			// On renvoie le texte au client dans un buffer assez grand
			int len = strlen("Vous avez dit : ") + strlen(buffer) + 1;
			char response[len];
			strcpy(response, "Vous avez dit : ");
			strcat(response, buffer);
			// Un seul envoie permet de ne pas surcharger le réseau
			send(*clientSocket, response, strlen(response), 0);
		}
	}
	if (isClosed == 1) {
		// On enlève la socket des événements EPOLL
		delEpollEvent(epfd, clientSocket);
		// La socket est fermé ou le client veut quitter le serveur !
		printf("Fermeture de la connexion avec le client\n");
		// Fermeture de la socket
		close(*clientSocket);
	}
}
// Ajoute un descripteur de socket aux événements EPOLL
void addEpollEvent(int * epfd, int * socket) {
	printf("Ajout de la socket %i dans les événements EPOLL\n", *socket);
	// Structure contenant les événements EPOLL
	struct epoll_event event;
	// Initialisation de la structure
	memset(&event, 0, sizeof(struct epoll_event));
	// On enregistre la socket du serveur comme descripteur EPOLL
	event.data.fd = *socket;
	// On surveille les message entrant, la fermeture de la socket
	event.events = EPOLLIN | EPOLLRDHUP;
	epoll_ctl(*epfd, EPOLL_CTL_ADD, *socket, &event);
}
// Efface un descripteur de socket des événements EPOLL
void delEpollEvent(int * epfd, int * socket) {
	printf("Suppression de la socket %i des événements EPOLL\n", *socket);
	// Structure contenant les événements EPOLL
	struct epoll_event event;
	// Initialisation de la structure
	memset(&event, 0, sizeof(struct epoll_event));
	// On enregistre la socket du serveur comme descripteur EPOLL
	event.data.fd = *socket;
	// On surveille les message entrant, la fermeture de la socket
	event.events = EPOLLIN | EPOLLRDHUP;
	epoll_ctl(*epfd, EPOLL_CTL_DEL, *socket, &event);
}
//Voici ce que l'on peut observer dans la console:
//Création de la socket
//Paramètrage de la socket
//Attachement de la socket sur le port 8080
//Mise en écoute de la socket
//Ajout de la socket 4 dans les événements EPOLL
//Connexion de 127.0.0.1:17607
//Ajout de la socket 5 dans les événements EPOLL
//Suppression de la socket 5 des événements EPOLL
//Fermeture de la connexion avec le client
//Connexion de 127.0.0.1:18119
//Ajout de la socket 5 dans les événements EPOLL
//Connexion de 127.0.0.1:18631
//Ajout de la socket 6 dans les événements EPOLL
//Suppression de la socket 5 des événements EPOLL
//Fermeture de la connexion avec le client

