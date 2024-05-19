#include "client_interface.h"



int login(char* username, char* password){
    int client_socket = socket(PF_INET, SOCK_STREAM, 0);
}

/**
 * !PLACEHOLDER IMPLEMENTATIONS.
*/

int chat(){
    printf("chatting\n");
    return 0;
}

int make_group(char* users[]){
    printf("making group\n");  
    return 0;  
}

int remove_chat(char* users[]){
    printf("removing chat\n");
    return 0;
}