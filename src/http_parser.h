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

 #define SP ' '

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

int parse_request_line ( char * request, int * cursor, HTTP_Node * node );

int parse_origin_form ( char * request, int * cursor, HTTP_Node * node );

int parse_absolute_form ( char * request, int * cursor, HTTP_Node * node );

int parse_authority_form ( char * request, int * cursor, HTTP_Node * node );

int parse_IPv4 ( char * request, int * cursor, HTTP_Node * node );

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

int isDIGIT ( char * request, int * cursor );

int isVCHAR ( char * request, int * cursor );

int isUnreserved ( char * request, int * cursor );

#endif