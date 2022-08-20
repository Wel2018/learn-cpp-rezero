# 构建脚本

CC = g++ -std=c++17
BIN_PATH = ./bin
INCLUDE = ./include
SRC = ./src

logger: 
	${CC} -g -D DEBUG \
	-I ${INCLUDE} -I ${SRC} \
	test/test_logger.cpp  \
	-o ${BIN_PATH}/logger.out
	${BIN_PATH}/logger.out

threadpool: 
	${CC} -g -D DEBUG \
	-I ${INCLUDE} -I ${SRC} \
	test/test_threadpool.cpp  \
	-o ${BIN_PATH}/threadpool.out
	${BIN_PATH}/threadpool.out

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

