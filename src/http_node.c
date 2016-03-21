#include "http_node.h"

void init_HTTP_Node ( const char * name, HTTP_Node * node ) {
	node->name = name;
	node->beg = 0;
	node->end = 0;
	node->childs = NULL;
	node->nb_childs = 0;
}

void addChild_HTTP_Node ( HTTP_Node * node, HTTP_Node * child ) {
	int i;

	HTTP_Node ** childs = malloc ( (node->nb_childs + 1) * sizeof ( HTTP_Node * ) ); // Créer un nouveau tableau avec une taille plus grande

	for ( i = 0; i < node->nb_childs; i++ ) { // Copier l'ancien tableau
		childs [i] = node->childs [i];
	}

	childs [node->nb_childs] = child; // Ajout du nouveau noeud

	if ( node->childs ) { // S'il y avait un tableau, on le supprime
		free ( node->childs );
	}

	node->childs = childs; // On installe le nouveau tableau sur le node
	node->nb_childs ++;
}

void free_HTTP_Node ( HTTP_Node * node ) {
	if ( node->childs )
		free ( node->childs );

	free ( node );
}

void free_HTTP_Tree ( HTTP_Node * root ) {
	int i;

	for ( i = 0; i < root->nb_childs; i++ ) {
		free_HTTP_Tree ( root->childs [i] );
	}

	free_HTTP_Node ( root );
}

HTTP_Node* found_HTTP_Node ( HTTP_Node * root, char* string ) {
	HTTP_Node* result;
	int i = 0;
	// On regarde le nom
	if (!strcmp(root->name, string)){
		return root;
	}
	// Si ce n'est pas lui on parcourt ses fils
	for(i = 0; i < root->nb_childs; i++ ) {
		// pour chaque fils on recherche à partir de lui
		result = found_HTTP_Node(root->childs[i], string);

		// si trouvé on arrete
		if (result != NULL) {
			return result;
		}
	}
	// Pas trouvé donc on retourne NULL;
	return NULL;
}

void foundAll_HTTP_Node ( HTTP_Node * root, char* string, int* nbFound, HTTP_Node** result ) {
	*nbFound = 0;
	int i = 0;

	// On regarde le nom et on l'ajoute au besoin
	if (!strcmp(root->name, string)) {
		 result[0] = root;
		 *nbFound = 1;
	}

	// On parcourt ses fils
	for(i = 0; i < root->nb_childs; i++ ) {
		// On recherche à partir de chacun de ces fils.
		foundAll_HTTP_Node_rec(root->childs[i], string, &result, nbFound);
	}
}

void foundAll_HTTP_Node_rec ( HTTP_Node * root, char* string, HTTP_Node** result, int* nbFound ) {
    int i = 0;

	// On regarde le nom
	if (!strcmp(root->name, string)) {
		// Si il concorde on l'ajoute au tableau
		result[++(*nbFound)] = root;
	}
	// On parcourt ses fils
	for(i = 0; i < root->nb_childs; i++ ) {
		// On recherche à partir de chacun de ces fils.
		foundAll_HTTP_Node_rec(root->childs[i], string, result, nbFound);
	}
}
