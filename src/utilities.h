#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * strcat_without_alloc ( char * s1, char * s2 );
char * charcat_without_alloc ( char * s1, char c );
char * copierChaine(char *buf, char* res, int beg, int end);

#endif
