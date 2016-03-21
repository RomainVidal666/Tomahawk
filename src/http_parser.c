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
		
		*cursor=38;
		
		header_field = malloc ( sizeof ( HTTP_Node ) );
		init_HTTP_Node ( "header-field", header_field );
		addChild_HTTP_Node ( node, header_field );
		header_field -> beg = *cursor;

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
	} else if ( parse_request_line ( request, cursor, node ) ) {
		printf("- request-target valide\n");
		return 1;
	}

	return 0;
}

int parse_status_line ( char * request, int * cursor, HTTP_Node * node ) { /* TO DO : annuler les déplacement du curseur si le mot n'est pas accepté */
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

int parse_request_line ( char * request, int * cursor, HTTP_Node * node ) {
	isVCHAR ( request, cursor ); /* au moins 1 TCHAR */
	while ( ( request [*cursor] != SP ) && ( isVCHAR ( request, cursor ) ) ); /* TCHAR ici est non pas VCHAR */

	if ( request [*cursor] == SP ) { /* ok pour method */
		printf("- method valide\n");
		(*cursor) ++;
		if ( parse_request_target ( request, cursor, node ) ) {
			if ( parse_string ( request, cursor, "HTTP/" ) && /* HTTP-version */
				 isDIGIT ( request, cursor ) &&  
				 parse_string ( request, cursor, "." ) &&
				 isDIGIT ( request, cursor ) ) {
				if ( parse_string ( request, cursor, "\n\r" ) ) { /* CRLF */
					printf ( "- HTTP-version valide\n" );

					return 1;
				}
			}
		}
	}

	return 0;
}

int parse_request_target ( char * request, int * cursor, HTTP_Node * node ) {
	if ( ( parse_origin_form ( request, cursor, node ) )
	  || ( parse_absolute_form ( request, cursor, node ) )
	  || ( parse_authority_form ( request, cursor, node ) ) ) {
		return 1;
	}
	return 0;
}

int parse_origin_form ( char * request, int * cursor, HTTP_Node * node ) {
	int etat = 0;
	int requestlength = strlen ( request );
	int old_cursor = *cursor;

	if ( parse_string ( request, cursor, "/" ) ) {
		while ( ( *cursor < requestlength ) && ( request [*cursor] != SP ) ) {
			if ( etat == 0 ) { /* abs_path2 */
				if ( request [*cursor] == '?' ) etat = 1;
			} else if ( etat == 1 ) { /* query */

			}
			(*cursor)++;
		}

		if ( request [*cursor] == SP ) {/* mot accepté */
			(*cursor)++;
			printf ( "-- origin-form valide\n" );
			return 1;
		}
	} 	

	*cursor = old_cursor;
	return 0; 
}

int parse_absolute_form ( char * request, int * cursor, HTTP_Node * node ) {
	return 0;
}

int parse_authority_form ( char * request, int * cursor, HTTP_Node * node ) {
	int etat = 0;
	int requestlength = strlen ( request );
	int old_cursor = *cursor;

	while ( ( *cursor < requestlength ) && ( request [*cursor] != SP ) ) {
		if ( etat == 0 ) { /* authority_1 */
			if ( parse_IPv4 ( request, cursor, node ) ) {
				etat = 1;
			} else {
				return 0;
			}

		} else if ( etat == 1 ) { /* query */
			return 1;
		}
		(*cursor)++;
	}

	*cursor = old_cursor;
	return 0;
}

int parse_IPv4 ( char * request, int * cursor, HTTP_Node * node ) {
	int etat = 0;
	int requestlength = strlen ( request );
	int old_cursor = *cursor;
	int nb_digit = 0;

	while ( ( *cursor < requestlength ) && ( request [*cursor] != SP ) && ( request [*cursor] != ':' ) && ( request [*cursor] != '?' ) ) {
		if ( etat == 0 ) { /* 1er groupe */ 
			if ( ( request [ (*cursor) ] >= '0') && ( request [ (*cursor) ] <= '9' ) ) {
				nb_digit ++;
			} else if ( request [ (*cursor) ] == '.' ) {
				if ( ( nb_digit > 0 ) && ( nb_digit <= 3 ) ) {
					nb_digit = 0;
					etat = 1;
				} else { /* nombre incorrect de digits */
					return 0;
				}
			} else {
				return 0;
			}
		} else if ( etat == 1 ) { /* 2eme groupe */
			if ( ( request [ (*cursor) ] >= '0') && ( request [ (*cursor) ] <= '9' ) ) {
				nb_digit ++;
			} else if ( request [ (*cursor) ] == '.' ) {
				if ( ( nb_digit > 0 ) && ( nb_digit <= 3 ) ) {
					nb_digit = 0;
					etat = 2;
				} else { /* nombre incorrect de digits */
					return 0;
				}
			} else {
				return 0;
			}
		} else if ( etat == 2 ) { /* 3eme groupe */
			if ( ( request [ (*cursor) ] >= '0') && ( request [ (*cursor) ] <= '9' ) ) {
				nb_digit ++;
			} else if ( request [ (*cursor) ] == '.' ) {
				if ( ( nb_digit > 0 ) && ( nb_digit <= 3 ) ) {
					nb_digit = 0;
					etat = 3;
				} else { /* nombre incorrect de digits */
					return 0;
				}
			} else {
				return 0;
			}
		} else if ( etat == 3 ) { /* 4eme groupe */
			if ( ( request [ (*cursor) ] >= '0') && ( request [ (*cursor) ] <= '9' ) ) {
				nb_digit ++;
			} else {
				return 0;
			}
		}
		(*cursor)++;
	}

	if ( ( nb_digit > 0 ) && ( nb_digit <= 3 ) && ( etat == 3 ) ) {
		printf ( "--- IPv4 validée\n" );
		return 1;
	}
	*cursor = old_cursor;
	return 0;
}

int parse_header_field ( char * request, int * cursor, HTTP_Node * header_field ) {
	printf("header	%d\n",*cursor);
	fflush(stdout);
	if ( parse_string ( request, cursor, "\n\r" ) ){ /* CRLF */

		header_field -> end = *cursor;
		return 1;	/* Message-Body */
	}
	

	HTTP_Node * field_name = malloc ( sizeof ( HTTP_Node ) );		/* Creation des noeuds pour field-name et field-value */
	HTTP_Node * field_value = malloc ( sizeof ( HTTP_Node ) );
	init_HTTP_Node ("field-value", field_value);
	init_HTTP_Node ("field-name", field_name);
	addChild_HTTP_Node ( field_name, field_value );
	addChild_HTTP_Node ( header_field, field_name );

	printf ("%s: nbr childs: %d \n", header_field->childs[0]->name, header_field->childs[0]->nb_childs);
	printf ("%s: %d -> %d\n", header_field->childs[0]->name, header_field->childs[0]->beg,header_field->childs[0]->end);
	printf ("%s: %d -> %d\n", header_field->childs[0]->childs[0]->name, header_field->childs[0]->childs[0]->beg,header_field->childs[0]->childs[0]->end);


	return( parse_field_name ( request, cursor, header_field, field_name, field_value) );	/* field-name */
}

int parse_field_name ( char * request, int * cursor, HTTP_Node * header_field, HTTP_Node * field_name, HTTP_Node * field_value ) {
	printf("field-name	%d\n",*cursor);
	printf ("%s: nbr childs: %d \n", header_field->childs[0]->name, header_field->childs[0]->nb_childs);
	printf ("%s: %d -> %d\n", header_field->childs[0]->name, header_field->childs[0]->beg,header_field->childs[0]->end);
	printf ("%s: %d -> %d\n", header_field->childs[0]->childs[0]->name, header_field->childs[0]->childs[0]->beg,header_field->childs[0]->childs[0]->end);

	field_name->beg = *cursor;
	if ( isTchar ( request, cursor ) ) {	/*tchar*/
		while ( isTchar ( request, cursor ) );	/* *(tchar)*/
		if( parse_string ( request, cursor, ":" ) ) {
			field_name -> end = *cursor-1;
			while( parse_string ( request, cursor, " " ) || parse_string ( request, cursor, "	") );
			return( parse_field_value ( request, cursor, header_field, field_name, field_value ) );	/* field-value */
		}
	}
	return 0;
}

int parse_field_value ( char * request, int * cursor, HTTP_Node * header_field, HTTP_Node * field_name, HTTP_Node * field_value ) {
	field_value->beg = *cursor;
	printf ("%s: nbr childs: %d \n", header_field->childs[0]->name, header_field->childs[0]->nb_childs);
	printf ("%s: %d -> %d\n", header_field->childs[0]->name, header_field->childs[0]->beg,header_field->childs[0]->end);
	printf ("%s: %d -> %d\n", header_field->childs[0]->childs[0]->name, header_field->childs[0]->childs[0]->beg,header_field->childs[0]->childs[0]->end);

	int curs_sec;
	if ( isFieldvchar ( request, cursor ) ) {	/* field-content */
		return ( parse_field_content ( request, cursor, header_field, field_name, field_value ) );
	}
	curs_sec = *cursor;							/* 2 possibilitees: retourner dans header field avec OWS CRLF, ou aller dans obs_fold avec CRLF */
	if (parse_string ( request, cursor, "\n\r" ) ) { /* CRLF */
		if ( parse_obs_fold ( request, cursor, header_field, field_name, field_value ) )
			return 1;
	}
	*cursor = curs_sec;
	field_value -> end = *cursor;
	while ( parse_string ( request, cursor, " " ) || parse_string ( request, cursor, "	" ) );	/* OWS */
	if (parse_string ( request, cursor, "\n\r" ) ) { /* CRLF */
		return ( parse_header_field ( request, cursor, header_field ) );
	}
	return 0;
}

int parse_field_content ( char * request, int * cursor, HTTP_Node * header_field, HTTP_Node * field_name, HTTP_Node * field_value ) {
	printf ("%s: nbr childs: %d \n", header_field->childs[0]->name, header_field->childs[0]->nb_childs);
	printf ("%s: %d -> %d\n", header_field->childs[0]->name, header_field->childs[0]->beg,header_field->childs[0]->end);
	printf ("%s: %d -> %d\n", header_field->childs[0]->childs[0]->name, header_field->childs[0]->childs[0]->beg,header_field->childs[0]->childs[0]->end);

	printf("field_content	%d\n",*cursor);
	int curs_sec;
	while ( isFieldvchar ( request, cursor ) );
	if ( parse_string ( request, cursor, " " ) || parse_string ( request, cursor, "	" ) ) {	/* SP or HTAB */
			if( isFieldvchar( request, cursor ) )
				return ( parse_field_content ( request, cursor, header_field, field_name, field_value ) );
			else
				return 0;
	}
	curs_sec = *cursor;							/* 2 possibilitees: retourner dans header field avec OWS CRLF, ou aller dans obs_fold avec CRLF */
	if (parse_string ( request, cursor, "\n\r" ) ) { /* CRLF */
		if ( parse_obs_fold ( request, cursor, header_field, field_name, field_value ) )
			return 1;
	}
	*cursor = curs_sec;
	field_value -> end = *cursor;
	while ( parse_string ( request, cursor, " " ) || parse_string ( request, cursor, "	" ) );	/* OWS */
	if (parse_string ( request, cursor, "\n\r" ) ) { /* CRLF */
		return ( parse_header_field ( request, cursor, header_field ) );
	}
	return 0; 
}

int parse_obs_fold ( char * request, int * cursor, HTTP_Node * header_field , HTTP_Node * field_name, HTTP_Node * field_value ) {
	int curs_sec;
	if ( parse_string ( request, cursor, " " ) || parse_string ( request, cursor, "	" ) ) {	/* SP or HTAB */
		while ( parse_string ( request, cursor, " " ) || parse_string ( request, cursor, "	" ) );	/* OWS */
		field_value -> end = *cursor;
		if ( parse_string ( request, cursor, "\n\r" ) ) { /* CRLF */
			curs_sec = *cursor;								/* on enregistre le curseur, car on va tester une branche ( car automate non deterministe à cet endroit ) */
			if ( parse_obs_fold ( request, cursor, header_field, field_name, field_value ) )	/* soit on retourne en obs_fold_1 */
				return 1;
			*cursor = curs_sec;								/* soit on retourne dans header field */
			return ( parse_header_field ( request, cursor, header_field ) );
		}
		if ( isFieldvchar ( request, cursor ) )
			return ( parse_field_content ( request, cursor, header_field, field_name, field_value ) );
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

<<<<<<< HEAD
int isTchar ( char * request, int * cursor ) {
	if ( ( request [ (*cursor) ] >= '0') && ( request [ (*cursor) ] <= '9' ) ||	/*DIGIT*/	/*tchar*/
		 ( request [ (*cursor) ] >= 'a') && ( request [ (*cursor) ] <= 'z' ) ||	/*ALPHA*/
		 ( request [ (*cursor) ] >= 'A') && ( request [ (*cursor) ] <= 'Z' ) ||
		 ( strchr("!#$%&'*+-.^_|`~", request[*cursor]) != NULL )) {													
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
=======
int isVCHAR ( char * request, int * cursor ) {
	if ( ( request [ (*cursor) ] >= 0x21 ) && ( request [ (*cursor) ] <= 0x7e ) ) {
		(*cursor)++;
		return 1;
	}
	
	return 0;
}

int isUnreserved ( char * request, int * cursor ) {
	if ( ( request [ (*cursor) ] >= 'a' ) && ( request [ (*cursor) ] <= 'z' )
	  && ( request [ (*cursor) ] >= 'A' ) && ( request [ (*cursor) ] <= 'Z' )  ) { /* ALPHA */
	  	(*cursor)++;
		return 1;
	} else if ( ( request [ (*cursor) ] >= '0') && ( request [ (*cursor) ] <= '9' ) ) { /* DIGIT */
		(*cursor)++;
		return 1;	
	} else if ( ( request [ (*cursor) ] == ' ' ) || ( request [ (*cursor) ] == '.' || ( request [ (*cursor) ] == '_' ) || ( request [ (*cursor) ] == '~' ) ) ) {
		(*cursor)++;
		return 1;
	}
	
>>>>>>> refs/remotes/origin/master
	return 0;
}