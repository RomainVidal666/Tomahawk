#include "config.h"

//===== VARIABLES GLOBALES =====//
char * gl_config[MAX_SITE][2];
int entryNumber;

//===== DEFINITIONS DES FONCTIONS =====//
void freeConfig() {
	int i;

	for (i = 0; i < entryNumber; i++) {
		free(gl_config[i][0]);
		free(gl_config[i][1]);
	}
}

char * findInConfig(char * domaine) {
	int i;
	for (i = 0; i < entryNumber; i++) {
		if(!strcmp(domaine, gl_config[i][0]) ) {
			return gl_config[i][1];
		}
	}
	return NULL;
}

// Parse des trucs comme : 
//		domaine_name=root_directory
int loadConfig() {
	
	char * configParameter;
	char * parseCharacter = "\n=";
	FILE *file = fopen ( CONF_FILE, "r" );
	entryNumber = 0;
	
	if ( file != NULL ) {
		char line [ 128 ];
 		while ( fgets ( line, sizeof line, file ) != NULL ) {
			// Si la ligne n'est pas vide ou commente
			if (line[0] != '#' && line[0] != '\n') {
				// On parse
				configParameter = strtok(line, parseCharacter);

				// On verifie le premier arguments
				if (configParameter == NULL) {
					printf("Bad configuration\n");
					exit(-1);
				}
				
				// On le stocke
				gl_config[entryNumber][0] = malloc(sizeof(char) * strlen(configParameter));
				strcpy(gl_config[entryNumber][0],configParameter);
				
				// De meme pour le deuxime arguments
				configParameter = strtok(NULL, parseCharacter);
				if (configParameter == NULL) {
					freeConfig();
					free(gl_config[entryNumber][0]);
					printf("Bad coniguration\n");
					exit(-1);
				}
				
				gl_config[entryNumber][1] = malloc(sizeof(char) * strlen(configParameter));
				strcpy(gl_config[entryNumber][1], configParameter);
				
				// On verifie que le nombre de site maximum n'est pas excede
				if (++entryNumber > MAX_SITE) {	
					printf("Bad configuration : too many website\n");
					freeConfig();
					exit(-1);
				}
				
				// On verifie que la ligne est bien vide
				configParameter = strtok(NULL, parseCharacter);
				if (configParameter != NULL) {
					freeConfig();
					printf("Bad configuration");
					exit(-1);
				}
			}
		}
		fclose ( file );
	} else {
		perror ( "Configuration file not found!" );
		exit(-1);
	}
	return 0;
}

