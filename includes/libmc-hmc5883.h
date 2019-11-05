#ifndef __MATRIX_COMPACT_HMC5883_H__
#define __MATRIX_COMPACT_HMC5883_H__

#define HMC5883_SYS_PATH    "/sys/bus/i2c/devices/i2c-1/"

#define WriteAddress      (0x3C)
#define ReadAddress       (0x3D)
#define HMC5883_ADDRESS   (0x1E)
#define PI                (3.14159265)

int hmc5883Read (int16_t fds[], int16_t data[]);
int hmc5883Init (int16_t fds[]);
void hmc5883DeInit (int16_t fds[]);

#endif
