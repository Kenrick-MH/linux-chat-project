#include "parser_debug_utils.h"

void display_packet(parse_packet_t* packet){
    if (packet == NULL) {
        printf("ERROR: NO PACKET\n");
        return;
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

    char* pack_msg = malloc(packet->msg_size+1);
    memcpy(pack_msg, packet->msg, packet->msg_size);
    pack_msg[packet->msg_size] = '\0';

    // Prints the message.
    printf(
        "==== PACKET CONTENTS ====\n"
        "Req.Type: %s\n"
        "Size  : %u\n"
        "Src   : %x\n"
        "Dest  : %x\n"
        "msg_size  : %u\n"
        "msg:%s\n", 
            request_type,
            packet->packet_size,
            packet->src_uid,
            packet->dest_uid,
            packet->msg_size,
            pack_msg);

    free(pack_msg);

    return;
}