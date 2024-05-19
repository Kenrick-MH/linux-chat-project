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

/*
    Logs on to the chatting service.

    Post-Conditions:
        - If the user-password pair is not found within the server
        database, the user is prompted to re-enter the password
        again.

    Returns 0 upon success and -1 upon error.
*/
int login(char* username, char* password);

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
int chat();

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


int chat2();

/*
    Creates a group 
*/
int make_group(char* users[]);

int remove_chat(char* users[]);
































