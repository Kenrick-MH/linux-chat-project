/*
    This is an interface (API) for the client to interact
    with the chatting services.
*/

/* 
    *INCLUDES 
*/

// C INCLUDES
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>
#include <assert.h>
#include <stdio.h>

// CLIENT STATUSES
#include "client_statuses.h"

typedef int client_fd;

typedef struct client_handle {
    client_fd server_fd;
    struct sockaddr_in in_addr;
} client_handle;

/*
    Initializes a client handle with a specific internet addr (not logged in).
*/
client_handle* init_client(struct sockaddr_in in_addr);

/*
    Logs on to the chatting service.

    Post-Conditions:
        - If the user-password pair is not found within the server
        database, the login is unsucessful and the function returns.

    Returns the file descriptor that upon success and -1 upon error.
*/
client_status_t login(client_handle* handle, char* username, char* password);

/*
    Chats with a specific user, specified by the username.
    
    Pre-Conditions:
        - The function is called when the user is in the main
        page of the app (after logging in).

    Post-Conditions:
        - Opens up a new chatting window to chat with another user.
        - If user is not found, does nothing, prints a message
          stating that the user is not found.

    Returns 0 on success and -1 on error.
*/
client_status_t chat(client_handle* handle);

/*
    Chats with a specific user, specified by a UID.
    
    Pre-Conditions:
        - The function is called when the user is in the main
        page of the app (after logging in).

    Post-Conditions:
        - Opens up a new chatting window to chat with another user.
        - If user is not found, does nothing, prints a message
          stating that the user is not found.

    Returns 0 on success and -1 on error.
*/

client_status_t chat2(client_handle* handle);

/*
    Creates a group 
*/
client_status_t make_group(client_handle* handle, char* users[]);

client_status_t remove_chat(client_handle* handle, char* users[]);

/*
    Displays a list of contacts for a user
    
    * Pre-Conditions:
        - Clients must be already logged in to the server 
        before calling this function.
*/
client_status_t view_contacts(client_handle* handle);

/*
    Displays a list of commands available to the
    chatting app.

    * Pre-Conditions:
        - Clients must be already logged in to the server 
        before calling this function.
*/
client_status_t help();





























