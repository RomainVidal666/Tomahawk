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

	HTTP_Node ** childs = malloc ( (node->nb_childs + 1) * sizeof ( HTTP_Node * ) );

	for ( i = 0; i < node->nb_childs; i++ ) {
		childs [i] = node->childs [i];
	}

	childs [node->nb_childs] = child;

	if ( node->childs ) {
		free ( node->childs );
	}

	node->childs = childs;
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