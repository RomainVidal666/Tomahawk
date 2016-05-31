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
*  Charge la configuration en memoire
**/
int loadConfig();
/**
*  Cherche si domaine est present dans la configuration
*  Retourne NULL si il n'est pas trouve, le chemin vers la racine sinon
**/
char * findInConfig(char * domaine);
/**
*  Libere la memoire allouee a la configuration
**/
void freeConfig();

#endif
