#include "http_parser.h"

int parse_HTTP_message ( char * request, int * cursor, HTTP_Node * node ) {
	HTTP_Node * start_line = NULL;
	HTTP_Node * message_body = NULL;
	HTTP_Node * header_field = NULL;

	init_HTTP_Node ( "http-message", node );
	node->beg = *cursor;
	
	start_line = malloc ( sizeof ( HTTP_Node ) );
	addChild_HTTP_Node ( node, start_line );

	if ( parse_start_line ( request, cursor, start_line ) ) { // On parse la start-line
		DEBUG_PRINT ( "Le start-line est valide\n" );
		header_field = malloc ( sizeof ( HTTP_Node ) );
		init_HTTP_Node ( "header-field", header_field );
		addChild_HTTP_Node ( node, header_field );
		header_field -> beg = *cursor;



		if ( parse_header_field ( request, cursor, header_field ) ) { // On parse le header-field
			
			DEBUG_PRINT ( "Le header-field est valide\n" );
			
			message_body = malloc ( sizeof ( HTTP_Node ) );
			addChild_HTTP_Node ( node, message_body );

			if ( parse_message_body ( request, cursor, message_body ) ) { // On parse le message-body

				DEBUG_PRINT ( "Le message-body est valide\n" );
				node->end = *cursor;

				return 1;
			}
		}
	}
}

int parse_start_line ( char * request, int * cursor, HTTP_Node * node ) {
	HTTP_Node * status_line = NULL;
	HTTP_Node * request_line = NULL;

	init_HTTP_Node ( "start-line", node );
	node->beg = *cursor;

	status_line = malloc ( sizeof ( HTTP_Node ) );
	request_line = malloc ( sizeof ( HTTP_Node ) );

	if ( parse_status_line ( request, cursor, status_line ) ) {

		DEBUG_PRINT ( "- status-line valide\n" );
		node->end = *cursor;
		addChild_HTTP_Node ( node, status_line ); 

		return 1;

	} else if ( parse_request_line ( request, cursor, request_line ) ) {

		DEBUG_PRINT ( "- request-line valide\n" );
		node->end = *cursor;
		addChild_HTTP_Node ( node, request_line ); 

		return 1;

	}
	return 0;
}

int parse_status_line ( char * request, int * cursor, HTTP_Node * node ) { /* TO DO : annuler les déplacement du curseur si le mot n'est pas accepté */
	int requestlength = strlen ( request );
	int end_status_line = 0;
	int old_cursor = *cursor;
	HTTP_Node * http_version = malloc ( sizeof ( HTTP_Node ) );
	HTTP_Node * status_code = malloc ( sizeof ( HTTP_Node ) );
	HTTP_Node * reason_phrase = malloc ( sizeof ( HTTP_Node ) );

	init_HTTP_Node ( "status-line", node );
	node->beg = *cursor;

	init_HTTP_Node ( "HTTP-version", http_version );
	http_version->beg = *cursor;

	init_HTTP_Node ( "status-code", status_code );
	init_HTTP_Node ( "reason-phrase", reason_phrase );

	addChild_HTTP_Node ( node, http_version );
	addChild_HTTP_Node ( node, status_code );
	addChild_HTTP_Node ( node, reason_phrase );
	
	/* status-line*/
	if ( parse_string ( request, cursor, "HTTP/" ) && /* HTTP-version */
		 isDIGIT ( request, cursor ) &&  
		 parse_string ( request, cursor, "." ) &&
		 isDIGIT ( request, cursor ) ) {

		http_version->end = *cursor;

		DEBUG_PRINT("-- HTTP-version valide\n");
		if ( parse_string ( request, cursor, " " ) ) { /* SP */
			status_code->beg = *cursor;
			if ( isDIGIT ( request, cursor ) && isDIGIT ( request, cursor ) && isDIGIT ( request, cursor ) ) { /* status-code */
				status_code->end = *cursor;
				DEBUG_PRINT("-- status-code valide\n");
				if ( parse_string ( request, cursor, " " ) ) { /* SP */
					reason_phrase->beg = *cursor;
					while ( ( requestlength > *cursor ) && ( ! end_status_line ) ) { /* reason-phrase */
						end_status_line = parse_string ( request, cursor, "\n\r" );

						if ( ! end_status_line ) {
							*cursor = *cursor + 1;
							reason_phrase->end = *cursor;
						}
					}
					DEBUG_PRINT ( "-- reason-phrase valide\n" );
					node->end = *cursor;
					return end_status_line; /* retourne 1 si on a trouvé le \n\r, 0 sinon */
				}
			}
		}
	}

	*cursor = old_cursor;
	return 0;
}

