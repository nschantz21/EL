#ifndef __MATRIX_COMPACT_FILECTRL_H__
#define __MATRIX_COMPACT_FILECTRL_H__

int openHW(const char *devName, int flags);
int writeHW(int fd, const void *_data, size_t len);
int readHW(int fd, void *_data, size_t len);
int selectHW(int fd, int sec, int usec);
void closeHW(int fd);
int ioctlWithIntValue(int fd, int cmd, int value);

#endif
