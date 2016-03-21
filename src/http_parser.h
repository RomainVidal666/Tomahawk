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
 * \brief Fonction pour parser le HTTP-message.
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
 * \brief Fonction pour parser le start-line.
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
 * \brief Fonction pour parser le status-line.
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
int parse_header_field ( char * request, int * cursor, HTTP_Node * header_field );

/**
 * \fn int parse_field_name ( char * request, int * cursor, HTTP_Node * node )
 * \brief Fonction de création d'une nouvelle instance d'un objet HTTP_Node.
 *
 * \param request Chaine contenant la requête.
 * \param cursor Pointeur vers la position de la lecture de la requête.
 * \param node Pointeur vers le noeud header-field utilisé pour sauvegarder la valeur de l'élément correspondant au noeud.
 * 
 * \return Retourne 1 si la requête est correcte, 0 sinon.
 */
int parse_field_name ( char * request, int * cursor, HTTP_Node * header_field, HTTP_Node * field_name, HTTP_Node * field_value );

/**
 * \fn int parse_field_value ( char * request, int * cursor, HTTP_Node * header_field, HTTP_Node * field_name, HTTP_Node * field_value )
 * \brief Fonction de création d'une nouvelle instance d'un objet HTTP_Node.
 *
 * \param request Chaine contenant la requête.
 * \param cursor Pointeur vers la position de la lecture de la requête.
 * \param node Pointeur vers le noeud header-field utilisé pour sauvegarder la valeur de l'élément correspondant au noeud.
 * \param node Pointeur vers le noeud field-name utilisé pour sauvegarder la valeur de l'élément correspondant au noeud.
 * \param node Pointeur vers le noeud field-value utilisé pour sauvegarder la valeur de l'élément correspondant au noeud.
 * 
 * \return Retourne 1 si la requête est correcte, 0 sinon.
 */
int parse_field_value ( char * request, int * cursor, HTTP_Node * header_field, HTTP_Node * field_name, HTTP_Node * field_value );

/**
 * \fn int parse_field_content ( char * request, int * cursor, HTTP_Node * header_field, HTTP_Node * field_name, HTTP_Node * field_value )
 * \brief Fonction de création d'une nouvelle instance d'un objet HTTP_Node.
 *
 * \param request Chaine contenant la requête.
 * \param cursor Pointeur vers la position de la lecture de la requête.
 * \param node Pointeur vers le noeud header-field utilisé pour sauvegarder la valeur de l'élément correspondant au noeud.
 * \param node Pointeur vers le noeud field-name utilisé pour sauvegarder la valeur de l'élément correspondant au noeud.
 * \param node Pointeur vers le noeud field-value utilisé pour sauvegarder la valeur de l'élément correspondant au noeud.
 * 
 * \return Retourne 1 si la requête est correcte, 0 sinon.
 */
int parse_field_content ( char * request, int * cursor, HTTP_Node * header_field, HTTP_Node * field_name, HTTP_Node * field_value );

/**
 * \fn int parse_obs_fold ( char * request, int * cursor, HTTP_Node * header_field , HTTP_Node * field_name, HTTP_Node * field_value )
 * \brief Fonction de création d'une nouvelle instance d'un objet HTTP_Node.
 *
 * \param request Chaine contenant la requête.
 * \param cursor Pointeur vers la position de la lecture de la requête.
 * \param node Pointeur vers le noeud header-field utilisé pour sauvegarder la valeur de l'élément correspondant au noeud.
 * \param node Pointeur vers le noeud field-name utilisé pour sauvegarder la valeur de l'élément correspondant au noeud.
 * \param node Pointeur vers le noeud field-value utilisé pour sauvegarder la valeur de l'élément correspondant au noeud.
 * 
 * \return Retourne 1 si la requête est correcte, 0 sinon.
 */
int parse_obs_fold ( char * request, int * cursor, HTTP_Node * header_field , HTTP_Node * field_name, HTTP_Node * field_value );