int parse_request_line ( char * request, int * cursor, HTTP_Node * node ) {

	HTTP_Node * http_version = malloc ( sizeof ( HTTP_Node ) );
	HTTP_Node * request_target = malloc ( sizeof ( HTTP_Node ) );
	HTTP_Node * method = malloc ( sizeof ( HTTP_Node ) );

	init_HTTP_Node ( "request-line", node );
	node->beg = *cursor;

	init_HTTP_Node ( "method", method );
	addChild_HTTP_Node ( node, method ); 
	method->beg = *cursor;
	isVCHAR ( request, cursor ); /* au moins 1 TCHAR */
	while ( ( request [*cursor] != SP ) && ( isVCHAR ( request, cursor ) ) ); /* TCHAR ici est non pas VCHAR */
	method->end = *cursor;

	init_HTTP_Node ( "HTTP-version", http_version );
	addChild_HTTP_Node ( node, http_version ); 

	if ( request [*cursor] == SP ) { /* ok pour method */

		DEBUG_PRINT("- method valide\n");
		(*cursor) ++;

		if ( parse_request_target ( request, cursor, request_target ) ) {

			http_version->beg = *cursor;

			if ( parse_string ( request, cursor, "HTTP/" ) && /* HTTP-version */
				 isDIGIT ( request, cursor ) &&  
				 parse_string ( request, cursor, "." ) &&
				 isDIGIT ( request, cursor ) ) {

				http_version->end = *cursor;

				if ( parse_string ( request, cursor, "\n\r" ) ) { /* CRLF */
					DEBUG_PRINT ( "- HTTP-version valide\n" );
					addChild_HTTP_Node ( node, request_target ); 
					node->end = *cursor;
					return 1;
				}

			}
		}
	}

	free_HTTP_Node ( request_target );
	return 0;
}

int parse_request_target ( char * request, int * cursor, HTTP_Node * node ) {
	HTTP_Node * origin_form = malloc ( sizeof ( HTTP_Node ) );
	HTTP_Node * absolute_form = malloc ( sizeof ( HTTP_Node ) );
	HTTP_Node * authority_form = malloc ( sizeof ( HTTP_Node ) );

	init_HTTP_Node ( "request-target", node );
	node->beg = *cursor;

	if ( parse_origin_form ( request, cursor, origin_form ) ) {
		node->end = *cursor;
		addChild_HTTP_Node ( node, origin_form );
		free_HTTP_Node ( absolute_form );
		free_HTTP_Node ( authority_form );
		return 1;
	} else if ( parse_absolute_form ( request, cursor, absolute_form ) ) {
		node->end = *cursor;
		addChild_HTTP_Node ( node, absolute_form );
		free_HTTP_Node ( origin_form );
		free_HTTP_Node ( authority_form );
		(*cursor) --;
		return 1;
	} else if ( parse_authority_form ( request, cursor, authority_form ) ) {
		node->end = *cursor;
		addChild_HTTP_Node ( node, authority_form );
		free_HTTP_Node ( absolute_form );
		free_HTTP_Node ( origin_form );
		(*cursor) ++;
		return 1;
	}

	free_HTTP_Node ( origin_form );
	free_HTTP_Node ( absolute_form );
	free_HTTP_Node ( authority_form );

	return 0;
}

