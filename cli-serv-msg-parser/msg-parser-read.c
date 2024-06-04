#include "msg-parser.h"
/*
    *DESCRIPTION: 
        This file contains the implementation for 
        deserialization using read, and will only be 
        used for testing purposes only.
*/

parse_packet_t* unpack_msg(int fd){
    parse_packet_t* packet_ptr;
    uint8_t opCodeByte;

    // Keep reading until we reach a header opcode.
    while (read(fd, &opCodeByte, 1) == 1){
        // Start to parse
        if (opCodeByte == HEADER_TAG){
            
        }
    }




}