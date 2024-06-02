#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// CONSTANTS
#define ORIGIN_SERVER 1
#define ORIGIN_CLIENT 0

// TAGS
#define HEADER_TAG 'h'
#define STRING_TAG 's'
#define INT_TAG 'i'

typedef enum {
    CLI_LOGIN
} request_type_t;

/**
 *  *Description:
 *     Represents a packet in the communication network, and is designed to 
 *     be serialized into the specified format below:
 * 
 *      | TAG | header | TAG  fields | ... | END |
 * 
*/
typedef struct parse_packet {
    // The two fields below will be the header of the packet.  
    uint32_t packet_size : 31; // The total size of the message
                               // packet (not including header)

    uint32_t origin_flag : 1; // Flag denoting the origin of the message
                              // true denoting server origin, false denoting
                              // client origin. 

    uint32_t src_uid;
    uint32_t dest_uid;
    uint32_t msg_size;
    char msg[];

} parse_packet_t;

/*
    Parse incoming messages between server and client.
*/
parse_packet_t* parse_receive_msg();

/*
    Sends a packet to the network.
    Returns 0 upon success and -1 on errors.
*/  
int pack_msg(parse_packet_t* packet);

// Cleans up any data dynamically allocated within packet.
void packet_cleanup(parse_packet_t* packet);


/*
    * ======= SERIALIZING FUNCTIONS =========
*/