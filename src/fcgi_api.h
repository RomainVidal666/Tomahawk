#ifndef FGCI_API_H
#define FGCI_API_H

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

#define BUFFSIZE 128

int init_connection ( char * ip, int port );
int my_send ( char * msg, int sock );
int my_recv ( int sock, char * msg );

#endif