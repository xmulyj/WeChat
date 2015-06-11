INSTALL_PREFIX=/usr

#头文件路径
INCLUDE=-I${INSTALL_PREFIX}/include -I${INSTALL_PREFIX}/include/enet
#INCLUDE+=

#标准库
LIBS=-lpthread -lrt -lprotobuf -llog4cplus ${INSTALL_PREFIX}/lib/libenet.a
#LIBS+=

CFLAGS=-g -D__LOG4CPLUS__

all:bin/WeCacheServer

bin/WeCacheServer:Main.cpp WeCacheServer.cpp WeCacheServer.h
	if [ ! -d "bin" ];then mkdir bin;fi
	if [ ! -d "log" ];then mkdir log;fi
	g++ Main.cpp WeCacheServer.cpp ${INCLUDE} ${LIBS} ${CFLAGS} -o $@

clean:
	rm bin/WeCacheServer

rebuild:clean all