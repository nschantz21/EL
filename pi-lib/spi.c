/*
 * oled.c
 *
 *  Created on: Feb 8, 2019
 *      Author: Doug Abbott
 *
 *  Derived from a library module from Friendly ARM
 *
 *  Library functions for controlling the SPI bus on the
 *  Raspberry Pi.
 */
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

#include "common.h"
#include "spidev.h"
#include "spi_enum.h"

#define SPI_MAX_SPEED 500000

extern int errno;

static struct spi_ioc_transfer tr = {
		.speed_hz = SPI_MAX_SPEED,
		.bits_per_word = 8,
		.delay_usecs = 10
};

int SPIfail (char *err_string)
{
	printf ("%s %s\n", err_string, strerror (errno));
	return -1;
}

int setSPIReadBitsPerWord (int spi_fd, int bits)
{
	int ret = ioctl (spi_fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
	if (ret < 0)
		return SPIfail ("Can't ioctl SPI_IOC_RD_BITS_PER_WORD:");

	return ret;
}

// FIXME: Need to read spi_mode first
int setSPIBitOrder (int spi_fd, int order)
{
	int ret;
	int spi_mode = 0;

	if (order == LSBFIRST)
	{
		spi_mode |=  SPI_LSB_FIRST;
	} else
	{
		spi_mode &= ~SPI_LSB_FIRST;
	}
	ret = ioctl (spi_fd, SPI_IOC_WR_MODE, &spi_mode);
	if (ret < 0)
		return SPIfail ("Can't ioctl SPI_IOC_WR_MODE:");

	return ret;
}

int initSPI (int channel, int mode)
// Initialize an SPI 'channel' to data transfer 'mode'.
// Return open file descriptor.
{
	int fd;
	char spiDev[20];

	sprintf (spiDev, "/dev/spidev0.%d", channel) ;
    if ((fd = open (spiDev, O_RDWR)) < 0)
    	return SPIfail ("Fail to open SPI device:");

    if (ioctl (fd, SPI_IOC_WR_MODE, &mode) < 0)
	    return SPIfail ("SPI Mode Change failure:");

    // Can't use constants because we're passing by reference
	if (ioctl (fd, SPI_IOC_WR_BITS_PER_WORD, &tr.bits_per_word) < 0)
	    return SPIfail ("SPI BPW Change failure:");

	if (ioctl (fd, SPI_IOC_WR_MAX_SPEED_HZ, &tr.speed_hz) < 0)
	    return SPIfail ("SPI Speed Change failure:");

	return fd;
}

int SPItransferOneByte (int spi_fd, unsigned char byteData)
{
	int ret;

	tr.tx_buf = (unsigned long) &byteData;
	tr.rx_buf = (unsigned long) &byteData;
	tr.len = 1;

	ret = ioctl (spi_fd, SPI_IOC_MESSAGE(1), &tr);
	if (ret < 0)
	{
		printf ("Can't ioctl SPI_IOC_MESSAGE\n");
		return -1;
	}
	return byteData;
}

int SPItransferBytes (
	 int spi_fd
	 , unsigned char *writeData, int writeLen
	 , unsigned char *readBuffer, int readLen
	 )
{
	if (writeLen > readLen)
	{
		writeLen = readLen;
	}
	tr.tx_buf = (unsigned long) writeData;
	tr.rx_buf = (unsigned long) readBuffer;
	tr.len = writeLen;

	int ret = ioctl (spi_fd, SPI_IOC_MESSAGE(1), &tr);
	if (ret < 0)
	{
		printf ("Can't ioctl SPI_IOC_MESSAGE\n");
	}
	return ret;
}

int writeBytesToSPI (int spi_fd, unsigned char *writeData, int writeLen)
{
	tr.tx_buf = (unsigned long) writeData;
	tr.rx_buf = 0;
	tr.len = writeLen;

	int ret = ioctl (spi_fd, SPI_IOC_MESSAGE(1), &tr);
 	if (ret < 0)
	{
		printf ("Can't ioctl SPI_IOC_MESSAGE\n");
	}
	return ret;
}

int readBytesFromSPI (int spi_fd, unsigned char *readBuffer, unsigned int readLen)
{
	tr.tx_buf = 0;
	tr.rx_buf = (unsigned long) readBuffer;
	tr.len = readLen;

	int ret = ioctl (spi_fd, SPI_IOC_MESSAGE(1), &tr);
	if (ret < 0)
	{
		printf ("Can't ioctl SPI_IOC_MESSAGE");
	}
	return ret;
}
