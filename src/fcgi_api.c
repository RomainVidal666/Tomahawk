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
    if (connect(sock, (struct sockaddr *) &echoserver, sizeof(echoserver)) < 0) {
      printf("Failed to connect with server\n");
  		return -1;
    }

    struct sockaddr_in local_address;
	int addr_size = sizeof(local_address);
	getsockname(sock, (struct sockaddr *) &local_address, &addr_size);
	(*src_port) = htons ( local_address.sin_port );

    return sock;
}

int my_recv ( int sock, char * msg ) {

    int bytes = 0;

    while ( ( bytes = recv ( sock, msg, BUFFSIZE - 1, 0 ) ) <= 0 ); // on attend de recevoir qqch
	int i;
    msg[bytes] = '\0'; 
    for ( i = 0; i < bytes; i++ ) {
    	printf ( "%c", msg[i]);
    }
    printf ( "\n" );

    return bytes;
}

char * read_from_fcgi ( char * pathname, char * root_dir, unsigned long long * taille ) {
	int src_port;
	int sock_fcgi = init_connection ( "127.0.0.1", 9000, &src_port );
	char src_port_str [6];
	snprintf ( src_port_str, 6, "%d", src_port );
	char buff [BUFFSIZE];

	if ( sock_fcgi == -1 ) { /* Si on n'arrive pas à se connecter au serveur FCGI */
		printf ( "Impossible de se connecter au serveur Fast CGI\n" );
		return NULL;
	} else { /* Si on arrive à se connecter */
		/* on créer le chemin absolu vers le script */
		char * real_pathname = NULL;
		int i, length;
		if ( pathname [0] == '/' ) { // on demande la racine du site 
			length = strlen ( pathname );
			real_pathname = malloc ( sizeof ( char ) * ( length - 1 ) );
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
		fcgi_request = add_fcgi_param ( 1, 1, "REQUEST_URI", "/test.php", fcgi_request, & fcgi_len ); // <=======
		fcgi_request = add_fcgi_param ( 1, 1, "SCRIPT_NAME", "test.php", fcgi_request, & fcgi_len ); // <=======
		fcgi_request = add_fcgi_param ( 1, 1, "SCRIPT_FILENAME", "/home/romain/Documents/Esisar/master2/Tomahawk/www/test.php", fcgi_request, & fcgi_len ); // <=======
		
                printf("add_fcgi_end\n");

		fcgi_request = add_fcgi_end ( 1, 1, fcgi_request, & fcgi_len );
                
                printf("Avant send\n");

		if ( send ( sock_fcgi, fcgi_request, fcgi_len, 0 ) != fcgi_len ) {
      		printf ( "Mismatch in number of sent bytes\n" );
   		}
                
                printf("Avant get_fcgi_response\n");

   		get_fcgi_response( sock_fcgi, buff );
	}
	
	return NULL;
}

char * add_fcgi_beg ( uint8_t ver, uint16_t id, int * len ) {
	char * res = malloc ( 15 );
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
	for ( i = i; i < *(len) + 10 + length; i++ ) { // le reste : params
		res [i] = value [i - *(len) - 10 - name_length];
	}

	(*len) += 8 + length;
	
	return res;
}

char * add_fcgi_end ( int ver, int id, char * req, int * len ) {
	char * res = malloc ( *(len) + 7 );
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

int get_fcgi_response ( int sock_fcgi, char * buff ) {
    int type = 0;
    unsigned short int content_length;
    char padding;

    char msg [ BUFFSIZE ];
    int buffExplore;
    int tailleReponse, taillePart;
    
    int i=0, j=0;

    buffExplore = 0;
    tailleReponse = 0;
    while ( type != 3 ) {
        taillePart = my_recv ( sock_fcgi, msg );
        for(i=0;i<taillePart/10;i=i+10){
            printf("\t[%d, %d, %d, %d, %d, %d, %d, %d, %d, %d]\n", msg[i], msg[i+1], msg[i+2], msg[i+3], msg[i+4], msg[i+5], msg[i+6], msg[i+7], msg[i+8], msg[i+9] ) ;
        }
        if(taillePart == 0) {
            printf("Pas de reponse du serveur FastCGI (ou incomplete, ou pas trouve, ou bug...)\n");
            return -1;
        }
        printf("Strcat chelou\n");
        buff = strcat_without_alloc_with_2_length ( buff, tailleReponse, msg, taillePart );
        printf("Qui passe pas\n");
        buffExplore++	;		//on passe la version
        type= buff[buffExplore];		//on recupere le type
        buffExplore ++;
        buffExplore ++;  		//Request ID
        content_length = (unsigned short) buff[buffExplore];	//on recupere le content_length
        buffExplore += 2;
        padding = (char) buff[buffExplore];		//on recupere le padding
        buff += 2;	
        //Content Data
        buff += content_length;
        buff += padding;
        printf("\n\n\n============================ Type : %d\n\n\n\n", type);
        
        for(i=0;i<20;i++){
            printf("\tbuff[%d]=%d\n", i, buff[i]);
        }
    }
    printf("Salut ! J'ai fini ta fonction :)\n");
    return 0;
}

int send_fcgi_nav ( char* msg, int clientId ) {
	int size=0;
	char * buf;
	int content_length;
	int fin=0;
	int type, padding;
	int is_data= 0;
	char * data;
	HTTP_Node * headers;
	HTTP_GET_response rep;	
	//msg+=42;		//on passe le TCP
	
	while (!fin){	//FCGI STDOUT
		msg++;			//on passe la version
		type= msg[0];		//on recupere le type
		msg++;
		msg++;			//Request ID
		content_length= (unsigned short) *msg;	//on recupere le content_length
		msg+=2;
		padding= (unsigned short) *msg;		//on recupere le padding
		msg+=2;	
		//Content Data
		int i=0;
		if( !is_data ){
			if ( parse_header_field ( msg, &i, headers) == -1)
				printf("ERREUR: champ field de fcgi invalide");
			int j= 0;
			for ( j=0; j<headers->nb_childs; j++ ){	//on parcours tous les headers
				strcat_without_alloc_with_length( data, msg + headers->childs[j]->beg , headers->childs[j]->end - headers->childs[j]->beg ); 
			}	
			if ( i<content_length ){
				is_data = 1;
			}
		}
		if( is_data ){
			while ( i<content_length && msg[i]!= '\0' )
				i++;
			strcat_without_alloc_with_length ( data, msg, i);
		}
		printf( "\nData:%s\n\n", msg );

	
		
		size+= content_length;

		if( type==3 ) fin=1;
	}
	rep.body = data;
	rep.code = 20;
	send_HTTP_GET_response( &rep, clientId, size );
	return 1;
} 
/*
	PARAM:
	|version|  type  | request id          | content-length    | padding-length | reserved: 0 | name-length | value-length | name | value |
	0       1        2                     4  				   6			    7			  8				9 			  10
*/
