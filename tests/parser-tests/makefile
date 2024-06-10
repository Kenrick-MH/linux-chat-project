
SRC_DIR := ../../cli-serv-msg-parser
EXCLUDE_FILE := ../../cli-serv-msg-parser/msg-parser-recv.c 

SRCS := $(wildcard $(SRC_DIR)/*.c)
SRCS := $(filter-out $(EXCLUDE_FILE), $(SRCS))

parser-test: ../../cli-serv-msg-parser/msg-parser.h  $(SRCS) parser_debug_utils.h tests.c debug_utils.c
	gcc -g $^ -o $@ 