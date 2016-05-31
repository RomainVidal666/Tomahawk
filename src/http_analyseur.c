#include "http_analyseur.h"

int analyse(char * request, HTTP_Node * root) {
    int nb_node = 0, i;
    int nb = 0, lenght = 0;
    HTTP_Node * node;
    HTTP_Node * node_method;

    // Verification du nombre d'host
    count_HTTP_Node(root, "field-name", &nb_node);
    
    HTTP_Node * result[nb_node];
    
    foundAll_HTTP_Node (root, "field-name", &nb_node, result );

    for(i = 0; i < nb_node; i++) {
        if (HTTP_Node_is_equal(request, result[i], "Host")) {
            nb++;
        }
    }
    if (nb != 1){
        printf("Le champs 'Host' est invalide (plusieurs ou aucune occurence) !");
        return -1;
    }
    
    // HTTP Version
    nb_node = 0;
    count_HTTP_Node(root, "HTTP-version", &nb_node);
    
    node = found_HTTP_Node (root, "HTTP-version");
    
    if (nb_node != 1){
        printf("Le champs 'HTTP_version' est invalide (plusieurs ou aucune occurence) !");
        return -1;
    } else {
        if (!(HTTP_Node_is_equal(request, node, "HTTP/1.1") || HTTP_Node_is_equal(request, node, "HTTP/1.0"))) {
            printf("Le champs 'HTTP_version' est invalide (version non-supporte) !");
            return -1;
        }
    }

    // Methode (GET / POST)   
    nb_node = 0;
    count_HTTP_Node(root, "method", &nb_node);
    
    node_method = found_HTTP_Node (root, "method");
    
    if (nb_node != 1){
        printf("Le champs 'methode' est invalide (plusieurs ou aucune occurence) !\n");
        return -1;
    } else {
        if (!(HTTP_Node_is_equal(request, node_method, "GET") | HTTP_Node_is_equal(request, node_method, "POST"))) {
            printf("Le champs 'method' est invalide (methode non-supporte) !\n");
            return -1;
        }
    }
    
    // Taille
    nb = 0;
    count_HTTP_Node(root, "Content-Length", &nb);
    
    if ( HTTP_Node_is_equal(request, node, "POST") ) {
        if ( nb != 1 ) {
            printf("Le champs 'Content-Lenght' est invalide (plusieurs ou aucune occurence) !\n");
            return -1;
        }
    } else {
        if ( nb > 1 ) {
            printf("Le champs 'Content-lenght' est invalide (plusieurs occurences) !");
            return -1;
        }
        if ( nb == 1 ) {
            node = found_HTTP_Node (root, "Content-Lenght");
            lenght = atoi( get_field_value( request, root, "Content-Lenght"));
            if (lenght != 0) {
                printf("Le champs 'Content Lenght' est invalide (different de 0 pour la methode 'GET') !");
            }

        }
    }

    return 0;
}

