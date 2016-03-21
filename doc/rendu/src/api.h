#ifndef API_H
#define API_H

/*!
 * \file api.h
 * \brief API du Parseur HTTP 1.0
 * \author R. Vidal / A. Lorber / T. Jacumin
 * \version 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * \fn int parser (char *buf,unsigned int len,char *search, void (*callback)())
 * \brief Fonction demande par l'API de test
 *
 * \param Buf pointeur vers le premier caractère du flux.
 * \param Len longueur du flux à traiter.
 * \param Search champs à chercher.
 * \param Callback fonction de callback.
 *
 * \return -1 si le message est valide syntaxiquement, sinon un entier
 * 		correspondant à l'indice dans la chaine buf ou le parsuer à
 * 		détecter une erreur syntaxique.
 */
int parser (char *buf,unsigned int len,char *search, void (*callback)());

/**
 * \fn char* copierChaine(char *buf, char* res, int beg, int end);
 * \brief Fonction permettant de recopier une sous-chaine
 *
 * \param buf Pointeur vers le premier caractère de la chaine.
 * \param res Pointeur vers le resultat.
 * \param beg Debut de la sous-chaine.
 * \param end Fin de la sous-chaine.
 *
 * \return Un pointeur vers res.
 */
char* copierChaine(char *buf, char* res, int beg, int end);



#endif
