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

char * strcat_without_alloc_with_length ( char * s1, char * s2, int length ) {
    int old_size;
    char * t;
    int i;

    if ( s1 ) {
        old_size = strlen ( s1 );
    } else {
        old_size = 0;
    }

    t = malloc ( sizeof ( char ) * ( old_size + length + 1 ) );
    if ( s1 ) {
        //strcpy ( t, s1 );
        for ( i = 0; i < length; i++ ) {
            t[i] = s1 [i];
        }
    }
    //strcpy ( t + old_size, s2 );
    for ( i = 0; i < length; i++ ) {
        t[i + old_size] = s2 [i];
    }
    
    return t;
}

char * strcat_without_alloc_with_2_length ( char * s1, long int lengths1, char * s2, long int lengths2 ) {
    //char * t;
    long int i;

    //t = malloc ( sizeof ( char ) * ( lengths1 + lengths2 ) );
	s1 = realloc ( s1, sizeof ( char ) * ( lengths1 + lengths2 ) );

    //strcpy ( t, s1 );
    printf("\n\n*********************\n %d : %d \n***********************\n", lengths1, lengths2);
    /*for ( i = 0; i < lengths1; i++ ) {
        t[i] = s1 [i];
    }*/

    //strcpy ( t + old_size, s2 );
    for ( i = 0; i < lengths2; i++ ) {
        s1[i + lengths1] = s2 [i];
    }

    return s1;
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

char * charcat_without_alloc_with_length ( char * s1, char c, int length ) {
    int old_size;
    char * t;
    int i; 

    if ( s1 ) {
        old_size = length;
    } else {
        old_size = 0;
    }

    t = malloc ( sizeof ( char ) * ( old_size + 2 ) );
    if ( s1 ) {
        for ( i = 0; i < length; i++ ) 
            t [i] = s1 [i];
    }
    t[old_size] = c;
    t[old_size + 1] = '\0';

    return t;
}

char * copierChaine(char *buf, char* res, int beg, int end) {
    // Variables locale
    int i = 0, j = 0;
    if ( ( ! res ) && ( beg <= end ) ) {
        res = malloc ( sizeof ( char ) * ( end - beg + 1 ) );
    }

    if ( res ) {
        // On recopie la chaine
        for ( i = beg; i < end; i++ ) {
            res[j++] = buf[i];
        }

        // On ajoute un zero de fin de chaine
        res[j] = '\0';
    }

    return res;
}
