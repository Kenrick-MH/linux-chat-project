#include "msg-parser.h"

/*
    Determines the size of a packet.
*/
static size_t pack_size(parse_packet_t* p){
    return p->packet_size + 5 * TAG_SIZE + HEADER_SIZE;
}
