
CFLAGS += -Wall -g -Og
INC := ../includes 

all: led

led: led.o
	$(CC) -o $@ $^ -lmchw -L../pi-lib 
led.o: led.c
	$(CC) $(CFLAGS) -c led.c -I$(INC)

clean:
	rm -f *.o *_t *_s *~ core

	