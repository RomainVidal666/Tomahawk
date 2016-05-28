#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "request.h"
#include "utilities.h"
#include "http_parser.h"
#include "request.h"
#include "percent_encoding.h"
#include "config.h"

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
};

typedef struct HTTP_POST HTTP_POST;
struct  HTTP_POST {
	char * name;
	int beg;
	int end;
	HTTP_POST * next;
};

int make_HTTP_requete( HTTP_Node * http_message, message * requete );

HTTP_header * add_HTTP_header ( char * name, char * value, HTTP_header * root );
void free_HTTP_header ( HTTP_header * root );

char * get_message_code ( int code );
char * get_mime_type(HTTP_Node * http_message, message * requete);

char * read_from_file ( char * pathname, char * root_dir, unsigned long long * taille );

char * cast_HTTP_GET_response_to_string ( HTTP_GET_response * response );
int send_HTTP_GET_response ( HTTP_GET_response * http_reponse, unsigned int clientId, unsigned long long body_length );
int send_HTTP_error ( int errNumber, int clientId, char * root_dir );


char * cast_HTTP_POST_response_to_string ( HTTP_GET_response * response );
int send_HTTP_POST_response ( HTTP_GET_response * http_reponse, unsigned int clientId );

HTTP_POST * add_HTTP_POST ( int beg, int end, HTTP_POST * root );
int parse_HTTP_POST ( HTTP_Node * http_message, message * requete );

#endif
