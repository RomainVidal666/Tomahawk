#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "request.h"   

int main(int argc, char *argv[])
{
	message *requete; 
	message *reponse;

	while ( 1 ) {
		// on attend la recpetion d'une requete 
		requete=getRequest(8080);

		// Affichage de debug 
		printf("#########################################\nDemande recue depuis le client %d\n",requete->clientId); 
		printf("Client [%d] [%s:%d]\n",requete->clientId,inet_ntoa(requete->clientAddress->sin_addr),htons(requete->clientAddress->sin_port));
		printf("Contenu de la demande %.*s\n\n",requete->len,requete->buf);  

		// Si on a une reponse a faire
		if (argv[1]) {
			if (reponse=malloc(sizeof(message))) { 
				reponse->buf=argv[1]; // on devrait l'allouer sinon
				reponse->len=strlen(argv[1]); 
				reponse->clientId=requete->clientId; 
				sendReponse(reponse); 
				// reponse est recopiée on peut tout de suite liberer la memoire
				free(reponse); 
				//optionnel, ici on clot la connexion tout de suite (HTTP/1.0) 
				requestShutdownSocket(reponse->clientId); 
			}
		} 		
		// on ne se sert plus de requete a partir de maintenant, on peut donc liberer... 
		freeRequest(requete); 
	}

	return (1);
}
