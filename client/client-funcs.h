#include "client_interface.h"
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
#include <string.h>

int connectToServer();

void startupMessage();

/*
    Prompts the user for credentials.
    Returns true upon sucessful login, false for unsucessful login.
    Exits the program if there is an error.
*/
bool promptCredentials();

int eval(char* args[]);

/*
    Parses user commands;
*/
int parseCommands(char* s);