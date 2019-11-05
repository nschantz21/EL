/*
 * hmc5883.c
 *
 *  Created on: Aug. 1, 2019
 *      Author: doug
 *
 * Set of library functions for accessing the HMC5883 magnetometer
 * on the Matrix Compact board
 *
 * Before invoking these functions, modprobe hmc5843_i2c.
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#include "common.h"
#include "libmc-filectl.h"
#include "libmc-hmc5883.h"

int hmc5883Read (int16_t fds[], int16_t data[])
/*
 * Returns raw magnetometer data from the three axis
 * file descriptor fds[] in data[]
 */
{
    int i;

    for (i = 0; i < 3; i++)
    {
    /*
     * lseek is necessary because the data file only returns
     * one value before reaching end of file.
     */
        lseek (fds[i], 0, SEEK_SET);
    	if (read (fds[i], &data[i], 2) < 0)
    		return -1;
    }
    return 6;
}

int hmc5883Init (int16_t fds[])
/*
 * Initializes an HMC5883 magnetometer device. fds[] is an array
 * of three integers where file descriptors for the raw x, y, and
 * z readings.
 */
{
    int fd;
	
    if ((fd = open (HMC5883_SYS_PATH"new_device", O_WRONLY)) < 0)
	{
        perror ("Fail to open I2C new_device file");
        return -1;
    }
    if (write (fd, "hmc5883 0x1e", 12) < 0)
    {
    	close (fd);
    	perror ("Couldn't write to new_device");
    	return -1;
    }
    close (fd);

    fds[0] = open (HMC5883_SYS_PATH"1-001e/iio:device0/in_magn_x_raw", O_RDONLY);
    fds[1] = open (HMC5883_SYS_PATH"1-001e/iio:device0/in_magn_y_raw", O_RDONLY);
    fds[2] = open (HMC5883_SYS_PATH"1-001e/iio:device0/in_magn_z_raw", O_RDONLY);

    if ((fds[0] | fds[1] | fds[2]) == -1)
    	return -1;
    return 0;
}

void hmc5883DeInit (int16_t fds[])
{
	int i, fd;

	for (i = 0; i < 3; i++)
		close (fds[i]);

	fd = open (HMC5883_SYS_PATH"delete_device", O_WRONLY);
	if (write (fd, "0x1e", 4) < 0)
	{
		perror ("Couldn't write delete_device");
	}
	close (fd);
}
