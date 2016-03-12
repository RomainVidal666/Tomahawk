#include <stdio.h>
#include <stdlib.h>

#include "http_node.h"
#include "http_parser.h"

int main ( int argc, char * argv [] ) {
	
	HTTP_Node * node = malloc ( sizeof ( HTTP_Node ) ); 
	HTTP_Node * child1 = malloc ( sizeof ( HTTP_Node ) );
	HTTP_Node * child2 = malloc ( sizeof ( HTTP_Node ) );
	HTTP_Node * child3 = malloc ( sizeof ( HTTP_Node ) );

	init_HTTP_Node ( "http", node );
	init_HTTP_Node ( "child1", child1 );
	init_HTTP_Node ( "child2", child2 );
	init_HTTP_Node ( "child3", child3 );

	addChild_HTTP_Node ( node, child1 );
	addChild_HTTP_Node ( node, child2 );
	addChild_HTTP_Node ( node, child3 );

	printf ( "%s\n", (node->childs [0])->name );
	printf ( "%s\n", (node->childs [1])->name );
	printf ( "%s\n", (node->childs [2])->name );

	free_HTTP_Tree ( node );

	return 0;
}