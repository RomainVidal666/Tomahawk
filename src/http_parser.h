#ifndef HTTP_PARSER_H
#define HTTP_PARSER_H

/*!
 * \file http_parser.h
 * \brief Parseur HTTP 1.0
 * \author R. Vidal / A. Lorber / T. Jacumin
 * \version 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "http_node.h"

/**
 * \fn int parse_HTTP_message ( char * request, int * cursor, HTTP_Node * node )
 * \brief Fonction de création d'une nouvelle instance d'un objet HTTP_Node.
 *
 * \param request Chaine contenant la requête.
 * \param cursor Pointeur vers la position de la lecture de la requête.
 * \param node Pointeur vers le noeud utilisé pour sauvegarder la valeur de l'élément correspondant au noeud.
 * 
 * \return Retourne 1 si la requête est correcte, 0 sinon.
 */
int parse_HTTP_message ( char * request, int * cursor, HTTP_Node * node );

/**
 * \fn int parse_start_line ( char * request, int * cursor, HTTP_Node * node )
 * \brief Fonction de création d'une nouvelle instance d'un objet HTTP_Node.
 *
 * \param request Chaine contenant la requête.
 * \param cursor Pointeur vers la position de la lecture de la requête.
 * \param node Pointeur vers le noeud utilisé pour sauvegarder la valeur de l'élément correspondant au noeud.
 * 
 * \return Retourne 1 si la requête est correcte, 0 sinon.
 */
int parse_start_line ( char * request, int * cursor, HTTP_Node * node );

/**
 * \fn int parse_status_line ( char * request, int * cursor, HTTP_Node * node )
 * \brief Fonction de création d'une nouvelle instance d'un objet HTTP_Node.
 *
 * \param request Chaine contenant la requête.
 * \param cursor Pointeur vers la position de la lecture de la requête.
 * \param node Pointeur vers le noeud utilisé pour sauvegarder la valeur de l'élément correspondant au noeud.
 * 
 * \return Retourne 1 si la requête est correcte, 0 sinon.
 */
int parse_status_line ( char * request, int * cursor, HTTP_Node * node );

/**
 * \fn int parse_header_field ( char * request, int * cursor, HTTP_Node * node )
 * \brief Fonction de création d'une nouvelle instance d'un objet HTTP_Node.
 *
 * \param request Chaine contenant la requête.
 * \param cursor Pointeur vers la position de la lecture de la requête.
 * \param node Pointeur vers le noeud utilisé pour sauvegarder la valeur de l'élément correspondant au noeud.
 * 
 * \return Retourne 1 si la requête est correcte, 0 sinon.
 */
int parse_header_field ( char * request, int * cursor, HTTP_Node * node );

/**
 * \fn int parse_message_body ( char * request, int * cursor, HTTP_Node * node )
 * \brief Fonction de création d'une nouvelle instance d'un objet HTTP_Node.
 *
 * \param request Chaine contenant la requête.
 * \param cursor Pointeur vers la position de la lecture de la requête.
 * \param node Pointeur vers le noeud utilisé pour sauvegarder la valeur de l'élément correspondant au noeud.
 * 
 * \return Retourne 1 si la requête est correcte, 0 sinon.
 */
int parse_message_body ( char * request, int * cursor, HTTP_Node * node );

int parse_request_target ( char * request, int * cursor, HTTP_Node * node );

/**
 * \fn int parse_string ( char * str, int * dep, char * cmp_str )
 * \brief Fonction de création d'une nouvelle instance d'un objet HTTP_Node.
 *
 * \param str Chaine contenant la requête.
 * \param cursor Pointeur vers la position de la lecture de la requête.
 * \param cmp_str Pointeur vers le noeud utilisé pour sauvegarder la valeur de l'élément correspondant au noeud.
 * 
 * \return Retourne 1 si la requête est correcte, 0 sinon.
 */
int parse_string ( char * str, int * cursor, char * cmp_str );

/**
 * \fn int parse_string ( char * str, int * dep, char * cmp_str )
 * \brief Fonction de création d'une nouvelle instance d'un objet HTTP_Node.
 *
 * \param str Chaine contenant la requête.
 * \param cursor Pointeur vers la position de la lecture de la requête.
 * 
 * \return Retourne 1 si le prochain caractere est un DIGIT, 0 sinon.
 */
int isDIGIT ( char * request, int * cursor );

/**
 * \fn int parse_string ( char * str, int * dep, char * cmp_str )
 * \brief Fonction de création d'une nouvelle instance d'un objet HTTP_Node.
 *
 * \param str Chaine contenant la requête.
 * \param cursor Pointeur vers la position de la lecture de la requête.
 * 
 * \return Retourne 1 si le caractere de la requete est un tchar, 0 sinon.
 */
int isTchar ( char * request, int * cursor );

/**
 * \fn int parse_string ( char * str, int * dep, char * cmp_str )
 * \brief Fonction de création d'une nouvelle instance d'un objet HTTP_Node.
 *
 * \param str Chaine contenant la requête.
 * \param cursor Pointeur vers la position de la lecture de la requête.
 * 
 * \return Retourne 1 si le prochain caractere de la requete est un vchar, 0 sinon.
 */
int isVCHAR ( char * request, int * cursor );

/**
 * \fn int parse_string ( char * str, int * dep, char * cmp_str )
 * \brief Fonction de création d'une nouvelle instance d'un objet HTTP_Node.
 *
 * \param str Chaine contenant la requête.
 * \param cursor Pointeur vers la position de la lecture de la requête.
 * 
 * \return Retourne 1 si la caractere de la requête est un obs-text, 0 sinon.
 */
int isObstext ( char * request, int * cursor );

/**
 * \fn int parse_string ( char * str, int * dep, char * cmp_str )
 * \brief Fonction de création d'une nouvelle instance d'un objet HTTP_Node.
 *
 * \param str Chaine contenant la requête.
 * \param cursor Pointeur vers la position de la lecture de la requête.
 * 
 * \return Retourne 1 si la caractere de la requête est un field-vchar, 0 sinon.
 */
int isFieldvchar ( char * request, int * cursor );
#endif