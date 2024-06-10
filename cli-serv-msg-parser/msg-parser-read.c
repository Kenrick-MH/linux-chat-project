#include "msg-parser.h"
/*
    *DESCRIPTION: 
        This file contains the implementation for 
        deserialization using read, and will only be 
        used for testing purposes only.
*/

parse_packet_t* unpack_msg(int fd){
    parse_packet_t* packet_ptr;
    uint8_t tagByte;

    // Keep reading until we reach a header opcode.
    if (read(fd, &tagByte, 1) != 1 || tagByte != HEADER_TAG){
        return NULL;
    }

    // Start to parse if a header tag is found.
    uint32_t packet_size;
    uint8_t header_opcode;
    uint32_t dest_uid, src_uid, msg_size;
    size_t content_bytes_read = 0;
    
    if (deserialize_header(fd, &packet_size, &header_opcode) != HEADER_SIZE){
        // skip to next header tag if fail
        return NULL;
    }

    // Parse next field
    if (deserialize_uint(fd, &src_uid) != FIELD_SIZE){
        // skip to next header tag if fail
        return NULL;
    }
    content_bytes_read += FIELD_SIZE;

    if (deserialize_uint(fd, &dest_uid) != FIELD_SIZE){
        // skip to next header tag if fail
        return NULL;
    }
    content_bytes_read += FIELD_SIZE;

    if (deserialize_uint(fd, &msg_size) != FIELD_SIZE){
        // skip to next header tag if fail
        return NULL;
    }
    content_bytes_read += FIELD_SIZE;

    // Before reading string buffer, try to check message size
    if (packet_size != 3 * FIELD_SIZE + msg_size){
        // If doesn't match search for another header tag.
        return NULL;
    }

    packet_ptr = malloc(sizeof(parse_packet_t) + msg_size);
    if (deserialize_string(fd, packet_ptr->msg, msg_size) != msg_size){
        free(packet_ptr);
        return NULL;
    }

    packet_ptr->dest_uid = dest_uid;
    packet_ptr->msg_size = msg_size;
    packet_ptr->req_code = header_opcode;
    packet_ptr->packet_size = packet_size;
    packet_ptr->src_uid = src_uid;

    return packet_ptr;

}

int deserialize_header(int fd, uint32_t* pack_size, uint8_t* req_code){
    // Try to read header.
    uint32_t combined_field;
    if (read(fd, &combined_field, HEADER_SIZE) != HEADER_SIZE){
        return -1;
    }

    combined_field = ntohl(combined_field);
    *pack_size = combined_field & 0xfffffff;
    *req_code = (uint8_t) (combined_field >> 28);

    return HEADER_SIZE;
}

int deserialize_uint(int fd, uint32_t* data){
    // Check tag
    uint8_t tag;
    if (read(fd, &tag, 1) != TAG_SIZE || tag != UINT_TAG){
        return -1;
    }

    if (read(fd, data, FIELD_SIZE) != FIELD_SIZE){
        return -1;
    }

    *data = ntohl(*data);
    return FIELD_SIZE;

}

int deserialize_string(int fd, char buf[], size_t len){
    // Check tag
    uint8_t tag;
    if (read(fd, &tag, 1) != TAG_SIZE || tag != STRING_TAG){
        return -1;
    }

    if (read(fd, buf, len) != len){
        return -1;
    }

    return len;
}