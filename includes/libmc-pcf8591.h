#ifndef __MATRIX_COMPACT_PCF8591_H__
#define __MATRIX_COMPACT_HARDWARE_PCF8591_H__

#define PCF8591_SYS_PATH    "/sys/bus/i2c/drivers/pcf8591/1-0048/"

int init_AD (int channel);
void close_AD (int fd);
int read_AD (int fd, int *value);

#endif
