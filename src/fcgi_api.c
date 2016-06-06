#include "fcgi_api.h"

int init_connection ( char * ip, int port ) {
	int sock;
    struct sockaddr_in echoserver;
    char buffer[BUFFSIZE];
    int received = 0;
    /* Create the TCP socket */
    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
      printf("Failed to create socket\n");
      return -1;
    }

    /* Construct the server sockaddr_in structure */
    memset(&echoserver, 0, sizeof(echoserver));       /* Clear struct */
    echoserver.sin_family = AF_INET;                  /* Internet/IP */
    echoserver.sin_addr.s_addr = inet_addr(ip);  /* IP address */
    echoserver.sin_port = htons(port);       /* server port */
    /* Establish connection */
    if (connect(sock,
                (struct sockaddr *) &echoserver,
                sizeof(echoserver)) < 0) {
      printf("Failed to connect with server\n");
  		return -1;
    }

    return sock;
}

int my_send ( char * msg, int sock ) {
	unsigned int echolen;
	/* Send the word to the server */
    echolen = strlen(msg);
    if (send(sock, msg, echolen, 0) != echolen) {
      printf("Mismatch in number of sent bytes\n");
    }
}

int my_recv ( int sock, char * msg ) {

	/* Receive the word back from the server */
	int bytes = 0;
    while ( recv ( sock, msg, BUFFSIZE - 1, 0 ) > 0 ) {
      	//msg[bytes] = '\0';        /* Assure null terminated string */
    	printf ( "ok\n" );
    }
    //printf ( "rec : %s\n", msg );
    printf ( "fin\n" );
}