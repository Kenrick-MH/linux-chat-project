#include "../../client/client-funcs.h"

void protoParseTests();

int main(){
    protoParseTests();
    return 0;
}

void protoParseTests(){
    char* buf = NULL;
    size_t len = 0;
    while (getline(&buf, &len, stdin) != -1){
        parseCommands(buf);
    }
}