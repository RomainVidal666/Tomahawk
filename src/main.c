#include <stdio.h>
#include <stdlib.h>

#include "http_node.h"
#include "http_parser.h"
//#include "api.h"
#include "http_response.h"
#include "percent_encoding.h"

#define ROOT_DIR "www/"

void callback(char* string, int len) {
    printf("CALLBACK : Trouve : (%s)\n", string);
}

int main ( int argc, char * argv [] ) {
	message * requete;
	HTTP_Node * http_message; 
	HTTP_GET_response reponse;
	int cursor;
	char * rc_pathname = NULL;

	init_percent_table ();

	//char url [] = "https://en.wikipedia.org:80/%30%2f../.%2Fwiki/Percent-encoding";
	//normalizeURL(url);
	//printf("%s\n", url);
	
	while ( 1 ) {
		reponse.headers = NULL;
		http_message = malloc ( sizeof ( HTTP_Node ) );
		cursor = 0;

		requete = getRequest ( 8080 ); // on attend la recepetion d'une requete 

		// Affichage de debug 
		printf("#########################################\nDemande recue depuis le client %d\n",requete->clientId); 
		printf("Client [%d] [%s:%d]\n",requete->clientId,inet_ntoa(requete->clientAddress->sin_addr),htons(requete->clientAddress->sin_port));
		printf("Contenu de la demande %.*s\n\n",requete->len,requete->buf); 

		if ( parse_HTTP_message ( requete->buf, & cursor, http_message ) ) { // la requete est valide 
			
			//print_HTTP_Tree ( requete->buf, http_message, 0 );
			make_HTTP_requete(http_message, requete );

		} else { // la requete est invalide => erreur 400  
			send_HTTP_error(400, requete->clientId);
		}

		// on ne se sert plus de requete a partir de maintenant, on peut donc liberer... 
		freeRequest ( requete ); 
		free_HTTP_Tree ( http_message );
	}
	return 0;
}
