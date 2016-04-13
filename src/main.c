#include <stdio.h>
#include <stdlib.h>

#include "http_node.h"
#include "http_parser.h"
#include "api.h"
#include "http_response.h"

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

			if ( rc_pathname = get_HTTP_Node_value ( requete->buf, & found_HTTP_Node ( http_message, "absolute-path" ) [0] ) ) { // on récupère l'absolute-path 
			} else { // par défaut on envoie l'index
				rc_pathname = "/index.html";
			}
			
			if ( reponse.body = read_from_file ( rc_pathname, ROOT_DIR ) ) { // on essaie de trouver la ressources 

				reponse.code = 200;
				send_HTTP_GET_response ( & reponse, requete->clientId );

			} else { // ressource non trouvée => errer 404

				reponse.code = 404;
				reponse.body = read_from_file ( "html_error_pages/404.html", ROOT_DIR );
				send_HTTP_GET_response ( & reponse, requete->clientId );

			}

		} else { // la requete est invalide => erreur 400  
			reponse.code = 400;
			reponse.body = read_from_file ( "html_error_pages/400.html", ROOT_DIR );
			send_HTTP_GET_response ( & reponse, requete->clientId );
		}

		// on ne se sert plus de requete a partir de maintenant, on peut donc liberer... 
		freeRequest ( requete ); 
		free_HTTP_Tree ( http_message );
	}

	return 0;
}
