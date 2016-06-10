
#include "fcgi_api.h"

int init_connection ( char * ip, int port, int * src_port ) {
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
    if (connect(sock, (struct sockaddr *) & echoserver, sizeof(echoserver)) < 0) {
      	printf("Failed to connect with server\n");
  		return -1;
    }

    struct sockaddr_in local_address;
	int addr_size = sizeof(local_address);
	getsockname(sock, (struct sockaddr *) &local_address, &addr_size);
	(*src_port) = htons ( local_address.sin_port );

    return sock;
}


char * my_recv ( int sock ) {

	HTTP_Node * headers = malloc ( sizeof ( HTTP_Node ) );
	clock_t timeout;
	int fin=0;
	long int i = 0;
	char req[BUFFSIZE];
	long int size_req = 0;
	long int size = 0;
	int content_length = 0;
	int padding = 0;
	int id;
	int type;
	int is_data = 0;
	char * msg;
	long int j;
	
	while ( ( clock () - timeout <= FCGI_TIMEOUT ) && ( !fin ) ) { // tant qu'on a pas reçus une réponse de type FCGI_END_REQUEST et si on est pas en timeout
		timeout = clock ();
		while ( ( clock () - timeout <= FCGI_TIMEOUT ) && ( size_req = recv ( sock, req, BUFFSIZE - 1, 0 ) ) <= 0 ); // on attend de recevoir qqch
		printf("Message recu\ntaille: %d\n", size_req );
		msg = strcat_without_alloc_with_2_length ( msg, size, req, size_req );
	    printf("Messages concatenes\n");		
		
		size += size_req;
		while ( i<size ) {		
			i++;			//on passe la version
			type = (unsigned short) msg[i];
			i++;
			i++;			//Request ID
			i++;
			i++;
			id = (unsigned short) msg[i];
			
			content_length= (unsigned short) msg[i];	//on recupere le content_lengt
			i+=1;
			padding= (unsigned char) msg[i];		//on recupere le padding
			i+=2;
			
			/*			
			if( !is_data ){
				if ( parse_header_field ( msg, &i, headers) == -1)
					printf("ERREUR: champ field de fcgi invalide");
				printf("header field fini\n");
			}
			print_HTTP_Tree ( msg, headers, 0 );
			*/
			/*is_data = 1;
			if( is_data ){
				while ( i<content_length )
					i++;
				printf("data fini\n");
			}*/
			i += content_length;
			printf("\n\npadding:\n");			
			for(j=0; j<padding; j++)
				printf("%d ", msg[i+j]);

			i += padding;
			printf("\n");

			if(type==3)
				fin=1;
			printf("type:%d\n", type);
			printf("content-length:%d\n", content_length);
			printf("padding:%d\n", padding);
			

			/*for(j=0; j<size; j++)
				printf("%d ", msg[j]); 
			getchar();*/
		}
	}

	if ( clock () - timeout > FCGI_TIMEOUT ) {
		printf ( "Erreur timeout\n" ); 
	} else {
		for ( int i = 0; i < bytes; i++ ) {
	    	printf ( "%c", msg[i]);
	    }
	    printf ( "\n" );
	}
}

