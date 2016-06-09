#ifndef FGCI_API_H
#define FGCI_API_H

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <time.h>

#include "config.h"
#include "utilities.h"
#include "request.h"
#include "http_response.h"

#define BUFFSIZE 12800
#define FCGI_TIMEOUT 200000

int init_connection ( char * ip, int port, int * src_port );
char * my_recv ( int sock, char * msg );
char * read_from_fcgi ( char * pathname, char * root_dir, unsigned long long * taille );

char * add_fcgi_beg ( uint8_t ver, uint16_t id, int * len );
char * add_fcgi_param ( uint8_t ver, uint16_t id, char * name, char * value, char * req, int * len );
char * add_fcgi_end ( int ver, int id, char * req, int * len );

#endif
