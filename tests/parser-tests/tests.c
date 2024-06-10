#include "../../cli-serv-msg-parser/msg-parser.h"
#include "parser_debug_utils.h"

#define NUM_TESTS 2
#define DUMMY_FILE "dummy.bin"

void testNoStringArgs();
void testStrArgs1();
void testStringArgs_Overflow();
void testMultipleMessages();

int main(){
    testNoStringArgs();
    testStrArgs1();
    return 0;
}

// Test suite for no string packets
void testNoStringArgs(){  
    printf("\nTest (1/%d): No string arguments\n", NUM_TESTS);
    
    // Client
    FILE* f1 = fopen(DUMMY_FILE, "wb+");
    int fd1 = fileno(f1);

    parse_packet_t p;
    p.dest_uid = 0xdeadbeef;
    p.msg_size = 0; 
    p.req_code = LOGIN_REQUEST;
    p.src_uid = 0xcafecafe;
    p.packet_size =  3 * sizeof(int);

    display_packet(&p);

    // Send file over the "network"
    uint8_t* buf;
    size_t buf_size = serialized_pack_size(&p);
    buf = pack_packet(&p);

    write(fd1, (void*) buf, buf_size);
    free(buf);

    // Server side
    FILE* f2 = fopen(DUMMY_FILE, "rb");
    int fd2 = fileno(f2);

    parse_packet_t* result = unpack_msg(fd2);
    printf("\n====================\n"
           "RECEIVING END PACKET\n"
           "====================\n");
    display_packet(result);
    assert(result->dest_uid == p.dest_uid);
    assert(result->msg_size == p.msg_size);
    assert(result->req_code == p.req_code);
    assert(result->src_uid == p.src_uid);
    assert(result->packet_size == p.packet_size);

    char* pack_msg = malloc(result->msg_size+1);
    memcpy(pack_msg, result->msg, result->msg_size);
    pack_msg[result->msg_size] = '\0';
    assert(strlen(pack_msg) == 0);
    free(pack_msg);
    free(result);
    fclose(f1);
    fclose(f2);

    printf("PASSED\n");  
}

void testStrArgs1(){
    printf("\nTest (2/%d): String arguments test\n", NUM_TESTS);
    FILE* send, *recv;
    int send_fd, recv_fd;
    send = fopen("dummy2.bin", "wb+");
    recv = fopen("dummy2.bin", "rb");
    send_fd = fileno(send);
    recv_fd = fileno(recv);

    // Client
    char* str = "Hello, World!";
    parse_packet_t* p = (parse_packet_t*) malloc(sizeof(parse_packet_t) + strlen("Hello, World!")+1);
    p->dest_uid = 0xbeefca3e; 
    p->req_code = CHAT_TO_SERVER;
    p->src_uid = 0xcafecafe;
    p->msg_size = strlen(str) + 1;
    strcpy(p->msg, str);
    p->packet_size =  3 * sizeof(int) + p->msg_size;

    display_packet(p);

    uint8_t* buf;
    size_t buf_size = serialized_pack_size(p);
    buf = pack_packet(p);

    write(send_fd, buf, buf_size);
    free(buf);

    parse_packet_t* result = unpack_msg(recv_fd);
    printf("\n====================\n"
           "RECEIVING END PACKET\n"
           "====================\n");
    display_packet(result);
    assert(result->dest_uid == p->dest_uid);
    assert(result->msg_size == p->msg_size);
    assert(result->req_code == p->req_code);
    assert(result->src_uid == p->src_uid);
    assert(result->packet_size == p->packet_size);
    assert(strcmp(str, result->msg) == 0);

    free(p);
    printf("PASSED\n");  
}

void testStringArgs_Overflow(){
    printf("Test (3/%d): No string arguments\n", NUM_TESTS);
}

// void testStringArgs_Overflow(){
//     printf("Test (3/%d): No string arguments\n", NUM_TESTS);
// }