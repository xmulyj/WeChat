SRCS=$(wildcard *.cc)
OBJS=$(patsubst %.cc, %.o, $(SRCS))
INCLUDE=-I./
FLAGS=

LIBNAME=libproto.a


all:$(OBJS) lib

%.o:%.cc
	g++ -fPIC ${INCLUDE} $< ${FLAGS} -c -o $@

lib:
	ar -cr ${LIBNAME} $(OBJS)
	
clean:
	rm libproto.a *.o *.cc *.h *.py *.pyc
