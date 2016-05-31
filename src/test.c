#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "percent_encoding.h"



int main ( int argc, char * argv [] ) {
	
	char * url="https://tools.ietf.org/html/rfc7230";
	
	normalizeURL(url);
	
	printf("%s", url);
}
