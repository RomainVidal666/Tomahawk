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

/**
 * \var char percent_table[NB_PERCENT_CHAR][3]
 * \brief Tableau de correspondance percent-encoding.
 **/
char percent_table[NB_PERCENT_CHAR][3];

/**
 * \fn void init_percent_table()
 * \brief Fonction pour initialiser le tableau de caractère avec traduction percent encoding.
 */
void init_percent_table();

/**
 * \fn void normalizeURL (char * url)
 * \brief Fonction principale pour normaliser l'URL.
 *
 * \param url Chaîne de caractère contenant l'URL à normaliser.
 * 
 */
void normalizeURL (char * url);

/**
 * \fn void percent_encoding(char * url)
 * \brief Fonction pour appliquer le percent encoding sur les 2 premiers caractères de url.
 *
 * \param url Chaine de caractère comportant la fin de l'URL (à partir du caractère à traiter).
 *
 */
void percent_encoding(char * url);

/**
 * \fn void str_del(char * str, int i)
 * \brief Fonction supprimer le caractère a l'emplacement i dans str.
 *
 * \param str Chaîne de caractère à traiter.
 * \param i Indice du caractère à supprimer.
 * 
 */
void str_del(char * str, int i);

#endif