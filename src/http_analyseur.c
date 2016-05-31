
#include "http_analyseyr.h"

int analyse(char * request, HTTP_Node root) {
    int nb_node, i;
    int nb;
    HTTP_Node node;

    // Verification du nombre d'host
    count_HTTP_Node(root, "Field Name", &nb_node);
    
    HTTP_Node result[nb_node];
    
    foundAll_HTTP_Node (root, "Host", nb_node, result );

    for(i = 0, i < nb_node, i++) {
        if (HTTP_Node_is_equal(request, result[i], "Host")) {
            nb++;
    }
    if (nb != 1){
        printf("Le champs 'Host' est invalide (plusieurs ou aucune occurence) !");
        return -1;
    }

    // HTTP Version
    count_HTTP_Node(root, "HTTP-version", &nb_node);
    
    node = found_HTTP_Node (root, "HTTP-version", result );
    
    if (nb_node != 1){
        printf("Le champs 'HTTP_version' est invalide (plusieurs ou aucune occurence) !");
        return -1;
    } else {
        if (HTTP_Node_is_equal(request, node, "HTTP/1.1") | HTTP_Node_is_equal(reqest, node, "HTTP/1.0")) {
            printf("Le champs 'HTTP_version' est invalide (version non-supporte) !");
            return -1;
    }

    // Methode (GET / POST)   
    count_HTTP_Node(root, "methode", &nb_node);
    
    node = found_HTTP_Node (root, "methode", result );
    
    if (nb_node != 1){
        printf("Le champs 'methode' est invalide (plusieurs ou aucune occurence) !");
        return -1;
    } else {
        if (HTTP_Node_is_equal(request, node, "GET") | HTTP_Node_is_equal(reqest, node, "POST")) {
            printf("Le champs 'methode' est invalide (methode non-supporte) !");
            return -1;
    }
    // Taille

    // ...
}
