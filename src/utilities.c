#include "utilities.h"

char * strcat_without_alloc ( char * s1, char * s2 ) {
    int old_size;
    char * t;

    if ( s1 ) {
    	old_size = strlen ( s1 );
	} else {
		old_size = 0;
	}

    t = malloc ( sizeof ( char ) * ( old_size + strlen ( s2 ) + 1 ) );
    if ( s1 ) {
    	strcpy ( t, s1 );
	}
    strcpy ( t + old_size, s2 );
    
	return t;
}

char * charcat_without_alloc ( char * s1, char c ) {
    int old_size;
    char * t;

    if ( s1 ) {
    	old_size = strlen ( s1 );
	} else {
		old_size = 0;
	}

    t = malloc ( sizeof ( char ) * ( old_size + 2 ) );
    if ( s1 ) {
    	strcpy ( t, s1 );
	}
    t[old_size] = c;
    t[old_size + 1] = '\0';

	return t;
}

char* copierChaine(char *buf, char* res, int beg, int end) {
    // Variables locale
    int i = 0, j = 0;

    // On recopie la chaine
    for (i = beg; i < end; i++ ) {
        res[j++] = buf[i];
    }

    // On ajoute un zero de fin de chaine
    res[j] = '\0';

    return res;
}
