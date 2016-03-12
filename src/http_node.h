#ifndef HTTP_NODE_H
#define HTTP_NODE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct HTTP_Node HTTP_Node;
struct HTTP_Node {
	char * name;
	int beg;
	int end;

	HTTP_Node ** childs;
	int nb_childs;
};

void init_HTTP_Node ( const char * name, HTTP_Node * node );
void addChild_HTTP_Node ( HTTP_Node * node, HTTP_Node * child );
void free_HTTP_Node ( HTTP_Node * root );
void free_HTTP_Tree ( HTTP_Node * root );

#endif