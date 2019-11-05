#  Posix threads version of thermostat

#  make          -- build the simulation version of thermostat.c
#  make TARGET=1 -- build the target version of thermostat.c

CFLAGS += -Wall -g -Og
INC := ../includes

ifdef TARGET
all: thermostat_t
thermostat.o: thermostat.c $(INC)/driver.h $(INC)/thermostat.h		# compile for the ARM
	$(CC) $(CFLAGS) -c -I$(INC) thermostat.c
monitor.o : monitor.c $(INC)/driver.h $(INC)/thermostat.h
	$(CC) $(CFLAGS) -c  -I$(INC) monitor.c
else
all: thermostat_s
thermostat.o: thermostat.c $(INC)/driver.h $(INC)/thermostat.h	# compile for x86
	gcc $(CFLAGS) -c -I$(INC) thermostat.c
monitor.o : monitor.c $(INC)/driver.h $(INC)/thermostat.h
	gcc $(CFLAGS) -c  -I$(INC) monitor.c
endif

thermostat_s : thermostat.o monitor.o
	gcc -o $@ $^ -lpthread -lsim -L../sim-lib

thermostat_t : thermostat.o monitor.o
	$(CC) -o $@ $^ -lpthread -lmchw -L../pi-lib

clean :
	rm -f *.o *_t *_s *~ core
