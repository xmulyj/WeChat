INSTALL_PREFIX=/usr

#头文件路径
INCLUDE=-I${INSTALL_PREFIX}/include -I${INSTALL_PREFIX}/include/enet
INCLUDE+=-I../proto

#标准库
LIBS=-lpthread -lrt -lprotobuf -llog4cplus ${INSTALL_PREFIX}/lib/libenet.a
LIBS+=../proto/libproto.a

CFLAGS=-g -D__LOG4CPLUS__

all:bin/WeChatServer

bin/WeChatServer:Main.cpp WeChatServer.cpp WeChatServer.h
	if [ ! -d "bin" ];then mkdir bin;fi
	if [ ! -d "log" ];then mkdir log;fi
	g++ Main.cpp WeChatServer.cpp ${INCLUDE} ${LIBS} ${LIBS_MY} ${CFLAGS} -o $@

clean:
	rm bin/WeChatServer

rebuild:clean all