#include "msg-parser.h"

/*
    Determines the size of a packet.
*/
size_t serialized_pack_size(parse_packet_t* p){
    return p->packet_size + 5 * TAG_SIZE + HEADER_SIZE;
}
