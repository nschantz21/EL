/*
 * pcf8591.c
 *
 *  Created on: Jan 11, 2019
 *      Author: Doug Abbott
 *
 *  Derived from a library module from Friendly ARM
 *
 * Library functions for accessing the pcf8591 ADC converter 
 * through the /sys file system.
 *
 * Before invoking these functions, install kernel module pcf8591.
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "common.h"
#include "libmc-pcf8591.h"

int init_AD (int channel)
/*
 * Find the data file for 'channel'. On success return the open
 * file descriptor.
 */
{
    int fd, existFlag = 0;
    DIR *d;
    char ch_no;
    struct dirent *de;
    char filename[100];
    const char *dev_string = "pcf8591 0x48";
/*
 * Find the input file for 'channel'
 */
    if (!(d = opendir (PCF8591_SYS_PATH)))
    { // Instantiate the pcf8591
    	fd = open ("/sys/bus/i2c/devices/i2c-1/new_device", O_WRONLY);
    	write (fd, dev_string, 12);
    	close (fd);
    	usleep (100000);	// We need a delay here for some reason

        if (!(d = opendir (PCF8591_SYS_PATH)))
        { // Something's wrong
			printf ("Fail to opendir %s\n", PCF8591_SYS_PATH);
			return -1;
        }
    }
    while ((de = readdir(d)))
    {
        if (de->d_name[0] == '.')
            continue;
        // Is this an input channel data file?
        ch_no = de->d_name[2];
        if ((ch_no < '0') || (ch_no > '3'))
        	continue;
        // Is it the right channel number?
        sprintf (filename, "%s%s", PCF8591_SYS_PATH, de->d_name);
        if ((ch_no - '0') == channel)
        	if (access (filename, F_OK) != -1)
        	{
        		existFlag = 1;
        		break;
        	}
    }
    closedir (d);

    if (existFlag == 0)
    {
        printf ("Failed to access pcf8591 sys file\n");
        return -1;
    }
    return open (filename, O_RDONLY);
}

void close_AD (int fd)
/*
 * Trivial function to close an open /sys file for the
 * pcf8591.
 */
{
    close (fd);
}

int read_AD (int fd, int *value)
/*
 * Reads file descriptor 'fd', which is assumed open to an input
 * data file in /sys for the pcf8591. Data is returned in 'value'.
 * Return 0 on success.
 */
{
    char buff[10];
    /*
     * lseek is necessary because the data file only returns
     * one value before reaching end of file.
     */
    lseek (fd, 0, SEEK_SET);
    if (read (fd, buff, sizeof (buff)) > 0)
    {
        *value = atoi (buff)/10;
        return 0;
    }
    else
    {
        printf ("Invalid data\n");
        return -1;
    }
}
