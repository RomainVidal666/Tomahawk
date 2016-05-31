#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

/*!
 * \file http_node.h
 * \brief Gestion du traitement d'une requête HTTP
 * \author R. Vidal / A. Lorber / T. Jacumin
 * \version 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "request.h"
#include "utilities.h"
#include "http_parser.h"
#include "request.h"
#include "percent_encoding.h"
#include "config.h"

#define ROOT_DIR "www/"

/**
 * \struct HTTP_header
 * \brief Représente un header-field de la réponse.
 */
typedef struct HTTP_header HTTP_header;
struct HTTP_header {
	char * name;			/*!< Nom du header. */
	char * value;			/*!< Valeur du header. */
	HTTP_header * next;		/*!< Pointeur vers le prochain header. */
};

/**
 * \struct HTTP_GET_response
 * \brief Représente la réponse.
 */
typedef struct HTTP_GET_response HTTP_GET_response;
struct HTTP_GET_response {
	int code;				/*!< Code de la réponse. */
	unsigned char * body;	/*!< Contenu du message-body. */
	HTTP_header * headers;	/*!< Pointeur vers le premier header. */
};

/**
 * \struct HTTP_POST
 * \brief Représente un champ de la méthode POST.
 */
typedef struct HTTP_POST HTTP_POST;
struct  HTTP_POST {
	char * name;			/*!< Nom du champ. */
	int beg;				/*!< Début de la valeur dans le buffer de la requête. */
	int end;				/*!< Fin de la valeur dans le buffer de la requête. */
	HTTP_POST * next;		/*!< Pointeur vers le prochain champ. */
};

/**
 * \fn int make_HTTP_requete( HTTP_Node * http_message, message * requete )
 * \brief Fonction d'envoie de la réponse.
 *
 * \param http_message Arbre des noeuds des différente partie de la requête.
 * \param requete Pointeur vers le contenu de la requête.
 *
 * \return Retourne 1 en cas de succès et 0 en cas d'échec.
 */

int make_HTTP_requete( HTTP_Node * http_message, message * requete );

/**
 * \fn HTTP_header * add_HTTP_header ( char * name, char * value, HTTP_header * root )
 * \brief Fonction pour ajouter un header.
 *
 * \param name Nom du nouveau champs.
 * \param value Valeur du nouveau champs.
 * \param root Début de la liste des champs.
 *
 * \return Retourne le début de la liste des champs.
 */

HTTP_header * add_HTTP_header ( char * name, char * value, HTTP_header * root );

/**
 * \fn void free_HTTP_header ( HTTP_header * root )
 * \brief Fonction pour supprimer un header.
 *
 * \param root Header à supprimer.
 */

void free_HTTP_header ( HTTP_header * root );

/**
 * \fn char * get_message_code ( int code )
 * \brief Fonction pour associer un code de requête avec sa signification
 *
 * \param code Code de requête.
 *
 * \return Retourne la signification du code de la requête.
 */

char * get_message_code ( int code );

/**
 * \fn char * get_mime_type(HTTP_Node * http_message, message * requete)
 * \brief Fonction pour connaître de type MIME associé à la ressource demandée.
 *
 * \param http_message Arbre des noeuds des différente partie de la requête.
 * \param requete Pointeur vers le contenu de la requête.
 *
 * \return Retourne de le type MIME.
 */

char * get_mime_type(HTTP_Node * http_message, message * requete);

/**
 * \fn char * read_from_file ( char * pathname, char * root_dir, unsigned long long * taille )
 * \brief Fonction pour lire dans un fichier binaire.
 *
 * \param pathname Chemin d'accès au fichier.
 * \param root_dir Chemin vers la racine du site.
 * \param taille Pointeur vers la taille du fichier.
 *
 * \return Retourne le contenu du fichier.
 */

char * read_from_file ( char * pathname, char * root_dir, unsigned long long * taille );

/**
 * \fn char * cast_HTTP_GET_response_to_string ( HTTP_GET_response * response )
 * \brief Fonction pour convertir une réponse HTTP en chaîne.
 *
 * \param response Pointeur vers la réponse.
 *
 * \return Retourne la réponse sous forme de chaîne de caractères.
 */

char * cast_HTTP_GET_response_to_string ( HTTP_GET_response * response );

/**
 * \fn int send_HTTP_GET_response ( HTTP_GET_response * http_reponse, unsigned int clientId, unsigned long long body_length )
 * \brief Fonction pour envoyer une réponse.
 *
 * \param http_reponse Pointeur vers la réponse.
 * \param clientId Identifiant du client.
 * \param body_length Taille du message-body.
 *
 * \return Retourne 1 en cas de succès et 0 en cas d'échec.
 */

int send_HTTP_GET_response ( HTTP_GET_response * http_reponse, unsigned int clientId, unsigned long long body_length );

/**
 * \fn int send_HTTP_error ( int errNumber, int clientId, char * root_dir )
 * \brief Fonction pour envoyer une page d'erreur.
 *
 * \param errNumber Numéro de l'erreur.
 * \param clientId Identifiant du client.
 * \param root_dir Chemin vers le fichier contenant les pages d'erreur.
 */

int send_HTTP_error ( int errNumber, int clientId, char * root_dir );

/**
 * \fn HTTP_POST * add_HTTP_POST ( int beg, int end, HTTP_POST * root )
 * \brief Fonction ajouter un champ POST
 *
 * \param beg Début de la valeur dans le buffer de la requête.
 * \param end Fin de la valeur dans le buffer de la requête.
 * \param root Pointeur vers le premier champs.
 *
 * \return Retourne un pointeur vers le premier champs.
 */

HTTP_POST * add_HTTP_POST ( int beg, int end, HTTP_POST * root );

/**
 * \fn int parse_HTTP_POST ( HTTP_Node * http_message, message * requete )
 * \brief Fonction pour parser les champs POST du message-body.
 *
 * \param http_message Arbre des noeuds des différente partie de la requête.
 * \param requete Pointeur vers le contenu de la requête.
 *
 * \return Retourne 1 si la syntaxe est vérifiée, 0 sinon.
 */

int parse_HTTP_POST ( HTTP_Node * http_message, message * requete );

#endif
