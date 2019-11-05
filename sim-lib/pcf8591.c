/*
 * pcf8591.c
 *
 *  Created on: Mar 11, 2019
 *      Author: Doug Abbott
 *
 * Library functions for accessing the pcf8591 ADC converter 
 * through the simulator.
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define DRIVER

#include "libmc-pcf8591.h"
#include "driver.h"

extern shmem_t *p;

int init_AD (int channel)
/*
 * Dummy. Just return the channel number.
 */
{
    return channel;
}

void close_AD (int fd)
/*
 * Nothing to do
 */
{
}

int read_AD (int fd, int *value)
/*
 * Get the A/D value from the shared memory area.
 */
{
	*value = p->a2d;
	return 0;
}
