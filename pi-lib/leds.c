/*
 * leds.c
 *
 *  Created on: Mar 18, 2019
 *      Author: doug
 *
 *  Derived from a library module from Friendly ARM
 *
 *  Collection of functions for the LEDs and the push buttons on the
 *  Matrix Compact board. This file is common to both pi-lib and sim-lib
 */

#include "libmc-gpio.h"

/* Map the LEDs to GPIO bits */
static int led[4] = {13, 6, 26, 19};
static int ledfd[4];

int init_leds (void)
/*
 * Sets up the four LEDs on the Matrix Compact board.
 * On success, 'ledfd' is populated with open file
 * descriptors for value files of each LED. Note that
 * setting direction to "out" also sets the bit to 0.
 */
{
	int i;

	for (i = 0; i < 4; i++)
	{
		if ((ledfd[i] = exportGPIOPin (led[i])) < 0)
			return -1;
		if (setGPIODirection (led[i], GPIO_OUT) < 0)
			return -1;
	}
	return 0;
}

void close_leds (void)
/*
 * Unexport the gpios associated with the LEDs
 */
{
	int i;

	for (i = 0; i < 4; i++)
	{
		unexportGPIOPin (led[i]);
	}
}

void ledON (int led)
{
	setGPIOValue (ledfd[led], 1);
}

void ledOFF (int led)
{
	setGPIOValue (ledfd[led], 0);
}

		/*** Pushbuttons ***/

/* Map the pushbuttons to GPIO bits */
static int pb[3] = {16, 20, 21};
static int pbfd[3];

int init_pbs (void)
/*
 * Note that we don't need to set the direction
 * because the default is IN. But we do need to
 * set active_low.
 */
{
	int i;

	for (i = 0; i < 3; i++)
	{
		if ((pbfd[i] = exportGPIOPin (pb[i])) < 0)
			return -1;
		if (setGPIOLow (pb[i], GPIO_ACTIVE_LOW) < 0)
			return -1;
	}
	return 0;
}

void close_pbs (void)
/*
 * Unexport the gpios associated with the pushbuttons
 */
{
	int i;

	for (i = 0; i < 3; i++)
	{
		unexportGPIOPin (pb[i]);
	}
}

int read_pbs (void)
/*
 * Returns a 3-bit mask where a 1 represents a pushed button
 */
{
	int i, res, ret = 0, mask = 1;

	for (i = 0; i < 3; i++, mask <<= 1)
	{
		if ((res = getGPIOValue (pbfd[i])) == 1)
				ret |= mask;
		if (res == -1)
			ret |= 8;
	}
	return ret;
}


