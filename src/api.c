#include "api.h"
#include "http_node.h"
#include "http_parser.h"
#include "utilities.h"

int parser (char *buf, unsigned int len, char *search ,void (*callback)()) {
	int cursor = 0;
	int i = 0;
	HTTP_Node * root = malloc ( sizeof ( HTTP_Node ) );
	HTTP_Node ** nodes;
	int result, nbResult, nodesCount;
   	char * string;

   	// On parse la chaine pour obtenir un arbre
	result = parse_HTTP_message ( buf, &cursor, root );

	// Si la requete est incorrecte on retourne l'erreur.
	if ( result != 1 ) {
		return cursor;
	}
	
	// On trouve les elements recherche
	count_HTTP_Node(root, search, &nodesCount);
	nodes = malloc( sizeof(HTTP_Node*) * nodesCount);
	
	foundAll_HTTP_Node ( root, search, &nbResult, nodes );

	for(i = 0; i < nbResult; i++) {
		string = malloc ( ( nodes[i]->end - nodes[i]->beg ) * sizeof ( char ) ); 
        	// Copie de la chaine pour eviter des modification de la requete par le callback
        	copierChaine(buf, string, (nodes[i]->beg), (nodes[i]->end));
		// Appel du callback
		callback(string, (unsigned) (nodes[i]->end - nodes[i]->beg) );
		free ( string );
	}

   	// Liberation de la memoire
   	free ( nodes );
	free_HTTP_Tree ( root );
	return -1;
}
