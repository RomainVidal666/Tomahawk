#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "request.h"
#include "utilities.h"
#include "http_parser.h"
#include "request.h"

#define ROOT_DIR "www/"

typedef struct HTTP_header HTTP_header;
struct HTTP_header {
	char * name;
	char * value;
	HTTP_header * next;
};

typedef struct HTTP_GET_response HTTP_GET_response;
struct HTTP_GET_response {
	int code;
	unsigned char * body;
	HTTP_header * headers;
	/* d'autre */
};



int make_HTTP_requete( HTTP_Node * http_message, message * requete );
/* thomas */
HTTP_header * add_HTTP_header ( char * name, char * value, HTTP_header * root );
void free_HTTP_header ( HTTP_header * root );

char * get_message_code ( int code );
char * get_mime_type(HTTP_Node * http_message, message * requete);

char * read_from_file ( char * pathname, char * root_dir, int * taille );

/* bob */
char * cast_HTTP_GET_response_to_string ( HTTP_GET_response * response );
int send_HTTP_GET_response ( HTTP_GET_response * http_reponse, unsigned int clientId, int body_length );
int send_HTTP_error ( int errNumber, int clientId );


/* romain666 */

char * cast_HTTP_POST_response_to_string ( HTTP_GET_response * response );
int send_HTTP_POST_response ( HTTP_GET_response * http_reponse, unsigned int clientId );

#endif