char * read_from_fcgi ( char * pathname, char * root_dir, unsigned long long * taille ) {
	int src_port;
	int sock_fcgi;
	char src_port_str [6];
	char buff [BUFFSIZE];

	if ( ! isFastCGIConfigure () ) {
		printf(" FastCGI non configurer\n");
		return NULL;
	}

	sock_fcgi = init_connection ( getFastCGIAddress (), getFastCGIPort (), &src_port );
	snprintf ( src_port_str, 6, "%d", src_port );

	if ( sock_fcgi == -1 ) { /* Si on n'arrive pas à se connecter au serveur FCGI */
		printf ( "Impossible de se connecter au serveur Fast CGI\n" );
		return NULL;
	} else { /* Si on arrive à se connecter */
		/* on créer le chemin absolu vers le script */
		char * real_pathname = NULL;
		int i, length;
		if ( pathname [0] == '/' ) { // on demande la racine du site 
			length = strlen ( pathname );
			real_pathname = malloc ( sizeof ( char ) * ( length ) );
			for ( i = 1; i <= length; i++ ) {
				real_pathname [i-1] = pathname [i];
			}
		} else {
			real_pathname = pathname;
		}
		real_pathname = strcat_without_alloc ( root_dir, real_pathname );

		/* on envoie à Fast CGI */
		int fcgi_len = 0;
		char * fcgi_request = add_fcgi_beg ( 1, 1, & fcgi_len );
		fcgi_request = add_fcgi_param ( 1, 1, "HTTP_HOST", "127.0.0.1", fcgi_request, & fcgi_len );
		fcgi_request = add_fcgi_param ( 1, 1, "HTTP_USER_AGENT", "Mozilla 5.0", fcgi_request, & fcgi_len );
		fcgi_request = add_fcgi_param ( 1, 1, "HTTP_ACCEPT", "text/html", fcgi_request, & fcgi_len );
		fcgi_request = add_fcgi_param ( 1, 1, "HTTP_ACCEPT_LANGUAGE", "en-US", fcgi_request, & fcgi_len );
		fcgi_request = add_fcgi_param ( 1, 1, "HTTP_ACCEPT_ENCODING", "gzip", fcgi_request, & fcgi_len );
		fcgi_request = add_fcgi_param ( 1, 1, "SERVER_SIGNATURE", "Tomahawk 1.0", fcgi_request, & fcgi_len );
		fcgi_request = add_fcgi_param ( 1, 1, "SERVER_SOFTWARE", "Tomahawk 1.0", fcgi_request, & fcgi_len );
		fcgi_request = add_fcgi_param ( 1, 1, "SERVER_NAME", "127.0.0.1", fcgi_request, & fcgi_len );
		fcgi_request = add_fcgi_param ( 1, 1, "SERVER_ADDR", "127.0.0.1", fcgi_request, & fcgi_len );
		fcgi_request = add_fcgi_param ( 1, 1, "SERVER_PORT", "8080", fcgi_request, & fcgi_len );
		fcgi_request = add_fcgi_param ( 1, 1, "REMOTE_ADDR", "127.0.0.1", fcgi_request, & fcgi_len );
		fcgi_request = add_fcgi_param ( 1, 1, "REMOTE_PORT", src_port_str, fcgi_request, & fcgi_len );
		fcgi_request = add_fcgi_param ( 1, 1, "DOCUMENT_ROOT", "/home/romain/Documents/Esisar/master2/Tomahawk/www", fcgi_request, & fcgi_len );
		fcgi_request = add_fcgi_param ( 1, 1, "DOCUMENT_URI", "/test.php", fcgi_request, & fcgi_len );
		fcgi_request = add_fcgi_param ( 1, 1, "REQUEST_SCHEME", "http", fcgi_request, & fcgi_len );
		fcgi_request = add_fcgi_param ( 1, 1, "SERVER_ADMIN", "test@tomahawk.fr", fcgi_request, & fcgi_len );
		fcgi_request = add_fcgi_param ( 1, 1, "GATEWAY_INTERFACE", "CGI/1.1", fcgi_request, & fcgi_len );
		fcgi_request = add_fcgi_param ( 1, 1, "SERVER_PROTOCOL", "HTTP/1.1", fcgi_request, & fcgi_len );
		fcgi_request = add_fcgi_param ( 1, 1, "REQUEST_METHOD", "GET", fcgi_request, & fcgi_len );
		fcgi_request = add_fcgi_param ( 1, 1, "QUERY_STRING", "", fcgi_request, & fcgi_len );
		fcgi_request = add_fcgi_param ( 1, 1, "REQUEST_URI", pathname, fcgi_request, & fcgi_len ); // <=======
		fcgi_request = add_fcgi_param ( 1, 1, "SCRIPT_NAME", pathname, fcgi_request, & fcgi_len ); // <=======
		fcgi_request = add_fcgi_param ( 1, 1, "SCRIPT_FILENAME", real_pathname, fcgi_request, & fcgi_len );
		fcgi_request = add_fcgi_end ( 1, 1, fcgi_request, & fcgi_len );

		if ( send ( sock_fcgi, fcgi_request, fcgi_len, 0 ) != fcgi_len ) {
      		printf ( "Mismatch in number of sent bytes\n" );
   		}

   		my_recv ( sock_fcgi );
	}
	
	return NULL;
}
char * add_fcgi_beg ( uint8_t ver, uint16_t id, int * len ) {
	char * res = malloc ( 16 );
	res [0] = ver; // version
	res [1] = 1; //type = FCGI_BEGIN_REQUEST
	res [2] = ( id >> 8 ) & 0xFF; res [3] = id & 0xFF; // identifiant sur 2 octets
	res [4] = 0; res [5] = 8; // content-length sur 2 octets
	res [6] = 0; // padding-length
	res [7] = 0; res [8] = 0; // begin request
	res [9] = 1; res [10] = 0; res [11] = 0; res [12] = 0; res [13] = 0; res [14] = 0, res [15] = 0;

	(*len) = 16;

	return res;
}

