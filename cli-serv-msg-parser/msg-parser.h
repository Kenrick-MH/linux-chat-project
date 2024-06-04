#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

// CONSTANTS
#define ORIGIN_SERVER 1
#define ORIGIN_CLIENT 0
#define TAG_SIZE 1
#define HEADER_SIZE 4
#define FIELD_SIZE 4

// TAGS
#define HEADER_TAG 'h'
#define STRING_TAG 's'
#define UINT_TAG 'i'

// OPCODES
#define LOGIN_REQUEST 0b0001
#define LOGIN_REPLY 0b1001
#define CHAT_TO_SERVER 0b0010
#define CHAT_FROM_SERVER 0b1010

/**
 *  *Description:
 *     Represents a packet in the communication network, and is designed to 
 *     be serialized into the specified format below:
 * 
 *      | TAG | header | TAG  fields | ... | END |
 * 
 *      Where the header is 32 bits in network byte order, 
 *      and the fields are also in netwrok byte oreder if they are an integer,
 *      whereas for strings the data ordering would be preserved.
 * 
*/
typedef struct parse_packet {
    // The two fields below will be the header of the packet.  
    // In the deserialized representation, the packet_size
    // and req_code are separate.

    // However, note that the header will be a 32 bit
    // word when serialized.

    uint32_t packet_size; // The total size of the message
                            // packet (not including header)
    uint8_t req_code; // The type of request

    uint32_t src_uid;
    uint32_t dest_uid;
    uint32_t msg_size;
    char msg[];

} parse_packet_t;

/*
    Reads incoming messages between server and client.
    The returned packet is dynamically allocated in the heap.
*/
parse_packet_t* unpack_msg(int fd);

/*
    * ======= SERIALIZING FUNCTIONS =========
*/
/*
    Packs the data contained in a packet into an encoded bytestream.
    !IMPORTANT: the returned buffer is dynamically allocated.
*/
static uint8_t* pack_packet(parse_packet_t* data);

/*
    Serializes an integer into a bytestream.
    
    Output Invariant:
    - Increments the pointer to the bytestream by the size of an int,
        with a INT_TAG preceeding the data itself.
    - The serialized integer is in network byte order (big-endian)

*/
static void serialize_uint(int data, uint8_t** stream);

/*
    Serializes the header into a bytestream.

    Input Inavriant:
    - packet_size occupies 28 bits of the header word, while req_code
       occupies the remaining 4 bits.

    Output Invariant:
    - Increments the pointer to the bytestream by the size of an int,
        with a INT_TAG preceeding the data itself.
    - The serialized integer is in network byte order (big-endian)

*/
static void serialize_header(uint32_t packet_size, uint8_t req_code, uint8_t** stream);

/*
    Serializes a string into a bytestream.
    
    Output Invariant:
    Increments the pointer to the bytestream by the length of the string,
    with STRING_TAG preceeding the data contained within the string.
*/
static void serialize_string(char* str, size_t len, uint8_t** stream);

/*
    *DESERIALIZING FUNCTIONS
*/

/*
    Deserializes a header from a file descriptor, 
    after the HEADER_TAG is read.
    
    Output Invariant:
        - If the read operation fails or the number
          of bytes read is different from the header size return -1.
          The reader would then proceed until another header TAG is found.

        - Otherwise, msg_size and req_code will be filled with 
            the packet size and request code respectively, 
            and the function returns the number of bytes read.

*/
static int deserialize_header(int fd, uint32_t* pack_size, uint8_t* req_code);

/*
    Deserializes an unsigned integer from a file descriptor, 
    including the UINT_TAG.

    Input Invariant:
        - The function is called after a successful header
            deserialziation.
    
    Output Invariant:
        - If the read operation fails, or the first byte read 
          is not a UINT_TAG, return -1. The reader would
          then proceed until another HEADER_TAG is found.

        - Otherwise, msg_size and req_code will be filled with 
            the packet size and request code respectively, 
            and the function returns the number of bytes read.

*/
static int deserialize_uint(int fd, uint32_t* data);

/*
    Deserializes a string from a file descriptor.

    Input Invariant: 
        - The string, data is already dynamically allocated.
    
    Output Invariant:
        - If the read operation fails, or the first byte read 
          is not a STRING_TAG, return -1. The reader would then
          proceed until another HEADER_TAG is found. The argument
          data would then would be deallocated.

        - Otherwise, msg_size and req_code will be filled with 
            the packet size and request code respectively, 
            and the function returns the number of bytes read.

*/
static int deserialize_string(int fd, char buf[], size_t len);

/*
    *HELPER FUNCTIONS
*/
/*
    Determines the size of a packet.
*/
static size_t calculate_pack_size(parse_packet_t* p);
