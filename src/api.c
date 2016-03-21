#include "api.h"
#include "http_node.h"
#include "http_parser.h"

int parser (char *buf, unsigned int len, char *search ,void (*callback)()) {
	int cursor = 0;
	int i = 0;
	HTTP_Node * root = malloc ( sizeof ( HTTP_Node ) );
	HTTP_Node * nodes[20];
	int result = -1, nbResult;
    char string[100];

    // On parse la chaine pour obtenir un arbre
	result = parse_HTTP_message ( buf, &cursor, root );

	// Si la requete est incorrecte on retourne l'erreur.
	if ( result != 1 ) {
		return cursor;
	}

	// On trouve les elements recherche
	foundAll_HTTP_Node ( root, search, &nbResult, nodes );

	for(i = 0; i < nbResult; i++) {
        // Copie de la chaine pour eviter des modification de la requete par le callback
        copierChaine(buf, string,
                         (nodes[i]->beg), (nodes[i]->end)+1);
		// Appel du callback
		callback(string, (unsigned) (nodes[i]->end - nodes[i]->beg) );

	}

    // Liberation de la memoire
	free_HTTP_Tree ( root );
	return -1;
}

char* copierChaine(char *buf, char* res, int beg, int end) {
    // Variables locale
    int i = 0, j = 0;

    // On recopie la chaine
    for (i = beg; i < end; i++ ) {
        res[j++] = buf[i];
    }

    // On ajoute un zero de fin de chaine
    res[j] = '\0';

    return res;
}
