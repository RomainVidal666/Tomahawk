#include <stdio.h>
#include <stdlib.h>

#include "http_node.h"

/**
 * \fn int analyse(char * request, HTTP_Node * root)
 * \brief Fonction d'analyse semantique.
 *
 * \param request chaîne contenant la requête.
 * \param cursor Pointeur vers la position de la lecture de la requête.
 * \param root Pointeur vers le noeud racine.
 * 
 * \return Retourne 1 si la requête est correcte, 0 sinon.
 */
int analyse(char * request, HTTP_Node * root);

