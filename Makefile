all: main.o api.o http_node.o http_parser.o
	gcc main.o api.o http_node.o http_parser.o -o tomahawk

main.o: main.c http_node.h http_parser.h api.h
	gcc -c main.c

http_node.o: http_node.c http_node.h
	gcc -c http_node.c

http_parser.o: http_parser.c http_parser.h
	gcc -c http_parser.c

api.o: api.c api.h
	gcc -c api.c
