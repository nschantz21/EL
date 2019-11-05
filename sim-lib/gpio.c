/*
 * gpio.c
 *
 *  Created on: Mar 14, 2019
 *      Author: Doug Abbott
 *
 *  Library functions for simulating Raspberry Pi GPIO bits.
 *  This serves two purposes: it serves as a sanity check on
 *  whether or not pins have been exported and also communicates
 *  with whatever simulation process may also be running.
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>

#define DRIVER

#include "driver.h"
#include "libmc-gpio.h"

typedef struct {
	int export;
	int dir;
	int active;
	int value;
} pin;
pin GPIO[25];

shmem_t *p;
static int num_export = 0;

int exportGPIOPin (int pin)
/*
 * Return the index into GPIO[]
 */
{
	if ((pin < 2) || (pin > 26))
		return -1;
	else
	{
		GPIO[pin - 2].export = 1;
/*
 * There should be a simulation process waiting for a connection from the library.
 * If this is the first time exportGPIOPin() has been called, connect to the
 * shared memory region of the simulator.
 *  */
		if (++num_export == 1)
		{
			int id;

		    id = shmget ((key_t) SHM_KEY, sizeof (shmem_t), 0666);
		    if ((id  < 0) || ((p = (shmem_t *) shmat (id, (void *) 0, 0)) == (shmem_t *) -1))
			   {
		    		printf ("Couldn't set up shared memory. Error: %s\n", strerror (errno));
		        	return -1;
			   }
		    p->GPIOmask = 0;
			
		// Get the device's output started
		    kill (p->pid, SIGUSR1);
		}
        return pin;
	}
}

int unexportGPIOPin (int pin)
/*
 * Return an error if 'pin' has not been exported.
 */
{
	pin -= 2;
	if (GPIO[pin].export)
	{
		if (--num_export == 0)
/*
 * If this is the last exported pin, disconnect from the
 * shared memory region.
 */
		{
		    shmdt (p);
		}
		GPIO[pin].export = 0;
		return 1;
	}
	else
		return -1;
}
int getGPIOValue (int pin)
/*
 * Return the current state of 'pin' if it has been exported
 */
{
    if (GPIO[pin-2].export)
    {
    	return (p->GPIOmask >> pin) & 1;
    }
    else
    {
    	printf ("Pin %d is not exported\n", pin);
    }
    return -1;
}

size_t setGPIOValue (int pin, int value)
/*
 * Sets the GPIO pin  to 'value' (0 or 1) if it is exported
 * and configured as output. Also signals whatever simulation
 * process is waiting on output changes. Returns positive value on success.
 */
{
	unsigned int mask = 1 << pin;
	
	pin -= 2;
    if (GPIO[pin].export)
    {
    	if (GPIO[pin].dir)
    	{
    		if (value)
				p->GPIOmask |= mask;
			else
				p->GPIOmask &= ~mask;
			
		// Signal simulation
    		kill (p->pid, SIGUSR1);
			return 1;
    	}
    	else
    	{
        	printf ("Pin %d is not configured for output\n", pin + 2);
        	return -1;
    	}
    }
	else
    {
    	printf ("Pin %d is not exported\n", pin + 2);
    	return -1;
    }
}

int setGPIODirection (int pin, int direction)
/*
 * Set the 'direction' (in or out) of 'pin'.
 */
{
    if ((direction < GPIO_IN) || (direction > GPIO_OUT))
    {
        printf ("direction must be 1 or 2,  1->in, 2->out\n");
        return -1;
    }
    pin -= 2;
    if (GPIO[pin].export)
    {
    	GPIO[pin].dir = direction - 1;
    	return 1;
    }
    else
    {
    	printf ("Pin %d is not exported\n", pin + 2);
    	return -1;
    }
}

int getGPIODirection (int pin)
/*
 * Return the direction (in or out) if 'pin'.
 */
{
	pin -= 2;
    if (GPIO[pin].export)
    	return GPIO[pin].dir + 1;
    else
    {
    	printf ("Pin %d is not exported\n", pin + 2);
    	return -1;
    }
}
int setGPIOLow (int pin, int low)
/*
 * Set active state (low or high) of 'pin'.
 */
{
    if ((low < GPIO_LOW) || (low > GPIO_HIGH))
    {
        printf ("active must be 0 or 1,  0->low, 1->high\n");
        return -1;
    }
    pin -= 2;
    if (GPIO[pin].export)
    {
    	GPIO[pin].active = low;
    	return 1;
    }
    else
    {
    	printf ("Pin %d is not exported\n", pin + 2);
    	return -1;
    }
}

int getGPIOLow (int pin)
/*
 * Return the active state (low or high) if 'pin'.
 */
{
	pin -= 2;
    if (GPIO[pin].export)
    	return GPIO[pin].active;
    else
    {
    	printf ("Pin %d is not exported\n", pin + 2);
    	return -1;
    }
}
