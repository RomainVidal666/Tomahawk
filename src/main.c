#include <stdio.h>
#include <stdlib.h>

#include "http_node.h"
#include "http_parser.h"

int main ( int argc, char * argv [] ) {
	int cursor = 0;
	HTTP_Node * http_message = malloc ( sizeof ( HTTP_Node ) ); 

	if ( parse_HTTP_message ( "HTTP/1.2 153 Coucou !!!! :\n\rD", & cursor, http_message ) ) {
		printf ( "La requête est valide \n" );
	}

	free_HTTP_Tree ( http_message );

	return 0;
}