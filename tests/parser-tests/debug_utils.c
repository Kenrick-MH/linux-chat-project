#include "parser_debug_utils.h"

void display_packet(parse_packet_t* packet){
    if (packet == NULL) {
        printf("ERROR: NO PACKET\n");
    }

    char* origin_str = packet->origin_flag == ORIGIN_SERVER ? "server" : "client";

    // Prints the message.
    printf(
        "==== PACKET CONTENTS ====\n"
        "Origin: %s\n"
        "Size  : %u\n"
        "Src   : %u\n"
        "Dest  : %u\n"
        "msg_size  : %s\n"
        "msg:\n", 
            origin_str,
            packet->packet_size,
            packet->src_uid,
            packet->dest_uid,
            packet->msg_size);

    return;
}