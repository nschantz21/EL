/*
    Declarations tying thermostat.c to monitor.c
*/
extern unsigned int setpoint, limit, deadband;
extern int curtemp;
extern pthread_mutex_t paramMutex;
extern int createThread (void);
extern void terminateThread (void);
