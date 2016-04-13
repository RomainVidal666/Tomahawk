#include <stdio.h>
#include <stdlib.h>

#include "http_node.h"
#include "http_parser.h"
#include "api.h"

void callback(char* string, int len) {
    printf("CALLBACK : Trouve : %s\n", string);
}

int main ( int argc, char * argv [] ) {
	int cursor = 0;
	HTTP_Node * http_message = malloc ( sizeof ( HTTP_Node ) );

	//Request 1->6 OK
	//Request 7->9 FAUX car SP après le field-content en fin de ligne
	//Request 10 FAUX car version A.1
	//Request 11->12 OK
	/*ok*///char request [] = "GET / HTTP/1.1\r\nHost:www.cvedetails.com\r\nUser-Agent:Mozilla/5.0 (X11; Linux x86_64; rv:44.0) Gecko/20100101 Firefox/44.0 (\"comment\")\r\nAccept:		 text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\nAccept-Language:	fr,fr-FR;q=0.8,en-US;q=0.5,en;q=0.3\r\nAccept-Encoding :	fr,fr-FR;q=0.8,en-US;q=0.5,en;q=0.3\r\nConnection: tryit\r\n\r\n";
	/*ok*///char request [] = "GET / HTTP/1.1\r\nHost: www.cvedetails.com\r\nUser-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:44.0) Gecko/20100101 Firefox/44.0 (\"comment\") \r\nAccept:		 text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\nAccept-Language:	fr,fr-FR;q=0.8,en-US;q=0.5,en;q=0.3	\r\nAccept-Encoding: *   ; q=0.876\r\nConnection: tryit\r\n\r\n";
	/*ok*///char request [] = "NINJATURTLE / HTTP/A.1\r\nUser-Agent: Wget/1.16 (linux-gnu)\r\nAccept: */*\r\nHost: www.google.com\r\nConnection: Keep-Alive\r\n\r\n";
	/*ok*///char request [] = "NINJATURTLE /niNjA/chuck/maurice/ HTTP/9.1\r\nPrenom: Chuck\r\nNom: Maurice\r\n\r\nOne ring to rule them all\r\n";
	/*ok*///char request [] = "NINJATURTLE /niNjA/chuck/maurice/ HTTP/9.1\r\nPrenom: Chuck\r\nNom: Maurice\r\n\r\nOne ring to rule them all";
	/*ok*///char request [] = "POST /fichier.ext HTTP/1.1\r\nHost: www.site.com\r\nConnection: Close\r\nContent-type: application/x-www-form-urlencoded\r\nContent-Length: 33\r\n\r\nvariable=valeur&variable2=valeur2";
	/*ok*///char request [] = "HTTP/1.1 200 OK\r\nDate: Thu, 11 Jan 2007 14:00:36 GMT\r\nServer: Apache/2.0.54 (Debian GNU/Linux) DAV/2 SVN/1.1.4\r\nConnection: close\r\nTransfer-Encoding: chunked\r\nContent-Type: text/html; charset=ISO-8859-1\r\n\r\n";
	/*ok*///char request [] = "GET http://www.commentcamarche.net HTTP/1.0\r\nAccept: text/html\r\nIf-Modified-Since: Saturday, 15-January-2000 14:37:11 GMT\r\nAccept: text/html\r\nAccept: text/html\r\nAccept: text/html\r\nAccept: text/html\r\nAccept: text/html\r\nAccept: text/html\r\nAccept: text/html\r\nAccept: text/html\r\nAccept: text/html\r\nAccept: text/html\r\nAccept: text/html\r\nAccept: text/html\r\nAccept: text/html\r\nAccept: text/html\r\nAccept: text/html\r\nAccept: text/html\r\nAccept: text/html\r\nAccept: text/html\r\nAccept: text/html\r\nAccept: text/html\r\nAccept: text/html\r\nAccept: text/html\r\nAccept: text/html\r\nAccept: text/html\r\nAccept: text/html\r\nAccept: text/html\r\nAccept: text/html\r\nAccept: text/html\r\nAccept: text/html\r\nAccept: text/html\r\nAccept: text/html\r\nAccept: text/html\r\nAccept: text/html\r\nAccept: text/html\r\nAccept: text/html\r\nAccept: text/html\r\nAccept: text/html\r\nAccept: text/html\r\nAccept: text/html\r\nAccept: text/html\r\nAccept: text/html\r\nAccept: text/html\r\nAccept: text/html\r\nAccept: text/html\r\nAccept: text/html\r\nAccept: text/html\r\nAccept: text/html\r\nUser-Agent: Mozilla/4.0 (compatible; MSIE 5.0; Windows 95)\r\n\r\n";
	char request [] = "GET / HTTP/1.1\r\nUser-Agent: Wget/1.16 (linux-gnu)\r\nAccept: */*\r\nHost: www.google.com\r\nConnection: Keep-Alive\r\n\r\n"
	if ( parse_HTTP_message ( request, &cursor, http_message ) ) { 
		printf ( "La requete est valide \n" );
		print_HTTP_Tree ( request, http_message, 0 );
	}
		//printf("%c\n",request[cursor]);
	
	/*printf ( "***************************** PARSER *****************************\n");
	int nb = parser (request, strlen(request), "field-name" ,callback);
*/
	free_HTTP_Tree ( http_message );

	return 0;
}
