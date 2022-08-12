# 构建脚本

CC = g++ -std=c++17
BIN_PATH = ./bin
INCLUDE = ./include
SRC = ./src

memcheck:
	${CC} -g -D DEBUG \
	-I ${INCLUDE} -I ${SRC} \
	test/test_memcheck.cpp  \
	-o ${BIN_PATH}/memcheck.out
	${BIN_PATH}/memcheck.out

allocator:
	${CC} -g -D DEBUG \
	-I ${INCLUDE} -I ${SRC} \
	test/test_allocator.cpp  \
	-o ${BIN_PATH}/allocator.out
	${BIN_PATH}/allocator.out

objpool:
	${CC} -g -D DEBUG \
	-I ${INCLUDE} -I ${SRC} \
	test/test_objpool.cpp  \
	-o ${BIN_PATH}/objpool.out
	${BIN_PATH}/objpool.out

