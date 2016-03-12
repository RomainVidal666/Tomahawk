#include "http_parser.h"

int parse_HTTP_message ( char * request, int * cursor, HTTP_Node * node ) {
	HTTP_Node * start_line;
	HTTP_Node * message_body;
	HTTP_Node * header_field;

	init_HTTP_Node ( "http-message", node );

	start_line = malloc ( sizeof ( HTTP_Node ) );
	addChild_HTTP_Node ( node, start_line );

	if ( parse_start_line ( request, cursor, start_line ) ) { // On parse le start-line

		printf ( "Le start-line est valide\n" );
		header_field = malloc ( sizeof ( HTTP_Node ) );
		addChild_HTTP_Node ( node, header_field );

		if ( parse_header_field ( request, cursor, header_field ) ) { // On parse le header-field

			printf ( "Le header-field est valide\n" );
			message_body = malloc ( sizeof ( HTTP_Node ) );
			addChild_HTTP_Node ( node, message_body );

			if ( parse_message_body ( request, cursor, message_body ) ) { // On parse le message-body

				printf ( "Le message-body est valide\n" );
				
				return 1;
			}
		}
	}
	return 0;
}

int parse_start_line ( char * request, int * cursor, HTTP_Node * node ) {
	init_HTTP_Node ( "start-line", node );

	return 1;
}

int parse_header_field ( char * request, int * cursor, HTTP_Node * node ) {
	init_HTTP_Node ( "header-field", node );

	return 1;
}

int parse_message_body ( char * request, int * cursor, HTTP_Node * node ) {
	init_HTTP_Node ( "message-body", node );

	return 1;
}