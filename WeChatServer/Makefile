INSTALL_PREFIX=/usr

#头文件路径
INCLUDE=-I${INSTALL_PREFIX}/include -I${INSTALL_PREFIX}/include/enet
INCLUDE+=-I../proto -I../../rocksdb/include/

#标准库
LIBS=-lpthread -lrt -lprotobuf -llog4cplus ${INSTALL_PREFIX}/lib/libenet.a
LIBS+=../proto/libproto.a ../../rocksdb/librocksdb.a -lz -lbz2 -std=gnu++11 -DROCKSDB_PLATFORM_POSIX  -DOS_LINUX -fno-builtin-memcmp -DROCKSDB_FALLOCATE_PRESENT -DZLIB -DBZIP2 -march=native

CFLAGS=-g -D__LOG4CPLUS__

all:bin/WeChatServer

bin/WeChatServer:Main.cpp WeChatServer.cpp WeChatServer.h
	if [ ! -d "bin" ];then mkdir bin;fi
	if [ ! -d "log" ];then mkdir log;fi
	g++ Main.cpp WeChatServer.cpp ${INCLUDE} ${LIBS} ${LIBS_MY} ${CFLAGS} -o $@

clean:
	rm bin/WeChatServer

rebuild:clean all