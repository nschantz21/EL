/*
 * Support functions for the ADXL34x line of accelerometers
 *
 *  Derived from a library module from Friendly ARM
 *
 *  Before invoking this function install kernel modules:
 *  	adxl34x
 *  	adxl34x-i2c
 */
#include <math.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

#include "common.h"
#include "libmc-filectl.h"
#include "libmc-adxl34x.h"

int adxl34xRead (char *position)
{
    int maxLength = sizeof("(-255, -255, -255)");
    DIR *d;
    struct dirent *de;
    
    if (!(d = opendir (ADXL34X_SYS_PATH)))
	{
        printf ("Fail to opendir %s\n", ADXL34X_SYS_PATH);
        return 0;
    }
    char adxFile[100];
    while ((de = readdir (d)))
	{
        if (de->d_name[0] == '.')
            continue;
        
        sprintf (adxFile, "%s%s/position", ADXL34X_SYS_PATH, de->d_name);
        
        if (access (adxFile, F_OK) != -1)
		{
            break;
        }
    }
    closedir (d);

    memset (position, 0, maxLength);
    if (readValueFromFile (adxFile, position, maxLength) == -1)
	{
        printf ("Fail to read adxl34x\n");
        return -1;
    }
	return strlen (position) + 1;
}
