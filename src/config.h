#ifndef CONFIG_H
#define CONFIG_H

/*!
 * \file config.h
 * \brief Gestion du fichier de configuration et du multi-sites.
 * \author R. Vidal / A. Lorber / T. Jacumin
 * \version 1.0
 */

//===== INCLUDES =====//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//===== CONSTANTES =====//
#define MAX_SITE 5
#define CONF_FILE "tomahawk.conf"

//===== PROTOTYPES =====//
/**
*  \fn int loadConfig();
*  \brief Charge la configuration en memoire
*  \return 0 si pas d'erreur sinon exit(-1)
**/
int loadConfig();

/**
*  \fn char * findInConfig(char * domaine);
*  \brief Cherche si domaine est present dans la configuration
*  \return Retourne NULL si il n'est pas trouve, le chemin vers la racine sinon
**/
char * findInConfig(char * domaine);

/**
*  \fn void freeConfig();
*  \brief Libere la memoire allouee a la configuration
**/
void freeConfig();

/**
* \fn char * getFastCGIAddress();
  \brief Fonction pour obtenir l'interface fastCGI
  \return L'adresse de l'interface FastCGI
**/
char * getFastCGIAddress();

/**
*  \fn int getFastCGIPort();
*  \brief Fonction pour obtenir le port de l'interface FastCGI
*  \return Retourne le port de l'interface FastCGI
**/
int getFastCGIPort();

/**
*  \fn int isFastCGIConfigure();
*  \brief Fonction pour savoir si l'interface FastCGI à été configuree
*  \return Retourne 1 si FastCGI a ete configure 0 sinon
**/
int isFastCGIConfigure();

#endif
