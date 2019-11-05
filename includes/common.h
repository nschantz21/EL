 #ifndef _COMMON_H_
 #define _COMMON_H_

#include <unistd.h>

#define __DEBUG

#ifdef __DEBUG
    #define DEBUG(format, args...) \
        printf("FAHW-Lib: " format, ## args)
#else
    #define DEBUG(format, args...)
#endif


extern size_t writeValueToFile (char* fileName, char* buff);
extern size_t writeIntValueToFile (char* fileName, int value);
extern int readValueFromFile( char* fileName, char* buff, int len);
extern int readIntValueFromFile (char* fileName);

#endif
