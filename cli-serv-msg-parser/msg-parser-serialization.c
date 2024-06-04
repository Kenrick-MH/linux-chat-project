#include "msg-parser.h"

/*
    Packs the data contained in a packet into an encoded bytestream.
*/
static uint8_t* pack_packet(parse_packet_t* data){
    size_t stream_buf_size = pack_size(data);
    uint8_t* buf = malloc(stream_buf_size);

    // If no memory left
    if (buf == NULL) return NULL;
    uint8_t* stream_ptr = buf;
    
    // Serializing each section
    serialize_header(data->packet_size, data->req_code, &stream_ptr);
    serialize_int(data->src_uid, &stream_ptr);
    serialize_int(data->dest_uid, &stream_ptr);
    serialize_int(data->msg_size, &stream_ptr);
    serialize_string(data->msg, data->msg_size, &stream_ptr);

    // check if total bytes traversed is the same
    assert(stream_ptr - buf == stream_buf_size);
    return buf;
}

static void serialize_header(uint32_t packet_size, uint8_t req_code, uint8_t** stream){
    uint32_t combined = packet_size | ((uint32_t) req_code << 28);
    uint32_t encoded_header = htonl(combined);
    *((*stream)++) = HEADER_TAG;
    for (int i = 3; i >= 0; --i){
        *((*stream)++) = (uint8_t) (combined >> (8 * i)) & 0xff;
    } 

}

static void serialize_uint(int data, uint8_t** stream){
    uint32_t encoded_data = htonl(data);    // 0xabcdef12 => 0x12fecdab
    *((*stream)++) = UINT_TAG;
    for (int i = 3; i >= 0; --i){
        *((*stream)++) = (uint8_t) (encoded_data >> (8 * i)) & 0xff;
    }   
}

static void serialize_string(char* str, size_t len, uint8_t** stream){
    *((*stream)++) = STRING_TAG;
    for (int i = 0; i < len; ++i){
         *((*stream)++) = str[i];
    }
}

