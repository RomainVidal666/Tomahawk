#include "http_parser.h"

int parse_HTTP_message ( char * request, int * cursor, HTTP_Node * node ) {
	HTTP_Node * start_line;
	HTTP_Node * message_body;
	HTTP_Node * header_field;

	init_HTTP_Node ( "http-message", node );
	node->beg = *cursor;

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
				node->end = *cursor;

				return 1;
			}
		}
	}
	return 0;
}

int parse_start_line ( char * request, int * cursor, HTTP_Node * node ) {
	init_HTTP_Node ( "start-line", node );
	if ( parse_status_line ( request, cursor, node ) ) {
		printf ( "- status-line valide\n" );
		return 1;
	} else if ( parse_request_target ( request, cursor, node ) ) {
		printf("- request-target valide\n");
		return 1;
	}

	return 0;
}

int parse_status_line ( char * request, int * cursor, HTTP_Node * node ) { /* TO DO : annuler les déplacement du curseur si le mot n'est pas accépté */
	int requestlength = strlen ( request );
	int end_status_line = 0;
	
	/* status-line*/
	if ( parse_string ( request, cursor, "HTTP/" ) && /* HTTP-version */
		 isDIGIT ( request, cursor ) &&  
		 parse_string ( request, cursor, "." ) &&
		 isDIGIT ( request, cursor ) ) {

		if ( parse_string ( request, cursor, " " ) ) { /* SP */

			if ( isDIGIT ( request, cursor ) && isDIGIT ( request, cursor ) && isDIGIT ( request, cursor ) ) { /* status-code */

				if ( parse_string ( request, cursor, " " ) ) { /* SP */

					while ( ( requestlength > *cursor ) && ( ! end_status_line ) ) { /* reason-phrase */
						end_status_line = parse_string ( request, cursor, "\n\r" );

						if ( ! end_status_line )
							*cursor = *cursor + 1;
					}

					return end_status_line; /* retourne 1 si on a trouvé le \n\r, 0 sinon */
				}
			}
		}
	}

	return 0;
}

int parse_request_target ( char * request, int * cursor, HTTP_Node * node ) {
	return 1;
}

int parse_header_field ( char * request, int * cursor, HTTP_Node * node ) {
	init_HTTP_Node ( "header-field", node );

	return 1;
}

int parse_message_body ( char * request, int * cursor, HTTP_Node * node ) {
	init_HTTP_Node ( "message-body", node );    // Initialisation de la node pour le resultat

	node->beg = *cursor;                        // Sauvegarde du debut du message body

	while ( request[*cursor] != '\0'            // Caractère fin de text
            && request[*cursor] != EOF) {       // Fin du flux ( rayer la mention inutile )
        *cursor = *cursor + 1;
    };

	node->end = *cursor;                        // Sauvegarde de la fin du message body

	return 1;                                   // Il ne peut pas y avoir d'erreur sur le retour
}

int parse_string ( char * str, int * cursor, char * cmp_str ) {
	int indice = 0;

	while ( (cmp_str [indice] != '\0' ) && ( str [indice + *cursor] == cmp_str [indice] ) ) {
		indice ++;
	}

	if ( strlen ( cmp_str ) == indice ) {
		*cursor = *cursor + indice;
		return 1;
	} else {
		return 0;
	}
}

int isDIGIT ( char * request, int * cursor ) {
	if ( ( request [ (*cursor) ] >= '0') && ( request [ (*cursor) ] <= '9' ) ) {
		(*cursor)++;
		return 1;
	}

	return 0;
}
