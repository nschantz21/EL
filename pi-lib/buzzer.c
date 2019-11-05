/*
 * buzzer.c
 *
 *  Created on: Mar 18, 2019
 *      Author: doug
 *
 *  Derived from a library module from Friendly ARM
 *
 *  Functions for managing the buzzer on the Matrix Compact board.
 */
#include <unistd.h>

#include "libmc-gpio.h"

static int buzzer_fd;

int init_buzzer (void)
{
	if ((buzzer_fd = exportGPIOPin (25)) < 0 )
		return -1;
	if (setGPIODirection (25, GPIO_OUT) < 0)
		return -1;
	return 0;
}

void close_buzzer (void)
{
	unexportGPIOPin (25);
}

void buzzer (int freq, int len)
/*
 * Sound the buzzer at the specified frequency, 'freq',
 * in hertz for 'len' milliseconds
 */
{
	int interval, count, i;

	interval = 1000000/(freq*2);
	count = (len*1000)/(interval*2);

	for (i = 0; i < count; i++)
	{
		setGPIOValue (buzzer_fd, 1);
		usleep (interval);
		setGPIOValue (buzzer_fd, 0);
		usleep (interval);
	}
}