char * add_fcgi_param ( uint8_t ver, uint16_t id, char * name, char * value, char * req, int * len ) {
	uint8_t name_length = strlen ( name );
	uint8_t value_length = strlen ( value );
	uint16_t length = name_length + value_length + 2;
	char * res = malloc ( *(len) + 10 + length );
	int i;

	for ( i = 0; i < *(len); i++ ) { // on copie ce qui existe déjà 
		res [i] = req [i];
	}

	res [i+0] = ver; // version
	res [i+1] = 4; //type = FCGI_PARAMS
	res [i+2] = ( id >> 8 ) & 0xFF; res [i+3] = id & 0xFF; // identifiant sur 2 octets
	res [i+4] = ( length >> 8 ) & 0xFF; res [i+5] = length & 0xFF; // content-length sur 2 octets
	res [i+6] = 0; // padding-length
	res [i+7] = 0;
	res [i+8] = name_length;
	res [i+9] = value_length;

	for ( i = i + 10; i < *(len) + 10 + name_length; i++ ) { // le reste : params
		res [i] = name [i - *(len) - 10];
	}
	for ( i = i; i < *(len) + 10 + length - 1; i++ ) { // le reste : params
		res [i] = value [i - *(len) - 10 - name_length]; /* TO DO : probleme sur value */
	}

	(*len) += 8 + length;
	
	return res;
}

char * add_fcgi_end ( int ver, int id, char * req, int * len ) {
	char * res = malloc ( *(len) + 16 );
	int i;
	for ( i = 0; i < *(len); i++ ) { // on copie ce qui existe déjà 
		res [i] = req [i];
	}

	res [i+0] = ver; // version
	res [i+1] = 4; //type = FCGI_STDIN
	res [i+2] = ( id >> 8 ) & 0xFF; res [i+3] = id & 0xFF; // identifiant sur 2 octets
	res [i+4] = 0; res [i+5] = 0; // content-length sur 2 octets
	res [i+6] = 0; // padding-length
	res [i+7] = 0; // padding-length

	res [i+8] = ver; // version
	res [i+9] = 5; //type = FCGI_STDIN
	res [i+10] = ( id >> 8 ) & 0xFF; res [i+11] = id & 0xFF; // identifiant sur 2 octets
	res [i+12] = 0; res [i+13] = 0; // content-length sur 2 octets
	res [i+14] = 0; // padding-length
	res [i+15] = 0; // padding-length

	(*len) += 16;
	
	return res;
}

int send_fcgi_nav ( char * msg, int sock, int clientId ) {
	message * rep;
	char * buf;
	msg += 67;		//Correspond au champ content-length
	int content_length= (unsigned short) msg;	//on le recupère
	msg += 4;	//on passe le content-length et le padding
	buf = strcat_without_alloc_with_length ( "HTTP/1.0 200 OK", msg, content_length );
	
	rep->clientId = clientId;
	rep->len = content_length + strlen( "HTTP/1.0 200 OK" );
	rep->buf =  buf;
	
	sendReponse( rep );
	return 1;
} 

/*
	PARAM:
	|version|  type  | request id          | content-length    | padding-length | reserved: 0 | name-length | value-length | name | value |
	0       1        2                     4  				   6			    7			  8				9 			  10
*/



