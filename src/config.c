#include "config.h"

//===== VARIABLES GLOBALES =====//
char * gl_config[MAX_SITE][2];
int entryNumber;
char * gl_fastcgiAdress;
int gl_fastcgiPort;


//===== DEFINITIONS DES FONCTIONS =====//
void freeConfig() {
	int i;

	for (i = 0; i < entryNumber; i++) {
            free(gl_config[i][0]);
    	    free(gl_config[i][1]);
	}
        if (gl_fastcgiPort) {
            free(gl_fastcgiAdress);
        }
}

char * findInConfig(char * domaine) {
	int i;
    if ( domaine ) {
	   for (i = 0; i < entryNumber; i++) {
    		if(!strcmp(domaine, gl_config[i][0]) ) {
    			return gl_config[i][1];
    		}
    	}
    }
	return NULL;
}

char * getFastCGIAddress() {
    return gl_fastcgiAdress;
}


int getFastCGIPort() {
    return gl_fastcgiPort;
}

int isFastCGIConfigure(){
    if (gl_fastcgiPort)
        return 1;
    return 0;
}

// Parse des trucs comme : 
//		domaine_name=root_directory
int loadConfig() {
	
    char * configParameter;
    char * parseCharacter = "\n=";
    char * parseCharacterGlobal = "\n=:";
    FILE *file = fopen ( CONF_FILE, "r" );
    int space = 0;
    
    // initialisation
    gl_fastcgiPort = 0;
    entryNumber = 0;

    if ( file != NULL ) {
        char line [ 128 ];
        while ( fgets ( line, sizeof line, file ) != NULL ) {
            // Si la ligne n'est pas vide ou commente

            // On rentre dans la partie configuration globale
            if (!strcmp(line, "global_conf {\n")) {
                // On parcourt les lignes

                fgets ( line, sizeof line, file );

                while ( strcmp(line, "}\n" ) ) {
                    space = 0;
                    while(line[space] == '\t' || line[space] == ' ')
                        space++;
                    
                    if (line[space] != '#' && line[space] != '\n') {
                        configParameter = strtok(&line[space], parseCharacterGlobal);

                        if ( configParameter != NULL ) {
                            // Si c'est un champs connu
                            if (!strcmp(configParameter,"fast_cgi")) {

                                // On le parse
                                configParameter = strtok(NULL, parseCharacterGlobal);
                                if (configParameter == NULL) {
                                    printf("Bad configuration\n");
                                    exit(-1);
                                }
                                
                                gl_fastcgiAdress = malloc(sizeof(char) * ( strlen(configParameter) + 1 ));
                                strcpy( gl_fastcgiAdress, configParameter );
                                if (configParameter == NULL) {
                                    printf("Bad configuration\n");
                                    exit(-1);
                                }
                                
                                // On stocke le deuxieme arguments
                                configParameter = strtok(NULL, parseCharacterGlobal);
                                gl_fastcgiPort = atoi(configParameter);

                                // On verifie que la ligne est bien vide
                                configParameter = strtok(NULL, parseCharacter);
                                if (configParameter != NULL) {
                                    freeConfig();
                                    printf("Bad configuration\n");
                                    exit(-1);
                                }

                            }
                        // else (autre champs a venir)       
                        }
                    }
                    // Ligne suivante
                    fgets ( line, sizeof line, file);
                    if (line == NULL) {
                        printf("Bad configuration (lose brace)");
                        exit(-1);
                    }
                }
            }

            // On rentre dans la partie configuration des hostnames
            if (!strcmp(line, "domain_name {\n")) {
                fgets ( line, sizeof line, file );

                while ( strcmp(line, "}\n" ) ) {
                    // On rentre dans la partie nom de domaine
                    space = 0;
                    while(line[space] == '\t' || line[space] == ' ')
                        space++;
                    
                    if (line[space] != '#' && line[space] != '\n') {
                        // On parse
                        configParameter = strtok(&line[space], parseCharacter);
                        
                        // On verifie le premier arguments
                        if (configParameter == NULL) {
                            printf("Bad configuration\n");
                            exit(-1);
                        }
                        // On le stocke
                        gl_config[entryNumber][0] = malloc(sizeof(char) * (strlen(configParameter)+1));
                        strcpy(gl_config[entryNumber][0],configParameter);

                        // De meme pour le deuxime arguments
                        configParameter = strtok(NULL, parseCharacter);
                        
                        if (configParameter == NULL) {
                            freeConfig();
                            free(gl_config[entryNumber][0]);
                            printf("Bad coniguration\n");
                            exit(-1);
                        }

                        gl_config[entryNumber][1] = malloc(sizeof(char) * (strlen(configParameter)+1));
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
                    // Ligne suivante
                    fgets ( line, sizeof line, file);
                    if (line == NULL) {
                        printf("Bad configuration (lose brace)");
                        exit(-1);
                    }
                }
            }
        }
        fclose ( file );
    } else
    {
        perror ( "Configuration file not found!" );
        exit(-1);
    }

    if (entryNumber == 0) {
        printf("Bad configuration ( You need at least one domaine name )\n");
        exit(0);
    }
    return 0;
}

