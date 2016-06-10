#include "http_response.h"

int make_HTTP_requete( HTTP_Node * http_message, message * requete ) {
	HTTP_GET_response reponse;
	reponse.headers = NULL;
	char * rc_pathname = NULL;
	char * root_dir = NULL;
	char * host_name = NULL;
	unsigned long long taille;

	host_name = get_field_value( requete->buf, http_message, "Host" );
	root_dir = findInConfig( host_name );
	
	free(host_name);

	if ( rc_pathname = get_HTTP_Node_value ( requete->buf, & found_HTTP_Node ( http_message, "absolute-path" ) [0] ) ) { // on récupère l'absolute-path 
        normalizeURL ( rc_pathname );
	} else { // par défaut on envoie l'index
		rc_pathname = "/index.html";
	}

	if ( is_php ( http_message, requete ) ) { /* Le fichier est un script PHP */
		char * msg;
		if ( read_from_fcgi ( rc_pathname, root_dir, &taille ) ) { // on essaie de trouver la ressources 
			printf("ok\n");
			send_fcgi_nav( msg, requete->clientId );
		} else { // ressource non trouvée => erreur 404
			send_HTTP_error( 404, requete->clientId, root_dir );
		}
	} else { /* Le fichier n'est pas un script PHP */ 
		if ( reponse.body = read_from_file ( rc_pathname, root_dir, &taille ) ) { // on essaie de trouver la ressources 
			reponse.code = 200;
			reponse.headers = add_HTTP_header ( "Content-Type", get_mime_type(http_message, requete), reponse.headers );
			send_HTTP_GET_response ( & reponse, requete->clientId, taille );
		} else { // ressource non trouvée => erreur 404
			send_HTTP_error( 404, requete->clientId, root_dir );
		}
	}

	return 1;
}

int send_HTTP_error ( int errNumber, int clientId, char * root_dir ) {
	char * pathname = NULL;
    HTTP_GET_response response;
	char str[3];
	unsigned long long taille;

	response.headers = NULL;
	response.code = errNumber;
	sprintf(str, "%03.3d", errNumber);
	
	if ( response.body = read_from_file ( strcat_without_alloc ( strcat_without_alloc ( "html_error_pages/", str ), ".html" ), root_dir, &taille ) ) {
		send_HTTP_GET_response ( & response, clientId, taille );
		return 1;
	} 

	return 0;
}

int send_HTTP_GET_response ( HTTP_GET_response * http_reponse, unsigned int clientId, unsigned long long body_length ) {
	message * reponse;
	char content_length [512];
    char * header = NULL;
	unsigned long long header_length;
    unsigned long long i, j, k;
        
	snprintf ( content_length, 512, "%d", body_length );

	if ( reponse = malloc ( sizeof ( message ) ) ) { 
	    /* headers minimaux si il y a un message-body */
	    http_reponse->headers = add_HTTP_header ( "Server", "Tomahawk/1.0", http_reponse->headers );
	    http_reponse->headers = add_HTTP_header ( "Content-Length", content_length, http_reponse->headers );

        header = cast_HTTP_GET_response_to_string ( http_reponse );
        header_length = strlen( header );
        reponse->buf = malloc(sizeof(char) * (header_length + body_length) );
        
        k = 0;
        for (i = 0; i < header_length; i++) {
            reponse->buf[k] = header[i];
            k++;
        }
        for (j = 0; j < body_length; j++) {
            reponse->buf[k] = http_reponse->body[j];
            k++;
        }
            
        reponse->len = header_length + body_length; 	
        reponse->clientId = clientId; 
    	sendReponse ( reponse ); 
    	
        free ( http_reponse->body );
        free ( reponse->buf );
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

		case 501:
			return "Not Implemented";
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

char * read_from_file ( char * pathname, char * root_dir, unsigned long long * taille ) {
	FILE * fichier = NULL;
	unsigned char caractereActuel;
	unsigned char * content = NULL;
	int i, length;
        
	char * real_pathname = NULL;
      
	if ( pathname [0] == '/' ) { // on demande la racine du site 
		length = strlen ( pathname );
		real_pathname = malloc ( sizeof ( char ) * ( length ) );
		for ( i = 1; i <= length; i++ ) {
			real_pathname [i-1] = pathname [i];
		}
	} else {
		real_pathname = pathname;
	}

	real_pathname = strcat_without_alloc ( root_dir, real_pathname );

	*taille = 0;

	if ( fichier = fopen ( real_pathname, "rb" ) ) {

            fseek( fichier ,0 ,SEEK_END);
            length = ftell(fichier);
            rewind(fichier);
            content = (char *) malloc( length * sizeof(char) );
            if (content == NULL)
                printf("BUFFER ERROR ------------------------------\n");

            fread( content, 1, length, fichier);
            fclose ( fichier );
            *taille = length;
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
			} else if ( ! strcmp ( extension, ".mp4 ") ) {
				type = malloc(9 * sizeof (char));
				type = "video/mp4"; 
            } else {
				type = malloc(9 * sizeof (char));
				type = "text/html"; 
			} 

			return type;
		}		
	}

	return "text/html";	
}


