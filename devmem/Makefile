#
# 
#  Makefile for ARM/Linux user application
# 

SHELL = /bin/sh

CFLAGS += -Wall -g

APP = devmem

all: ${APP}

${APP}: ${APP}.c
	${CC} -o ${APP} $?

clean:
	rm -f *.o
