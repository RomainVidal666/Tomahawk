#include "http_node.h"

void init_HTTP_Node ( char * name, HTTP_Node * node ) {
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
	free ( node );
}

void free_HTTP_Tree ( HTTP_Node * root ) {
	int i;

	for ( i = 0; i < root->nb_childs; i++ ) {
		if ( root->childs [i] ) {
			free_HTTP_Tree ( root->childs [i] );
		}
	}

	//free_HTTP_Node ( root );
	free ( root );
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
		foundAll_HTTP_Node_rec(root->childs[i], string, result, nbFound);
	}
}

void foundAll_HTTP_Node_rec ( HTTP_Node * root, char* string, HTTP_Node** result, int* nbFound ) {
    int i = 0;

	// On regarde le nom
	if (!strcmp(root->name, string)) {
		// Si il concorde on l'ajoute au tableau
		result[(*nbFound)++] = root;
	}
	// On parcourt ses fils
	for(i = 0; i < root->nb_childs; i++ ) {
		// On recherche à partir de chacun de ces fils.
		foundAll_HTTP_Node_rec(root->childs[i], string, result, nbFound);
	}
}

void count_HTTP_Node ( HTTP_Node * root, char * string, int * count ) {
	int i = 0;

	// On regarde le nom et on l'ajoute au besoin
	if (!strcmp(root->name, string)) {
		 (*count)++;
	}

	// On parcourt ses fils
	for(i = 0; i < root->nb_childs; i++ ) {
		// On recherche à partir de chacun de ces fils.
		count_HTTP_Node(root->childs[i], string, count);
	}
}

void print_HTTP_Node ( char * request, HTTP_Node * node ) {
	if ( node ) {
		int i;
		printf ( "\"" );
		for ( i = node->beg; i < node->end; i++ )
			printf ( "%c", request [i] );

		printf ( "\"\n" );
	} else {
		printf ( "ERREUR : Node non initialisé\n" );
	}

}

void print_HTTP_Tree ( char * request, HTTP_Node * root, int level ) {
	int i;
	int j;
	if ( root ) {

		/* Mise en forme et affichage */
		for ( j = 0; j < level * 2; j++ )
			printf ( " " );

		if ( level == 0 ) {
			printf ( " %s : ", root->name );
		} else {
			printf ( "`--> %s : ", root->name );
		}
		print_HTTP_Node ( request, root );

		/* Tratement des fils */
		for ( i = 0; i < root->nb_childs; i++ ) {
			print_HTTP_Tree ( request, root->childs [i], level + 1 );
		}
	}
}

int HTTP_Node_is_equal ( char * request, HTTP_Node * node, char * str ) {
	int i;
	for ( i = node->beg; i < node->end; i++ )
		if ( request [i] != str [i-node->beg] )
			return 0;

	return 1;
}

char * get_HTTP_Node_value ( char * request, HTTP_Node * node ) {
	char * str = NULL;
	int i;
	if ( ( node ) && ( node->end > node->beg ) ) {
		str = malloc ( sizeof ( char ) * ( node->end - node->beg + 1 ) );
		for ( i = 0; i < node->end - node->beg; i++ ) {
			str [i] = request [node->beg + i];
		}
		str [node->end - node->beg] = '\0';
	}

	return str;
}

char * get_field_value( char * request, HTTP_Node * root, char * search) {
	int count = 0;
	count_HTTP_Node(root, "field-name", &count);
	HTTP_Node * nodeFound[count];
	char * nodeValue;
	int nbFound;
	int i;
	
	foundAll_HTTP_Node ( root, "field-name", &nbFound, nodeFound );

	for ( i = 0; i < nbFound; i++) {
		nodeValue = get_HTTP_Node_value(request,nodeFound[i]);
		if (! strcmp( nodeValue, search ) ){
			free(nodeValue);
			return (get_HTTP_Node_value(request, nodeFound[i]->childs[0]));
		}
		free(nodeValue);
	}
	return NULL;
}