HTTP_POST * add_HTTP_POST ( int beg, int end, HTTP_POST * root ) {
	HTTP_POST * current = root;
	if ( root ) {
		while ( current->next != NULL ) {
			current = current->next;
		}
		current->next = malloc ( sizeof ( HTTP_POST ) );
		current->next->beg = beg;
		current->next->end  = end;
		current->next->next = NULL;
		current->next->name = NULL;
	} else {
		root = malloc ( sizeof ( HTTP_POST ) );
		root->beg = beg;
		root->end  = end;
		root->name = NULL;
		root->next = NULL;
	}

	return root;
}

int parse_HTTP_POST ( HTTP_Node * http_message, message * requete ) {
	HTTP_Node * body = found_HTTP_Node ( http_message, "message-body" );
	HTTP_POST * post = NULL, * curr;
	int cursor = body->beg;
	int etat = 0, i;

	post = add_HTTP_POST ( 0, 0, post );
	curr = post;
	while ( cursor < body->end ) {
		if ( etat == 0 ) {
			if ( requete->buf [cursor] == '=' ) {
				etat = 1;
				curr->beg = cursor + 1;
			} else {
				curr->name = charcat_without_alloc ( curr->name, requete->buf [cursor] );
			}
		} else if ( etat == 1 ) {
			if ( requete->buf [cursor] == '&' ) {
				etat = 0;
				add_HTTP_POST ( 0, 0, curr );
				curr = curr->next;
			} else {
				curr->end = cursor + 1;
			}
		}
		cursor++;
	}

	/* affichage pour le debug */
	
	printf ( "\n\n--- POST ---\n" );
	curr = post;
	while ( curr ) {
		printf ( "%s = ", curr->name );

		for ( i = curr->beg; i < curr->end; i++ )
			printf("%c", requete->buf [i] );

		printf ( "\n" );

		curr = curr->next;
	}
	printf ( "--- POST ---\n\n" );
	
	/* /!\ ne pas oublier les percents encoding lors de l'envoie a php /!\ */
	make_HTTP_requete ( http_message, requete );

	return 1;
}

int is_php ( HTTP_Node * http_message, message * requete ) {
	HTTP_Node * node = found_HTTP_Node ( http_message, "request-target" );
	char * str = NULL, * type = NULL, * extension = NULL;

	str = copierChaine ( requete->buf, str, node->beg, node->end );

	// On cherche le point
	if ( str ) {
		extension = strrchr ( str, '.' );
		if ( extension ) {
			if ( ! strcmp ( extension, ".php ") ) {
				return 1;
			}
		}		
	}
	return 0;
}