int parse_origin_form ( char * request, int * cursor, HTTP_Node * node ) {
	int etat = 0;
	int requestlength = strlen ( request );
	int old_cursor = *cursor;
	HTTP_Node * query = malloc ( sizeof ( HTTP_Node ) );
	HTTP_Node * absolute_path = malloc ( sizeof ( HTTP_Node ) );

	init_HTTP_Node ( "origin-form", node );
	node->beg = *cursor;

	init_HTTP_Node ( "query", query );
	init_HTTP_Node ( "absolute-path", absolute_path );

	addChild_HTTP_Node ( node, absolute_path );

	absolute_path->beg = *cursor;
	if ( parse_string ( request, cursor, "/" ) ) {
		while ( ( *cursor < requestlength ) && ( request [*cursor] != SP ) ) {
			if ( etat == 0 ) { /* abs_path2 */
				absolute_path->end = (*cursor) + 1;
				if ( request [*cursor] == '?' ) {
					absolute_path->end --; /* on enleve le ? */
					etat = 1;
					query->beg = (*cursor) + 1; /* +1 pour enlever le ? */
					addChild_HTTP_Node ( node, query );
				}
			} else if ( etat == 1 ) { /* query */
				query->end = (*cursor) + 1;
			}
			(*cursor)++;
		}

		node->end = *cursor;

		if ( request [*cursor] == SP ) {/* mot accepté */
			(*cursor)++;
			DEBUG_PRINT ( "-- origin-form valide\n" );
			return 1;
		}
	} 	

	free_HTTP_Node ( query );
	free_HTTP_Node ( absolute_path );

	*cursor = old_cursor;
	return 0; 
}

int parse_absolute_form ( char * request, int * cursor, HTTP_Node * node ) {
	int old_cursor = *cursor;
	int etat = 0;
	HTTP_Node * authority_form = malloc ( sizeof ( HTTP_Node ) );
	HTTP_Node * scheme = malloc ( sizeof ( HTTP_Node ) );
	HTTP_Node * query = malloc ( sizeof ( HTTP_Node ) );

	init_HTTP_Node ( "absolute-form", node );
	init_HTTP_Node ( "scheme", scheme );
	init_HTTP_Node ( "query", query );

	addChild_HTTP_Node ( node, scheme );
	addChild_HTTP_Node ( node, authority_form );

	node->beg = *cursor;
	scheme->beg = *cursor;
	while ( ( request [*cursor] != '\0' ) && ( request [*cursor] != SP ) ) {
		if ( etat == 0 ) { /* scheme */
			if ( ( request [*cursor] >= 'a' ) && ( request [*cursor] <= 'z' ) 
			  || ( request [*cursor] >= 'A' ) && ( request [*cursor] <= 'Z' )  ) {
				etat = 1;
				DEBUG_PRINT ( "-- scheme valide\n" );
			} else {
				etat = -1;
			}
		} else if ( etat == 1 ) { /* scheme 2 */
			if ( request [*cursor] == ':' ) {
				scheme->end = (*cursor);
				etat = 2;
			}

		} else if ( etat == 2 ) {
			if ( ( parse_string ( request, cursor ,"//" ) ) && ( parse_authority_form ( request, cursor, authority_form ) ) ) {
				if ( request [*cursor] == '?' ) {
					etat = 3;
					query->beg = (*cursor) + 1;
					addChild_HTTP_Node ( node, query );
				} else {
					DEBUG_PRINT("- absolute-forme valide\n");
					(*cursor)++;
					node->end = *cursor - 1; /* on enlève l'espace final */
					return 1;
				}
				DEBUG_PRINT ( "- hier-part valide\n" );
			} else {
				etat = -1;
			}

		} else if ( etat == 3 ) { /* query */
			query->end = (*cursor) + 1;
		} else {
			*cursor = old_cursor;
			return 0;
		}
		(*cursor) ++;
	}

	if ( etat == 3 ) {
		DEBUG_PRINT("- absolute-forme valide\n");
		(*cursor)++;
		node->end = *cursor - 1; /* on enlève l'espace final */
		return 1;
	}

	free_HTTP_Node ( node );
	free_HTTP_Node ( scheme );
	free_HTTP_Node ( query );
	*cursor = old_cursor;
	return 0;
}

