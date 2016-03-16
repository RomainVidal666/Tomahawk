#include "http_parser.h"

int parse_HTTP_message ( char * request, int * cursor, HTTP_Node * node ) {
	HTTP_Node * start_line;
	HTTP_Node * message_body;
	HTTP_Node * header_field;

	init_HTTP_Node ( "http-message", node );
	node->beg = *cursor;

	start_line = malloc ( sizeof ( HTTP_Node ) );
	addChild_HTTP_Node ( node, start_line );

	if ( parse_start_line ( request, cursor, start_line ) ) { // On parse la start-line

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

// int parse_header_field ( char * request, int * cursor, HTTP_Node * node ) {
	// init_HTTP_Node ( "header-field", node );
	
	// int cursor_sec;		/* curseur de secours, si il a pris le mauvais vhemin */
	
	// while ( ! parse_string ( request, cursor, "\n\r" ) ) { /* CRLF */
		// /*field_name*/
		// if ( isTchar ( request, cursor ) ) {	/*tchar*/			
			// while ( isTchar ( request, cursor ) );	/* *(tchar)*/
			// if( parse_string ( request, cursor, ":" ) ) {
				// while( parse_string ( request, cursor, " " ) || parse_string ( request, cursor, "	") );
				// /*field-value*/
				// if ( isObstext ( request, cursor ) || isVCHAR ( request, cursor ) ) {	/* field-content */
					// if( parse_string ( request, cursor, " " ) || parse_string ( request, cursor, "	" ) ) {	/* SP or HTAB */
						// if( isObstext ( request, cursor ) || isVCHAR ( request, cursor ) )	
					// }
				// }
				// else if ( parse_string ( request, cursor, "\n\r") ) {		/* obs-fold */
					
				// }
				// else return 0;
			// }
			// else return 0;
		// }
		// else return 0;
	// }
	// return 1;
// }

int parse_header_field ( char * request, int * cursor, HTTP_Node * node ) {
	init_HTTP_Node ( "header-field", node );
	
	int cursor_sec;		/* curseur de secours, si il a pris le mauvais vhemin */
	
	while ( ! parse_string ( request, cursor, "\n\r" ) ) { /* CRLF */
		/*field_name*/
		parse_field_name( request, cursor, node );
				
			}
			else return 0;
		}
		else return 0;
	}
	return 1;
}

int parse_field_name ( char * request, int * cursor, HTTP_Node * node ) {
	if ( isTchar ( request, cursor ) ) {	/*tchar*/			
		while ( isTchar ( request, cursor ) );	/* *(tchar)*/
		if( parse_string ( request, cursor, ":" ) ) {
			while( parse_string ( request, cursor, " " ) || parse_string ( request, cursor, "	") );
			return( parse_field_value ( request, cursor, node ) );
		}
	}
	return 0;
}

int parse_field_value ( char * request, int * cursor, HTTP_Node * node ) {
	int curs_sec;
	if ( isFieldvchar ( request, cursor ) ) {	/* field-content */
		return ( parse_field_content ( request, cursor ) );
	}
	curs_sec = *cursor;							/* 2 possibilitees: retourner dans header field avec OWS CRLF, ou aller dans obs_fold avec CRLF */
	if (parse_string ( request, cursor, "\n\r" ) ) { /* CRLF */
		if ( parse_obs_fold ( request, cursor, node ) )
			return 1;
	}
	*cursor = curs_sec;
	while ( parse_string ( request, cursor, " " ) || parse_string ( request, cursor, "	" ) );	/* OWS */
	if (parse_string ( request, cursor, "\n\r" ) ) { /* CRLF */
		return ( parse_header_field ( request, cursor, node ) );
	}
	return 0;
}

int parse_field_content ( char * request, int * cursor, HTTP_Node * node ) {
	int curs_sec;
	while ( isFieldvchar ( request, cursor ) );
	if ( parse_string ( request, cursor, " " ) || parse_string ( request, cursor, "	" ) ) {	/* SP or HTAB */
			if( isFieldvchar( request, cursor ) )
				return ( parse_field_content ( request, cursor, node ) );
			else
				return 0;
	}
	curs_sec = *cursor;							/* 2 possibilitees: retourner dans header field avec OWS CRLF, ou aller dans obs_fold avec CRLF */
	if (parse_string ( request, cursor, "\n\r" ) ) { /* CRLF */
		if ( parse_obs_fold ( request, cursor, node ) )
			return 1;
	}
	*cursor = curs_sec;
	while ( parse_string ( request, cursor, " " ) || parse_string ( request, cursor, "	" ) );	/* OWS */
	if (parse_string ( request, cursor, "\n\r" ) ) { /* CRLF */
		return ( parse_header_field ( request, cursor, node ) );
	}
	return 0; 
}

int parse_obs_fold ( char * request, int * cursor, HTTP_Node * node ) {
	int curs_sec;
	if ( parse_string ( request, cursor, " " ) || parse_string ( request, cursor, "	" ) ) {	/* SP or HTAB */
		while ( parse_string ( request, cursor, " " ) || parse_string ( request, cursor, "	" ) );	/* OWS */
		if ( parse_string ( request, cursor, "\n\r" ) ) { /* CRLF */
			curs_sec = *cursor;								/* on enregistre le curseur, car on va tester une branche ( car automate non deterministe à cet endroit ) */
			if ( parse_obs_fold ( request, cursor, node ) )	/* soit on retourne en obs_fold_1 */
				return 1;
			*cursor = curs_sec;								/* soit on retourne dans header field */
			return ( parse_header_field ( request, cursor, node ) );
		}
		if ( isFieldvchar ( request, cursor ) )
			return ( parse_field_content ( request, cursor, node) );
	}
	return 0;
}

int parse_message_body ( char * request, int * cursor, HTTP_Node * node ) {
	init_HTTP_Node ( "message-body", node );

	return 1;
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

int isTchar ( char * request, int * cursor ) {
	if ( ( request [ (*cursor) ] >= '0') && ( request [ (*cursor) ] <= '9' ) ||	/*DIGIT*/	/*tchar*/
		 ( request [ (*cursor) ] >= 'a') && ( request [ (*cursor) ] <= 'z' ) ||	/*ALPHA*/
		 ( request [ (*cursor) ] >= 'A') && ( request [ (*cursor) ] <= 'Z' ) ||
		 ( strchr("!#$%&'*+-.^_`|~", request[cursor]) != NULL )) {													
		(*cursor)++;
		return 1;
	}
	return 0;
}

int isVCHAR ( char * request, int * cursor ) {
	if ( ( request [ (*cursor) ] >= 0x21 ) && ( request [ (*cursor) ] <= 0x7E ) ) {	/* visible printing caracteres */
		(*cursor)++;
		return 1;
	}
	return 0;
}

int isObstext ( char * request, int * cursor ) {
	if ( ( request [ (*cursor) ] >= 0x80 ) && ( request [ (*cursor) ] <= 0xFF ) ) {
		(*cursor)++;
		return 1;
	}
	return 0;
}

int isFieldvchar ( char * request, int * cursor ) {
	if ( isObstext ( request, cursor ) || isVCHAR ( request, cursor ) ) {
		return 1;
	}
	return 0;
}