/**
 * \fn int parse_message_body ( char * request, int * cursor, HTTP_Node * node )
 * \brief Fonction pour parser le message-body.
 *
 * \param request Chaine contenant la requête.
 * \param cursor Pointeur vers la position de la lecture de la requête.
 * \param node Pointeur vers le noeud utilisé pour sauvegarder la valeur de l'élément correspondant au noeud.
 * 
 * \return Retourne 1 si la requête est correcte, 0 sinon.
 */
int parse_message_body ( char * request, int * cursor, HTTP_Node * node );

/**
 * \fn int parse_request_target ( char * request, int * cursor, HTTP_Node * node )
 * \brief Fonction pour parser le request-target.
 *
 * \param request Chaine contenant la requête.
 * \param cursor Pointeur vers la position de la lecture de la requête.
 * \param node Pointeur vers le noeud utilisé pour sauvegarder la valeur de l'élément correspondant au noeud.
 * 
 * \return Retourne 1 si la requête est correcte, 0 sinon.
 */
int parse_request_target ( char * request, int * cursor, HTTP_Node * node );

/**
 * \fn int parse_request_line ( char * request, int * cursor, HTTP_Node * node )
 * \brief Fonction pour parser le request-line.
 *
 * \param request Chaine contenant la requête.
 * \param cursor Pointeur vers la position de la lecture de la requête.
 * \param node Pointeur vers le noeud utilisé pour sauvegarder la valeur de l'élément correspondant au noeud.
 * 
 * \return Retourne 1 si la requête est correcte, 0 sinon.
 */
int parse_request_line ( char * request, int * cursor, HTTP_Node * node );

/**
 * \fn int parse_origin_form ( char * request, int * cursor, HTTP_Node * node )
 * \brief Fonction pour parser le origin-form.
 *
 * \param request Chaine contenant la requête.
 * \param cursor Pointeur vers la position de la lecture de la requête.
 * \param node Pointeur vers le noeud utilisé pour sauvegarder la valeur de l'élément correspondant au noeud.
 * 
 * \return Retourne 1 si la requête est correcte, 0 sinon.
 */
int parse_origin_form ( char * request, int * cursor, HTTP_Node * node );

/**
 * \fn int parse_absolute_form ( char * request, int * cursor, HTTP_Node * node )
 * \brief Fonction pour parser le absolute-form.
 *
 * \param request Chaine contenant la requête.
 * \param cursor Pointeur vers la position de la lecture de la requête.
 * \param node Pointeur vers le noeud utilisé pour sauvegarder la valeur de l'élément correspondant au noeud.
 * 
 * \return Retourne 1 si la requête est correcte, 0 sinon.
 */
int parse_absolute_form ( char * request, int * cursor, HTTP_Node * node );

/**
 * \fn int parse_authority_form ( char * request, int * cursor, HTTP_Node * node )
 * \brief Fonction pour parser le authority-form.
 *
 * \param request Chaine contenant la requête.
 * \param cursor Pointeur vers la position de la lecture de la requête.
 * \param node Pointeur vers le noeud utilisé pour sauvegarder la valeur de l'élément correspondant au noeud.
 * 
 * \return Retourne 1 si la requête est correcte, 0 sinon.
 */
int parse_authority_form ( char * request, int * cursor, HTTP_Node * node );

/**
 * \fn int parse_IPv4 ( char * request, int * cursor, HTTP_Node * node )
 * \brief Fonction pour parser le IPv4.
 *
 * \param request Chaine contenant la requête.
 * \param cursor Pointeur vers la position de la lecture de la requête.
 * \param node Pointeur vers le noeud utilisé pour sauvegarder la valeur de l'élément correspondant au noeud.
 * 
 * \return Retourne 1 si la requête est correcte, 0 sinon.
 */
int parse_IPv4 ( char * request, int * cursor, HTTP_Node * node );

/**
 * \fn int parse_user_info ( char * request, int * cursor, HTTP_Node * node )
 * \brief Fonction pour parser le user-info.
 *
 * \param request Chaine contenant la requête.
 * \param cursor Pointeur vers la position de la lecture de la requête.
 * \param node Pointeur vers le noeud utilisé pour sauvegarder la valeur de l'élément correspondant au noeud.
 * 
 * \return Retourne 1 si la requête est correcte, 0 sinon.
 */
int parse_user_info ( char * request, int * cursor, HTTP_Node * node );

