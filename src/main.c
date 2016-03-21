#include <stdio.h>
#include <stdlib.h>

#include "http_node.h"
#include "http_parser.h"

int main ( int argc, char * argv [] ) {
	int cursor = 0;
	HTTP_Node * http_message = malloc ( sizeof ( HTTP_Node ) ); 

<<<<<<< HEAD
	// if ( parse_HTTP_message ( "METHOD / HTTP/1.2 153 Coucou !!!! :\n\rD", & cursor, http_message ) ) {
		// printf ( "La requête est valide \n" );
	// }
	if ( parse_HTTP_message ( "METHOD / HTTP/1.2 153 Coucou !!!! :\n\rParam1: 42\n\rParam2: 45addg\n\r\n\r", &cursor, http_message ) ) { //param2:rien\n\r 	\n\r
		printf ( "La requete est valide \n" );
		printf ("%s: %d -> %d\n", http_message->childs[1]->name, 						http_message->childs[1]->beg, 						http_message->childs[1]->end);
		printf ("%s: %d -> %d\n", http_message->childs[1]->childs[0]->name,				http_message->childs[1]->childs[0]->beg, 			http_message->childs[1]->childs[0]->end);
		printf ("%s: %d -> %d\n", http_message->childs[1]->childs[0]->childs[0]->name, 	http_message->childs[1]->childs[0]->childs[0]->beg, http_message->childs[1]->childs[0]->childs[0]->end);
		printf ("%s: %d -> %d\n", http_message->childs[1]->childs[1]->name, 			http_message->childs[1]->childs[1]->beg, 			http_message->childs[1]->childs[1]->end);
		printf ("%s: %d -> %d\n", http_message->childs[1]->childs[1]->childs[0]->name, 	http_message->childs[1]->childs[1]->childs[0]->beg, http_message->childs[1]->childs[1]->childs[0]->end);
=======
	if ( parse_HTTP_message ( "METHOD 122.168.055.5 HTTP/1.2\n\r 153 Coucoddu !!!! :\n\rD", & cursor, http_message ) ) {
		printf ( "La requête est valide \n" );
>>>>>>> refs/remotes/origin/master
	}
	free_HTTP_Tree ( http_message );

	return 0;}