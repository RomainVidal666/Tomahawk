#include <stdio.h>
#include <stdlib.h>

#include "http_node.h"

int main ( int argc, char * argv [] ) {
	int cursor = 0;
	int nb;

	// Pour les resultats
    HTTP_Node * resultAllNode[10];
    HTTP_Node * resultOneNode;

	// Allocation de l'arbre
	HTTP_Node * root = malloc ( sizeof ( HTTP_Node ) );
	HTTP_Node * node1 = malloc ( sizeof ( HTTP_Node ) );
	HTTP_Node * node2 = malloc ( sizeof ( HTTP_Node ) );
	HTTP_Node * node3 = malloc ( sizeof ( HTTP_Node ) );
	HTTP_Node * resultExpected1 = malloc ( sizeof ( HTTP_Node ) );
	HTTP_Node * resultExpected21 = malloc ( sizeof ( HTTP_Node ) );
	HTTP_Node * resultExpected22 = malloc ( sizeof ( HTTP_Node ) );

    // Initialisation de l'arbre
	init_HTTP_Node ( "root", root );
	init_HTTP_Node ( "node1", node1 );
	init_HTTP_Node ( "node2", node2 );
	init_HTTP_Node ( "node3", node3 );
	init_HTTP_Node ( "resultExpected1", resultExpected1 );
	init_HTTP_Node ( "resultExpected2", resultExpected21 );
	init_HTTP_Node ( "resultExpected2", resultExpected22 );

    // Création de l'arbre
	addChild_HTTP_Node ( root, node1 );
	addChild_HTTP_Node ( root, node2 );
	addChild_HTTP_Node ( root, node3 );
	addChild_HTTP_Node ( node3, resultExpected1);
	addChild_HTTP_Node ( node2, resultExpected21);
	addChild_HTTP_Node ( node3, resultExpected22);

    // on cheche "result1"
    printf("RECHERCHE FEUILLE : ");
    resultOneNode = found_HTTP_Node(root, "resultExpected1");
    if(resultOneNode == resultExpected1) {
        printf("\t\tOK\n");
    }else {
        printf("\t\tKO /!\\ \n");
    }
    // on cheche "root"
    printf("RECHERCHE RACINE : ");
    resultOneNode = found_HTTP_Node(root, "root");
    if(resultOneNode == root) {
        printf("\t\tOK\n");
    }else {
        printf("\t\tKO /!\\ \n");
    }
    // On cherche tout les "resultExpected1"
    printf("RECHERCHE MULTI RESULT 1 : ");
    foundAll_HTTP_Node ( root, "resultExpected1", &nb, resultAllNode );
    if(resultAllNode[0] == resultExpected1) {
        printf("\tOK\n");
    }else {
        printf("\tKO /!\\ \n");
    }
    // On cherche tout les "resultExpected2"
    printf("RECHERCHE MULTI RESULT 2 : ");
    foundAll_HTTP_Node ( root, "resultExpected2", &nb, resultAllNode );
    if(resultAllNode[0] == resultExpected21
       && resultAllNode[1] == resultExpected22) {
        printf("\tOK\n");
    }else {
        printf("\tKO /!\\ \n");
    }
    // On cherche tout les "root"
    printf("RECHERCHE MULTI RESULT : ");
    foundAll_HTTP_Node ( root, "root", &nb, resultAllNode );
    if(resultAllNode[0] == root) {
        printf("\tOK\n");
    }else {
        printf("\tKO /!\\ \n");
    }

    // Liberation de la memoire
    free_HTTP_Tree ( root );

	return 0;
}
