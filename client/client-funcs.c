#include "client-funcs.h"
#include <stdio.h>
#define MAX_BUF_PARSE 1024

/*
    Parses user commands;
*/
int parseCommands(char* s){

    char* args[MAX_BUF_PARSE];
    int argNo = 0;
    while (*s != '\0' && argNo < MAX_BUF_PARSE){ 
        if (*s == ' ' || *s == '\t' || *s == '\n') {++s; continue;};
        // reached a non-whitespace character.

        args[argNo] = s;
        while (strchr(" \n\t\0", *s) == NULL) ++s;

        // reached another whitespace character OR NULL
        *(s++) = '\0', ++argNo;
    }

    args[argNo] = NULL;
    eval(args);
}

/*

*/
int eval(char* args[]){
    if (strcmp(args[0], "chat") == 0){
        chat();    
    } else if (strcmp(args[0], "make_group") == 0){
        make_group(args);
    } else if (strcmp(args[0], "remove") == 0){
        remove_chat(args); 
    } else {
        fprintf(stderr, "ERROR: Command not found!\n" 
                        "Please type \"help\"for a list of commands.\n");
    }
}