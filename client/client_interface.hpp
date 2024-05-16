/*
    This is an interface (API) for the client to interact
    with the chatting services.
*/

/*
    Logs on to the chatting service.

    Post-Conditions:
        - If the user-password pair is not found within the server
        database, the user is prompted to re-enter the password
        again.
*/
int login();

/*
    Chats with a specific user, specified by the username.
    
    Pre-Conditions:
        - The function is called when the user is in the main
        page of the app (after logging in).

    Post-Conditions:
        - Opens up a new chatting window to chat with another user.
        - If user is not found, does nothing, prints a message
          stating that the user is not found.
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
*/

/*
    TODO: Finish the function definition for the other services
*/
int chat2();

int make_group();

int remove_chat();
































