#include "request.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct HTTP_header HTTP_header;
struct HTTP_header {
	char * name;
	char * value;
	HTTP_header * next;
};

typedef struct HTTP_GET_response HTTP_GET_response;
struct HTTP_GET_response {
	int code;
	char * body;
	HTTP_header * headers;
	/* d'autre */
};


/* thomas */
HTTP_header * add_HTTP_header ( char * name, char * value, HTTP_header * root );

void free_HTTP_header ( HTTP_header * root );

char * get_message_code ( int code );

char * strcat_without_alloc ( char * s1, char * s2 );


/* bob */
char * cast_HTTP_GET_response_to_string ( HTTP_GET_response * response );

int send_HTTP_GET_response ( HTTP_GET_response * http_reponse, unsigned int clientId );


/* romain666 */

char * cast_HTTP_POST_response_to_string ( HTTP_GET_response * response );

int send_HTTP_POST_response ( HTTP_GET_response * http_reponse, unsigned int clientId );