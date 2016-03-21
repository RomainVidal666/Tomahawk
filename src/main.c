#include <stdio.h>
#include <stdlib.h>

#include "http_node.h"
#include "http_parser.h"
#include "api.h"

void callback(char* chaine, int len);

int main ( int argc, char * argv [] ) {

    parser ("METHOD 122.168.055.5 HTTP/1.2\n\r 153 Coucoddu !!!! :\n\rD",
            61, "http-message",callback);
	return 0;
}

void callback(char* chaine, int len) {
    printf("Chaine de longeur %d touvee : '%s'\n", len, chaine);
}
