#
# 
#  Makefile for ARM/Linux user application
# 

CFLAGS = -g -O0 -Wall -DPORT=4201 -DSERVER=\"192.168.15.50\"
INC_ARM := ../includes

all: oledtest

oledtest: oledtest.c
	$(CC) $(CFLAGS) -o $@ -I$(INC_ARM) -lmchw -L../pi-lib oledtest.c
	
thermostat.o: thermostat.c		
	$(CC) $(CFLAGS) -c -I$(INC_ARM) thermostat.c
monitor.o: monitor.c		
	$(CC) $(CFLAGS) -c -I$(INC_ARM) monitor.c

netthermo_t: thermostat.o monitor.o
	$(CC) -o $@ $^ -lpthread -lmchw -L../pi-lib

clean:
	rm -f *.o
