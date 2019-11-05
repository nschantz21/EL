/*
 * gpio.c
 *
 *  Created on: Jan 11, 2019
 *      Author: Doug Abbott
 *
 *  Derived from a library module from Friendly ARM
 *
 *  Library functions for manipulating Raspberry Pi GPIO
 *  bits through the /sys file system.
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "common.h"
#include "libmc-gpio.h"

int exportGPIOPin (int pin)
/*
 * Make GPIO pin 'pin' visible in /sys/class/gpio. Returns
 * a file descriptor for the corresponding value file.
 */
{
    int ret = writeIntValueToFile ("/sys/class/gpio/export", pin);
    if (ret > 0)
    {
        GPIO_FILENAME (pin, "value");
        return open (fileName, O_RDWR);
    }
    else
        return -1;
}

int unexportGPIOPin (int pin)
/*
 * Removes the entry in /sys/class/gpio for 'pin'.
 */
{
    return writeIntValueToFile ("/sys/class/gpio/unexport", pin);
}
/*
 * Note that GPIO_FILENAME() declares a string 'fileName'.
 */

int getGPIOValue (int gpiofd)
/*
 * Return the current state of 'gpiofd', which is expected
 * to be an open file descriptor to the value file for a
 * gpio pin.
 */
{
    char buff[10] = {0};
    size_t res;
/*
 * lseek is necessary because the value file only returns
 * one value before reaching end of file.
 */
    lseek (gpiofd, 0, SEEK_SET);
    if ((res = read (gpiofd, buff, sizeof (buff))) > 0)
    {
    	return atoi(buff);
    }
    else if (res < 0)
    {
    	printf ("Unable to read from value file: %s\n", strerror (errno));
    	return -1;
    }
    return -1;
}

size_t setGPIOValue (int gpiofd, int value)
/*
 * Sets the GPIO pin associated with the open file
 * descriptor to 'value' (0 or 1). The pin must be
 * configured as output. Returns positive value on success.
 */
{
    char buff[10];
    int ret;

    sprintf (buff, "%d", value);
    if ((ret = write (gpiofd, buff, strlen(buff))) > 0)
    		return ret;
    else
    {
    	printf ("Unable to write to value file: %s\n", strerror (errno));
    	return -1;
    }
}

int setGPIODirection (int pin, int direction)
/*
 * Set the 'direction' (in or out) of 'pin'.
 */
{
    static char *directionStr[2] = {"in", "out"};
    GPIO_FILENAME (pin, "direction");

    if ((direction < GPIO_IN) || (direction > GPIO_OUT))
    {
        printf ("direction must be 1 or 2,  1->in, 2->out\n");
        return -1;
    }
    return writeValueToFile (fileName, directionStr[direction - 1]);
}

int getGPIODirection (int pin)
/*
 * Return the direction (in or out) if 'pin'.
 */
{
    char buff[20] = {0};
    int direction;
    int ret;
    GPIO_FILENAME (pin, "direction");

    ret = readValueFromFile (fileName, buff, sizeof(buff));
    if (ret >= 0)
    {
        if (strncasecmp (buff, "out", 3) == 0)
        {
            direction = GPIO_OUT;
        }
        else if (strncasecmp (buff, "in", 2) == 0)
        {
            direction = GPIO_IN;
        }
        else
        {
            printf ("direction wrong, must be in or out,  but is %s\n", buff);
            return -1;
        }
        return direction;
    }
    return ret;
}
int setGPIOLow (int pin, int low)
/*
 * Set active state (low or high) of 'pin'.
 */
{
    GPIO_FILENAME (pin, "active_low");

    if ((low < GPIO_ACTIVE_HIGH) || (low > GPIO_ACTIVE_LOW))
    {
        printf ("Active sense must be 0 or 1,  0->high, 1->low\n");
        return -1;
    }
    return writeIntValueToFile (fileName, low);
}

int getGPIOLow (int pin)
/*
 * Return the active state (low or high) if 'pin'.
 */
{
    GPIO_FILENAME (pin, "active_low");
    return readIntValueFromFile (fileName);
}

