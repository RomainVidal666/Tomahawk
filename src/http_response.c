#include "http_response.h"

int send_HTTP_GET_response ( HTTP_GET_response * http_reponse, unsigned int clientId ) {
	message * reponse;

	reponse->buf = cast_HTTP_GET_response_to_string ( http_reponse );

	printf ( "%s\n", reponse->buf );	

	/*

	if ( reponse = malloc ( sizeof ( message ) ) ) { 

		reponse->buf = http_reponse->body; 
		reponse->len = strlen ( http_reponse->body ); 
		reponse->clientId = clientId; 

		sendReponse ( reponse ); 

		free ( reponse ); 
		
		requestShutdownSocket ( clientId ); //optionnel, ici on clot la connexion tout de suite (HTTP/1.0) 

		return 1;
	}

	*/

	return 0;
}

char * get_message_code ( int code ) {
	switch ( code ) {
		case 100:
			return "Continue";
			break;

		case 200:
			return "OK";
			break;

		case 400:
			return "Bad Request";
			break;

		case 401:
			return "Unauthorized";
			break;

		case 404:
			return "Not Found";
			break;

		case 418:
			return "I’m a teapot";
			break;
	}

}

char * cast_HTTP_GET_response_to_string ( HTTP_GET_response * response ) {
	//buf.concatener ( tostring ( code ), " ", get_message_code ( code ) );
}