#ifndef PERCENT_ENCODING_H
#define PERCENT_ENCODING_H

/*!
 * \file percent_encoding.h
 * \brief Gestion de la normalisation de l'URL
 * \author R. Vidal / A. Lorber / T. Jacumin
 * \version 1.0
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NB_PERCENT_CHAR 352

void init_percent_table();
void normalizeURL (char * url);
void percent_encoding(char * url);
void str_del(char * str, int i);

char percent_table[NB_PERCENT_CHAR][3];

#endif