int parse_authority_form ( char * request, int * cursor, HTTP_Node * node ) {
	int etat = 0;
	int requestlength = strlen ( request );
	int old_cursor = *cursor;

	HTTP_Node * port = malloc ( sizeof ( HTTP_Node ) );
	HTTP_Node * user_info = malloc ( sizeof ( HTTP_Node ) );
	HTTP_Node * ipv4 = malloc ( sizeof ( HTTP_Node ) );
	HTTP_Node * regname = malloc ( sizeof ( HTTP_Node ) );

	init_HTTP_Node ( "authority-form", node );
	init_HTTP_Node ( "port", port );

	node->beg = *cursor;
	while ( ( *cursor < requestlength ) && ( request [*cursor] != SP ) ) {
		if ( etat == 0 ) { /* authority_1 */
			if ( parse_user_info ( request, cursor, user_info ) ) {
				addChild_HTTP_Node ( node, user_info );
			}
			etat = 1;
		} else if ( etat == 1 ) { /* query */
			if ( parse_IPv4 ( request, cursor, ipv4 ) ) {
				addChild_HTTP_Node ( node, ipv4 );
				if ( request [ *cursor ] == ':' ) { /* vers port */
					etat = 2;
				} else if ( request [ *cursor ] == ' ' ) {
					etat = 3;
				}
			} else if ( parse_regname ( request, cursor, regname ) ) {
				addChild_HTTP_Node ( node, regname );
				if ( request [ *cursor ] == ':' ) { /* vers port */
					etat = 2;
				} else if ( request [ *cursor ] == ' ' ) {
					etat = 3;
				} 
			} else {
				*cursor = old_cursor;
				return 0;
			}
		} else if ( etat == 2 ) { /* fin */
			port->beg = *cursor;
			while ( ( request [ *cursor ] != '\0' ) && ( isDIGIT ( request, cursor ) ) ); /* tant qu'on lit des digits */
			port->end = *cursor;

			addChild_HTTP_Node ( node, port );
			DEBUG_PRINT("--- port valide\n");
			DEBUG_PRINT("-- authority-form valide\n");
			node->end = *cursor;
			return 1;
		} else if ( etat == 3 ) {
			free_HTTP_Node ( port );
			DEBUG_PRINT("-- authority-form valide\n");
			node->end = *cursor;
			return 1;
		}
		(*cursor)++;
	}
	free_HTTP_Node ( node );
	free_HTTP_Node ( port );
	*cursor = old_cursor;
	return 0;
}

int parse_user_info ( char * request, int * cursor, HTTP_Node * node ) {
	int old_cursor = *cursor;
	int taille = 0;

	init_HTTP_Node ( "user-info", node );

	node->beg = *cursor;
	while ( ( request [ *cursor ] != '\0' ) && ( isUnreserved ( request, cursor ) ) ) {
		taille ++;
	}
	node->end = *cursor;

	if ( ( request [ *cursor ] != '\0' ) && ( request [ *cursor ] == '@' ) && ( taille > 0 ) ) {
		DEBUG_PRINT("--- user-info valide\n");
		return 1;
	}

	free_HTTP_Node ( node );
	*cursor = old_cursor;
	return 0;
}

int parse_regname ( char * request, int * cursor, HTTP_Node * node ) {
	init_HTTP_Node ( "regname", node );
	node->beg = *cursor;
	while ( ( request [ *cursor ] != '\0' ) && ( isUnreserved ( request, cursor ) ) );
	node->end = *cursor;
	DEBUG_PRINT("--- regname valide\n");
	return 1;
}

int parse_IPv4 ( char * request, int * cursor, HTTP_Node * node ) {
	int etat = 0;
	int requestlength = strlen ( request );
	int old_cursor = *cursor;
	int nb_digit = 0;

	init_HTTP_Node ( "IPv4", node );
	node->beg = *cursor;
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
		DEBUG_PRINT ( "--- IPv4 validée\n" );
		node->end = *cursor;
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
}

int isUnreserved ( char * request, int * cursor ) {
	if ( ( request [ (*cursor) ] >= 'a' ) && ( request [ (*cursor) ] <= 'z' )
	  || ( request [ (*cursor) ] >= 'A' ) && ( request [ (*cursor) ] <= 'Z' )  ) { /* ALPHA */
	  	(*cursor)++;
		return 1;
	} else if ( ( request [ (*cursor) ] >= '0') && ( request [ (*cursor) ] <= '9' ) ) { /* DIGIT */
		(*cursor)++;
		return 1;	
	} else if ( ( request [ (*cursor) ] == '.' ) || ( request [ (*cursor) ] == '_' ) || ( request [ (*cursor) ] == '~' ) ) {
		(*cursor)++;
		return 1;
	}
	return 0;
}