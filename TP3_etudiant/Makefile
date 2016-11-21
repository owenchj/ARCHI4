SYSTEMC   ?= /usr/local/systemc230
ARCH      ?= linux64

CC        = gcc
CXX       = g++

CFLAGS   +=  -g -Wall -std=gnu++0
CPPFLAGS  =  -isystem $(SYSTEMC)/include \
#	-DTP2_DEBUG -DSOCLIB_MODULE_DEBUG

CXXFLAGS  =  -Wall -O2 -g -Wno-deprecated
LDFLAGS   =  -g -L$(SYSTEMC)/lib-$(ARCH)
LDLIBS    =  -lsystemc -pthread
#-lpng
all:
	soclib-cc -p tp3_top.desc -o simulator.x

clean :
	rm -f $(EXE)
	rm -f $(OBJS)
	rm -rf picture.png
	rm -f $(DEPS)
	rm -f *.vcd
	rm -f *~ *_old
	rm -f core
	rm -f *.o
	rm -f term0
