#include "parser_debug_utils.h"

void display_packet(parse_packet_t* packet){
    if (packet == NULL) {
        printf("ERROR: NO PACKET\n");
    }

    char* request_type;

    switch (packet->req_code)
    {
    case LOGIN_REQUEST:
        request_type = "LOGIN_REQUEST";
        break;

    case LOGIN_REPLY:
        request_type = "LOGIN_REPLY";
        break;
    
    case CHAT_FROM_SERVER:
        request_type = "CHAT_FROM_SERVER";
        break;

    case CHAT_TO_SERVER:
        request_type = "CHAT_TO_SERVER";
        break;
    
    default:
        request_type = "UNKNOWN";
        break;
    }

    // Prints the message.
    printf(
        "==== PACKET CONTENTS ====\n"
        "Req.Type: %s\n"
        "Size  : %u\n"
        "Src   : %u\n"
        "Dest  : %u\n"
        "msg_size  : %s\n"
        "msg:\n", 
            request_type,
            packet->packet_size,
            packet->src_uid,
            packet->dest_uid,
            packet->msg_size);

    return;
}