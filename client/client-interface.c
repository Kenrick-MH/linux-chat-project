#include "client_interface.h"

#define SERVER_IP INADDR_LOOPBACK
#define SERVER_PORT 27069

/*
    Helper function to display a help message
*/
static void printHelpMessage(){
    printf(
        "                ========== LIST OF COMMANDS ==========             \n"
        " help -> displays a list of commands available for this chat window.\n"
        " make_group <list-of-users> -> adds users from the list to form a group\n"
        " remove <list-of-users> -> removes a chat room for the users in the list\n"
    );
}


// Helper function to check the password for the username over the network.
static client_status_t checkPassword(client_fd client_fd, char* username, char* password){
    return true;
}


client_status_t login(client_handle* handle, char* username, char* password){

    client_fd client_socket_fd = socket(PF_INET, SOCK_STREAM, 0);
    // Error check socket creation.
    if (client_socket_fd == -1){
        return CLIENT_SOCK_ERR;
    }

    int status = connect(client_socket_fd,(struct sockaddr*) &(handle->in_addr)
                            , sizeof(struct sockaddr_in));
    
    if (status == -1) return CLIENT_CONNECTION_FAIL;

    // Successful Connection.
    handle->server_fd = client_socket_fd;

    // Check Password.
    client_status_t c_status;
    if (c_status = checkPassword(client_socket_fd, username, password) == CLIENT_SUCCESS){
        return CLIENT_SUCCESS;
    } 
    
    return c_status;

}

/**
 * !PLACEHOLDER IMPLEMENTATIONS.
*/

int chat(client_handle* handle){
    printf("chatting\n");
    return 0;
}

int make_group(client_handle* handle, char* users[]){
    printf("making group\n");  
    return 0;  
}

int remove_chat(client_handle* handle, char* users[]){
    printf("removing chat\n");
    return 0;
}

int help(){
    printHelpMessage();
}