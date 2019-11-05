/*
 * led.c
 *
 *  Created on: Feb 19, 2019
 *      Author: Doug Abbott
 *
 *      Simple test program for peripheral I/O. Sequentially blinks the LEDs
 *      on the Matrix Compact hat and reads the pushbuttons.

 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

#include "libmc-gpio.h"

int running = 1;

void done (int sig)
/*
    Signal handler to stop the program gracefully
*/
{
    running = 0;
}

int main (int argc, char *argv[])
{
	int i, pbs;

    signal (SIGINT, done);  // set up signal handler

    if (init_leds() < 0)
    {
    	printf ("Couldn't initialize LEDs\n");
		return -1;
    }
    if (init_pbs() < 0)
    {
    	printf ("Couldn't initialize pushbuttons\n");
    	close_leds();
		return -1;
    }
    printf ("The Embedded Linux Learning Kit from Intellimetrix\n");

	while (running)
	{
		for (i = 0; i < 4; i++)
		{
			int j;
			ledON (i);
			sleep (1);
			ledOFF (i);

			pbs = read_pbs();
			for (j = 0; j < 3; j++, pbs >>= 1)
				if ((pbs & 1) > 0)
					printf ("Button %d pressed\n", j + 1);
		}
	}
	close_leds();
	close_pbs();
	return 0;
}