/**
 * \fn int parse_authority_form ( char * request, int * cursor, HTTP_Node * node )
 * \brief Fonction pour parser le authority-form.
 *
 * \param request Chaine contenant la requête.
 * \param cursor Pointeur vers la position de la lecture de la requête.
 * \param node Pointeur vers le noeud utilisé pour sauvegarder la valeur de l'élément correspondant au noeud.
 * 
 * \return Retourne 1 si la requête est correcte, 0 sinon.
 */
int parse_authority_form ( char * request, int * cursor, HTTP_Node * node );

/**
 * \fn int parse_regname ( char * request, int * cursor, HTTP_Node * node )
 * \brief Fonction pour parser le regname.
 *
 * \param request Chaine contenant la requête.
 * \param cursor Pointeur vers la position de la lecture de la requête.
 * \param node Pointeur vers le noeud utilisé pour sauvegarder la valeur de l'élément correspondant au noeud.
 * 
 * \return Retourne 1 si la requête est correcte, 0 sinon.
 */
int parse_regname ( char * request, int * cursor, HTTP_Node * node );

/**
 * \fn int parse_string ( char * str, int * cursor, char * cmp_str )
 * \brief Fonction pour vérifier l'égalité d'une chaine et d'une sous-chaine.
 *
 * \param str Chaine contenant la requête.
 * \param cursor Pointeur vers la position de la lecture de la requête.
 * \param cmp_str Pointeur vers le noeud utilisé pour sauvegarder la valeur de l'élément correspondant au noeud.
 * 
 * \return Retourne 1 si la requête est correcte, 0 sinon.
 */
int parse_string ( char * str, int * cursor, char * cmp_str );

/**
 * \fn int isDIGIT ( char * request, int * cursor )
 * \brief Fonction pour vérifier si on a bien un DIGIT.
 *
 * \param request Chaine contenant la requête.
 * \param cursor Pointeur vers la position de la lecture de la requête.
 * 
 * \return Retourne 1 si le prochain caractere est un DIGIT, 0 sinon.
 */
int isDIGIT ( char * request, int * cursor );

/**
 * \fn int isTchar ( char * request, int * cursor )
 * \brief Fonction pour vérifier si on a bien un TCHAR.
 *
 * \param str Chaine contenant la requête.
 * \param cursor Pointeur vers la position de la lecture de la requête.
 * 
 * \return Retourne 1 si le caractere de la requete est un TCHAR, 0 sinon.
 */
int isTchar ( char * request, int * cursor );

/**
 * \fn int isVCHAR ( char * request, int * cursor )
 * \brief Fonction pour vérifier si on a bien un VCHAR.
 *
 * \param str Chaine contenant la requête.
 * \param cursor Pointeur vers la position de la lecture de la requête.
 * 
 * \return Retourne 1 si le caractere de la requete est un VCHAR, 0 sinon.
 */
int isVCHAR ( char * request, int * cursor );

/**
 * \fn int isObstext ( char * request, int * cursor )
 * \brief Fonction pour vérifier si on a bien un ObsText.
 *
 * \param str Chaine contenant la requête.
 * \param cursor Pointeur vers la position de la lecture de la requête.
 * 
 * \return Retourne 1 si le caractere de la requete est un ObsText, 0 sinon.
 */
int isObstext ( char * request, int * cursor );

/**
 * \fn int isFieldvchar ( char * request, int * cursor )
 * \brief Fonction pour vérifier si on a bien un Field-VCHAR.
 *
 * \param str Chaine contenant la requête.
 * \param cursor Pointeur vers la position de la lecture de la requête.
 * 
 * \return Retourne 1 si la caractere de la requête est un field-vchar, 0 sinon.
 */
int isFieldvchar ( char * request, int * cursor );

/**
 * \fn int isUnreserved ( char * request, int * cursor )
 * \brief Fonction pour vérifier si on a bien un Unreserved.
 *
 * \param str Chaine contenant la requête.
 * \param cursor Pointeur vers la position de la lecture de la requête.
 * 
 * \return Retourne 1 si la caractere de la requête est un Unreserved, 0 sinon.
 */
int isUnreserved ( char * request, int * cursor );

#endif