#ifndef UTILITIES_H
#define UTILITIES_H

/*!
 * \file utilities.h
 * \brief Fonctions de manipulation de chaînes utiles.
 * \author R. Vidal / A. Lorber / T. Jacumin
 * \version 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * \fn char * strcat_without_alloc ( char * s1, char * s2 )
 * \brief Fonction pour concaténer s2 à s1 sans avoir à faire d'allocation dynamique.
 *
 * \param s1 Chaîne 1.
 * \param s2 Chaîne 2.
 *
 * \return Retourne la nouvelle chaîne.
*/

char * strcat_without_alloc ( char * s1, char * s2 );

/**
 * \fn char * strcat_without_alloc_with_length ( char * s1, char * s2, int length )
 * \brief Fonction pour concaténer s2 à s1 sans avoir à faire d'allocation dynamique et spécifiant la taille de s1.
 *
 * \param s1 Chaîne 1.
 * \param s2 Chaîne 2.
 * \param length Taille de s1.
 *
 * \return Retourne la nouvelle chaîne.
*/

char * strcat_without_alloc_with_length ( char * s1, char * s2, int length );

/**
 * \fn char * charcat_without_alloc ( char * s1, char c )
 * \brief Fonction pour concaténer c à s1 sans avoir à faire d'allocation dynamique.
 *
 * \param s1 Chaîne 1.
 * \param c Caractère.
 *
 * \return Retourne la nouvelle chaîne.
*/

char * charcat_without_alloc ( char * s1, char c );

/**
 * \fn char * charcat_without_alloc_with_length ( char * s1, char c, int length )
 * \brief Fonction pour concaténer c à s1 sans avoir à faire d'allocation dynamique et spécifiant la taille de s1.
 *
 * \param s1 Chaîne 1.
 * \param c Caractère.
 * \param length Taille de s1.
 *
 * \return Retourne la nouvelle chaîne.
*/

char * charcat_without_alloc_with_length ( char * s1, char c, int length );

/**
 * \fn char * copierChaine(char *buf, char* res, int beg, int end)
 * \brief Fonction pour copier la sous-chaîne entre beg et end de buf dans res.
 *
 * \param buf Chaîne contenant la sous-chaîne.
 * \param res Chaîne qui contiendra le resultat.
 * \param beg Début de la sous-chaîne.
 * \param end Fin de la sous-chaîne.
 * 
 * \return Retourne la sous-chaîne.
*/

char * copierChaine(char *buf, char* res, int beg, int end);

#endif
