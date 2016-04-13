#include "http_response.h"

int send_HTTP_GET_response ( HTTP_GET_response * http_reponse, unsigned int clientId ) {
	message * reponse;
	char content_length [512];
	snprintf ( content_length, 512, "%d", strlen ( http_reponse->body ) );
	
	if ( reponse = malloc ( sizeof ( message ) ) ) { 

		/* headers minimaux si il y a un message-body */
		http_reponse->headers = add_HTTP_header ( "Server", "Tomahawk/1.0", http_reponse->headers );
		http_reponse->headers = add_HTTP_header ( "Content-Type", "text/html", http_reponse->headers );
		http_reponse->headers = add_HTTP_header ( "Content-Length", content_length, http_reponse->headers );
		http_reponse->headers = add_HTTP_header ( "alcohol-type", "Rum", http_reponse->headers );

		reponse->buf = cast_HTTP_GET_response_to_string ( http_reponse );
		printf ( "(%s)\n", reponse->buf );	
	
		reponse->len = strlen ( reponse->buf ); 
		reponse->clientId = clientId; 
		sendReponse ( reponse ); 
		free ( reponse ); 
		requestShutdownSocket ( clientId ); //optionnel, ici on clot la connexion tout de suite (HTTP/1.0) 

		return 1;
	}

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
	char * str_reponse = NULL;
	char code [4];

	HTTP_header * curr_head = response->headers;

	snprintf ( code, 4, "%d", response->code );

	/* start-line */
	str_reponse = strcat_without_alloc ( str_reponse, "HTTP/1.0 " );
	str_reponse = strcat_without_alloc ( str_reponse, code );
	str_reponse = strcat_without_alloc ( str_reponse, " " );
	str_reponse = strcat_without_alloc ( str_reponse, get_message_code ( response->code ) );
	str_reponse = strcat_without_alloc ( str_reponse, "\r\n" );

	/* headers */
	while ( curr_head ) {
		str_reponse = strcat_without_alloc ( str_reponse, curr_head->name );
		str_reponse = strcat_without_alloc ( str_reponse, ": " );
		str_reponse = strcat_without_alloc ( str_reponse, curr_head->value );
		str_reponse = strcat_without_alloc ( str_reponse, "\r\n" );
		curr_head = curr_head->next;
	}

	/* body */
	str_reponse = strcat_without_alloc ( str_reponse, "\r\n" );
	str_reponse = strcat_without_alloc ( str_reponse, response->body );

	return str_reponse;
}

char * strcat_without_alloc ( char * s1, char * s2 ) {
    int old_size;
    char * t;

    if ( s1 ) {
    	old_size = strlen ( s1 );
	} else {
		old_size = 0;
	}

    t = malloc ( sizeof ( char ) * ( old_size + strlen ( s2 ) + 1 ) );
    if ( s1 ) {
    	strcpy ( t, s1 );
	}
    strcpy ( t + old_size, s2 );
    
	return t;
}

char * charcat_without_alloc ( char * s1, char c ) {
    int old_size;
    char * t;

    if ( s1 ) {
    	old_size = strlen ( s1 );
	} else {
		old_size = 0;
	}

    t = malloc ( sizeof ( char ) * ( old_size + 2 ) );
    if ( s1 ) {
    	strcpy ( t, s1 );
	}
    t[old_size] = c;
    t[old_size + 1] = '\0';

	return t;
}

HTTP_header * add_HTTP_header ( char * name, char * value, HTTP_header * root ) {
	HTTP_header * current = root;
	if ( root ) {
		while ( current->next != NULL ) {
			current = current->next;
		}
		current->next = malloc ( sizeof ( HTTP_header ) );
		current->next->name = name;
		current->next->value  = value;
		current->next->next = NULL;
	} else {
		root = malloc ( sizeof ( HTTP_header ) );
		root->name = name;
		root->value  = value;
		root->next = NULL;
	}

	return root;
}

char * read_from_file ( char * pathname ) {
	FILE * fichier = NULL;
	char caractereActuel;
	char * content = NULL;

    if ( fichier = fopen ( pathname, "r" ) ) {
    	caractereActuel = fgetc ( fichier );
    	while ( caractereActuel != EOF ) {
            content = charcat_without_alloc ( content, caractereActuel );
            caractereActuel = fgetc ( fichier );
        }
        fclose ( fichier );

    }

	return content;
}