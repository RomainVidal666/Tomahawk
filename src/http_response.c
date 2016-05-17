#include "http_response.h"

int make_HTTP_requete( HTTP_Node * http_message, message * requete ) {
	HTTP_GET_response reponse;
	reponse.headers = NULL;
	char * rc_pathname = NULL;
	int taille;

	if ( rc_pathname = get_HTTP_Node_value ( requete->buf, & found_HTTP_Node ( http_message, "absolute-path" ) [0] ) ) { // on récupère l'absolute-path 

	} else { // par défaut on envoie l'index
		rc_pathname = "/index.html";
	}

	if ( reponse.body = read_from_file ( rc_pathname, ROOT_DIR, &taille ) ) { // on essaie de trouver la ressources 
		printf("taille: %d\n", taille );
		reponse.code = 200;
		reponse.headers = add_HTTP_header ( "Content-Type", get_mime_type(http_message, requete), reponse.headers );

		send_HTTP_GET_response ( & reponse, requete->clientId, taille );

	} else { // ressource non trouvée => erreur 404
		send_HTTP_error( 404, requete->clientId );
	}
	return 1;
}

int send_HTTP_error ( int errNumber, int clientId ) {
	char * pathname = NULL;
	HTTP_GET_response response;
	char str[3];
	int taille;

	response.headers = NULL;
	response.code = errNumber;
	sprintf(str, "%d", errNumber);

	response.body = read_from_file ( strcat_without_alloc ( strcat_without_alloc ( "html_error_pages/", str ), ".html" ), ROOT_DIR, &taille );

	send_HTTP_GET_response ( & response, clientId, taille );
	
	return 1;
}

int send_HTTP_GET_response ( HTTP_GET_response * http_reponse, unsigned int clientId, int body_length ) {
	message * reponse;
	char content_length [512];
	int header_length;

	snprintf ( content_length, 512, "%d", body_length );

	if ( reponse = malloc ( sizeof ( message ) ) ) { 
		/* headers minimaux si il y a un message-body */
		http_reponse->headers = add_HTTP_header ( "Server", "Tomahawk/1.0", http_reponse->headers );
		
		http_reponse->headers = add_HTTP_header ( "Content-Length", content_length, http_reponse->headers );

		reponse->buf = cast_HTTP_GET_response_to_string ( http_reponse );
		header_length = strlen ( reponse->buf );
		//reponse->buf = strcat_without_alloc ( reponse->buf, http_reponse->body );
		reponse->buf = strcat_without_alloc_with_length ( reponse->buf, http_reponse->body, body_length );	
		reponse->len = header_length + body_length; 
		printf ( "header_length:%d\n", header_length );	
		printf ( "body_length:%d\n", body_length );	
		printf ( "reponse->len:%d\n", reponse->len );	

		reponse->clientId = clientId; 
		printf ( "(%s)\n", reponse->buf );	
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
		if ( curr_head->name ) {
			str_reponse = strcat_without_alloc ( str_reponse, curr_head->name );
		} else {
			str_reponse = strcat_without_alloc ( str_reponse, "(null)" );
		}
		str_reponse = strcat_without_alloc ( str_reponse, ": " );
		if ( curr_head->value ) {
			str_reponse = strcat_without_alloc ( str_reponse, curr_head->value );
		} else {
			str_reponse = strcat_without_alloc ( str_reponse, "(null)" );
		}
		str_reponse = strcat_without_alloc ( str_reponse, "\r\n" );
		curr_head = curr_head->next;
	}

	/* body */
	str_reponse = strcat_without_alloc ( str_reponse, "\r\n" );
	//str_reponse = strcat_without_alloc ( str_reponse, response->body );

	return str_reponse;
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

char * read_from_file ( char * pathname, char * root_dir, int * taille ) {
	FILE * fichier = NULL;
	unsigned char caractereActuel;
	unsigned char * content = NULL;
	int i, length;

	char * real_pathname = NULL;

	if ( pathname [0] == '/' ) { // on demande la racine du site */
		length = strlen ( pathname );
		real_pathname = malloc ( sizeof ( char ) * ( length - 1 ) );
		for ( i = 1; i <= length; i++ ) {
			real_pathname [i-1] = pathname [i];
		}
	} else {
		real_pathname = pathname;
	}

	real_pathname = strcat_without_alloc ( root_dir, real_pathname );

	*taille = 0;

	if ( fichier = fopen ( real_pathname, "rb" ) ) {
    	while ( ( fread ( & caractereActuel, sizeof ( caractereActuel ), 1, fichier ) ) != 0 ) {
            content = charcat_without_alloc_with_length ( content, caractereActuel, (*taille) );
            (*taille) ++;
            
        }

        fclose ( fichier );
    }

	return content;
}

char * get_mime_type(HTTP_Node * http_message, message * requete) {
	HTTP_Node * node = found_HTTP_Node ( http_message, "request-target" );
	char * str = NULL, * type = NULL, * extension = NULL;

	str = copierChaine ( requete->buf, str, node->beg, node->end );

	// On cherche le point
	if ( str ) {
		extension = strrchr ( str, '.' );
		if ( extension ) {
			// Selon on decide du mime
			//!\ Espace en trop ( pour toute "request-taget" ):/
			if ( ! strcmp ( extension, ".png ") ) {
				type = malloc(10 * sizeof (char));
				type = "image/png"; 
			} else if ( ! strcmp ( extension, ".jpg ") ) {
				type = malloc(11 * sizeof (char));
				type = "image/jpeg"; 
			} else if ( ! strcmp ( extension, ".css ") ) {
				type = malloc(9 * sizeof (char));
				type = "text/css"; 
			} else if ( ! strcmp ( extension, ".js ") ) {
				type = malloc(23 * sizeof (char));
				type = "application/javascript"; 
			} else {
				type = malloc(9 * sizeof (char));
				type = "text/html"; 
			} 

			return type;
		}		
	}

	return "text/html";	
}
