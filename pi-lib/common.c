/*
 * common.c
 *
 *  Created on: Jan 11, 2019
 *      Author: Doug Abbott
 *
 *  Derived from a library module from Friendly ARM
 *
 *  Library functions for manipulating /sys files related
 *  to Raspberry Pi hardware.
 */
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stddef.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include "common.h"

size_t writeValueToFile (char* fileName, char* buff)
/*
 * Write the string in 'buff' to 'fileName'. Return
 * number of bytes written.
 */
{
    size_t ret;
    int fp = open (fileName, O_WRONLY);
    if (fp < 0)
    {
        printf ("Unable to open file %s for writing: %s\n", fileName, strerror (errno));
        ret = -1;
    }
    else
    {
        if ((ret = write (fp, buff, strlen(buff))) < 0)
        	printf ("Unable to write to %s: %s\n", fileName, strerror (errno));
        close (fp);
    }
    return ret;
}


size_t writeIntValueToFile (char* fileName, int value)
/*
 * Write integer 'value' to 'filename'. Return string
 * length of 'value'.
 */
{
    char buff[20];

    sprintf (buff, "%d", value);
    return writeValueToFile (fileName, buff);
}


int readValueFromFile (char* fileName, char* buff, int len)
/*
 * Read from 'filename' into 'buff' that is 'len' bytes
 * long. Return 0 on success, -1 otherwise.
 */
{
    int ret = -1;
    int fp = open (fileName, O_RDONLY);

    if (fp < 0)
    {
        printf ("Unable to open file %s for reading: %s\n",fileName, strerror (errno));
        return -1;
    }
    else
    {
        if (read (fp, buff, len) > 0)
            ret = 0;
        else
        	printf ("Unable to read from %s: %s\n", fileName, strerror (errno));

    }
    close (fp);
    return ret;
}

int readIntValueFromFile (char* fileName)
/*
 * Read and return an integer value from 'filename'
 */
{
    char buff[80];
    memset (buff, 0, sizeof(buff));
    int ret = readValueFromFile (fileName, buff, sizeof(buff));
    if (ret == 0)
    {
        return atoi(buff);
    }
    return ret;
}
