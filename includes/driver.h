/*
	Definitions for the simulation
*/
#ifdef DRIVER
#define SHM_KEY 1234		// shared memory key
typedef struct {
	unsigned int a2d;
	unsigned int GPIOnum;
	unsigned int GPIOvalue;
	pid_t pid;
} shmem_t;
#endif

/*
    Thermostat application definitions
*/
#define COOLER  0
#define ALARM   1

