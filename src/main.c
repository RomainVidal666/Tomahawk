#include <stdio.h>
#include <stdlib.h>

#include "http_node.h"
#include "http_parser.h"

int main ( int argc, char * argv [] ) {
	int cursor = 0;
	HTTP_Node * http_message = malloc ( sizeof ( HTTP_Node ) ); 

	char request [] = "METHOD / HTTP/1.2 153 Coucou !!!! :\n\rParam1: 42\n\rParam2: 45addg\n\r\n\r";

	if ( parse_HTTP_message ( request, &cursor, http_message ) ) { //param2:rien\n\r 	\n\r
		printf ( "La requete est valide \n" );

		print_HTTP_Tree ( request, http_message, 0 );

	}
	
	free_HTTP_Tree ( http_message );

	return 0;
}