#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * strcat_without_alloc ( char * s1, char * s2 );
char * strcat_without_alloc_with_length ( char * s1, char * s2, int length );
char * charcat_without_alloc ( char * s1, char c );
char * charcat_without_alloc_with_length ( char * s1, char c, int length );
char * copierChaine(char *buf, char* res, int beg, int end);

#endif
