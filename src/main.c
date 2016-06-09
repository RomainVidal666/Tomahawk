#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "http_node.h"
#include "http_parser.h"
//#include "api.h"
#include "http_response.h"
#include "percent_encoding.h"
#include "config.h"
#include "fcgi_api.h"
#include "http_analyseur.h"

void quit(int signum) {
	freeConfig();
	exit(0);
}

int main ( int argc, char * argv [] ) {
	message * requete;
	HTTP_Node * http_message, * method; 
	HTTP_GET_response reponse;
	int cursor;
	char * rc_pathname = NULL;
	char * root_dir = NULL;
	char * host_name = NULL;

	init_percent_table ();
	loadConfig();
	
	signal(SIGINT, quit);
        
	while ( 1 ) {
		reponse.headers = NULL;
		http_message = malloc ( sizeof ( HTTP_Node ) );
		cursor = 0;

		requete = getRequest ( 8080 ); // on attend la recepetion d'une requete 

		// Affichage de debug 
		/*printf("#########################################\nDemande recue depuis le client %d\n",requete->clientId); 
		printf("Client [%d] [%s:%d]\n",requete->clientId,inet_ntoa(requete->clientAddress->sin_addr),htons(requete->clientAddress->sin_port));
		printf("Contenu de la demande %.*s\n\n",requete->len,requete->buf); 
	*/
		if ( ( parse_HTTP_message ( requete->buf, & cursor, http_message ) ) && ( analyse(requete->buf, http_message) == 0 ) ) { // la requete est valide 
			
			//print_HTTP_Tree ( requete->buf, http_message, 0 );
                        
            method = found_HTTP_Node ( http_message, "method" );

			if ( HTTP_Node_is_equal ( requete->buf, method, "GET" ) ) {
				make_HTTP_requete(http_message, requete );
			} else if ( HTTP_Node_is_equal ( requete->buf, method, "POST" ) ) {
				parse_HTTP_POST ( http_message, requete );
			} else {
				send_HTTP_error(501, requete->clientId, root_dir);
			}

		} else { // la requete est invalide => erreur 400
			host_name = get_field_value( requete->buf, http_message, "Host" );
			root_dir = findInConfig( host_name );
			free(host_name);
			send_HTTP_error(400, requete->clientId, root_dir);
		}

		// on ne se sert plus de requete a partir de maintenant, on peut donc liberer... 
		freeRequest ( requete ); 
		free_HTTP_Tree ( http_message );
	}
	return 0;
}
