#ifndef __MATRIX_COMPACT_GPIO_H__
#define __MATRIX_COMPACT_GPIO_H__

#include <stdio.h>

// Direction
#define GPIO_IN                 (1) 
#define GPIO_OUT                (2) 

// Value
#define GPIO_LOW                (0)
#define GPIO_HIGH               (1)

// Active
#define GPIO_ACTIVE_LOW         (1)
#define GPIO_ACTIVE_HIGH        (0)

// Matrix CK revision level
#define REV_A	1
#define REV_B	0

#define PWM0       (96 + 1)  // GPIOD1
#define PWM1       (64 + 13) // GPIOC13
#define PWM2       (64 + 14) // GPIOC14

#define GPIO_FILENAME(pin,field) char fileName[255] = {0}; \
        sprintf (fileName, "/sys/class/gpio/gpio%d/%s", pin, field)

int exportGPIOPin (int pin);
int unexportGPIOPin (int pin);

// GPIO_LOW or GPIO_HIGH
size_t setGPIOValue (int gpiofd, int value);
int getGPIOValue (int gpiofd);

// GPIO_IN or GPIO_OUT
int setGPIODirection (int pin, int direction);
int getGPIODirection (int pin);

// GPIO_ACTIVE_LOW or GPIO_ACTIVE_HIGH
int setGPIOLow (int pin, int low);
int getGPIOLow (int pin);

// LED functions
int init_leds (int rev);
void close_leds (void);
void ledON (int led);
void ledOFF (int led);

// Buzzer functions
int init_buzzer (int rev);
void close_buzzer (int rev);
void buzzer (int freq, int len);

// Pushbutton functions
int init_pbs (void);
void close_pbs (void);
int read_pbs (void);

#endif
