#ifndef HTTP_NODE_H
#define HTTP_NODE_H

/*!
 * \file http_node.h
 * \brief Gestion de l'arbre n-aire utiliser par le parseur HTTP
 * \author R. Vidal / A. Lorber / T. Jacumin
 * \version 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct HTTP_Node HTTP_Node;

/**
 * \struct HTTP_Node
 * \brief Représente un noeud de l'arbre utilisé par le parseur.
 */
struct HTTP_Node {
	char * name; 			/*!< Nom du noeud. */
	int beg;	 			/*!< Début de l'élément dans la requête HTTP. */
	int end;				/*!< Fin de l'élément dans la requête HTTP. */

	HTTP_Node ** childs;	/*!< Ensemble de ses enfants. */
	int nb_childs;			/*!< Nombre d'enfant. */
};

/**
 * \fn void init_HTTP_Node ( char * name, HTTP_Node * node )
 * \brief Fonction de création d'une nouvelle instance d'un objet HTTP_Node.
 *
 * \param name Nom du noeud.
 * \param node Pointeur vers le noeud à initialiser.
 */
void init_HTTP_Node ( char * name, HTTP_Node * node );

/**
 * \fn void addChild_HTTP_Node ( HTTP_Node * node, HTTP_Node * child )
 * \brief Fonction d'ajout d'un fils à un noeud.
 *
 * \param node Pointeur vers le noeud parent.
 * \param child Pointeur vers le noeud fils.
 */
void addChild_HTTP_Node ( HTTP_Node * node, HTTP_Node * child );

/**
 * \fn void free_HTTP_Node ( HTTP_Node * node )
 * \brief Fonction de suppression d'un noeud.
 *
 * \param node Pointeur vers le noeud à supprimer.
 */
void free_HTTP_Node ( HTTP_Node * node );

/**
 * \fn void free_HTTP_Tree ( HTTP_Node * root )
 * \brief Fonction de suppression d'un arbre.
 *
 * \param node Pointeur vers le noeud racine de l'arbre à supprimer.
 */
void free_HTTP_Tree ( HTTP_Node * root );

/**
 * \fn HTTP_Node found_HTTP_Node ( HTTP_Node * root, char* string )
 * \brief Fonction de recherche dans un arbre.
 *
 * \param root Pointeur vers le noeud racine de l'arbre.
 * \param string La chaine à rechercher.
 *
 * \return Le noeud qui à pour nom la chaine string.
 */
HTTP_Node* found_HTTP_Node ( HTTP_Node * root, char* string );

/**
 * \fn HTTP_Node* foundAll_HTTP_Node ( HTTP_Node * root, char* string, int* nbFound )
 * \brief Fonction de recherche dans un arbre.
 *
 * \param root Pointeur vers le noeud racine de l'arbre.
 * \param string La chaine à rechercher.
 * \param nbFound Le nombre de noeud trouvé.
 *
 * \return Un tableau des noeuds qui ont pour nom la chaine string (dans la limite de 10).
 */
void foundAll_HTTP_Node ( HTTP_Node * root, char* string, int* nbFound, HTTP_Node** result );

/**
 * \fn void foundAll_HTTP_Node_rec ( HTTP_Node * root, char* string, HTTP_Node** result, int* nbFound )
 * \brief Fonction de recherche dans un arbre.
 *
 * \param root Pointeur vers le noeud racine de l'arbre.
 * \param string La chaîne à rechercher.
 * \param result Tableau des noeuds correspondant à la recherche.
 * \param nbFound Le nombre de noeud trouvé.
 *
 */
void foundAll_HTTP_Node_rec ( HTTP_Node * root, char* string, HTTP_Node** result, int* nbFound );

/**
 * \fn int count_HTTP_Node ( HTTP_Node * root, char* string )
 * \brief Fonction de comptage d'elements dans un arbre.
 *
 * \param root Pointeur vers le noeud racine de l'arbre.
 * \param string La chaine à rechercher.
 * \param count Le nombre de noeud qui ont comme nom string.
 * 
 */
void count_HTTP_Node ( HTTP_Node * root, char* string, int * count );

/**
 * \fn void print_HTTP_Node ( char * request, HTTP_Node * node )
 * \brief Fonction pour afficher le contenu d'un HTTP_Node
 *
 * \param request Chaîne contenant la requête.
 * \param node Noeud à afficher.
 *
 */
void print_HTTP_Node ( char * request, HTTP_Node * node );

/**
 * \fn void print_HTTP_Tree ( char * request, HTTP_Node * root, int level )
 * \brief Fonction pour afficher le contenu d'un arbre de HTTP_Node
 *
 * \param request Chaîne contenant la requête.
 * \param node Noeud racine.
 * \param level Pour l'indentation (laisser à 0).
 *
 */
void print_HTTP_Tree ( char * request, HTTP_Node * root, int level );

/**
 * \fn int HTTP_Node_is_equal ( char * request, HTTP_Node * node, char * str )
 * \brief Fonction pour comparer la valeur d'un HTTP_Node
 *
 * \param request Chaîne contenant la requête.
 * \param node Noeud à comparer.
 * \param str Chaîne à comparer.
 *
 * \return 1 si la valeur de node est la même que contenue dans str. 0 sinon.
 */
int HTTP_Node_is_equal ( char * request, HTTP_Node * node, char * str );

#endif
