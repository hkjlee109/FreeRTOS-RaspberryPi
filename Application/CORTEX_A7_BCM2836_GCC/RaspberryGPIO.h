#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

#define RASPBERRY_GPIO_BASE  0x3F200000UL

typedef struct
{
    volatile uint32_t GPFSEL0;
    volatile uint32_t GPFSEL1;
    volatile uint32_t GPFSEL2;
    volatile uint32_t GPFSEL3;
    volatile uint32_t GPFSEL4;
    volatile uint32_t GPFSEL5;
    volatile uint32_t Reserved0;
    volatile uint32_t GPSET0;
    volatile uint32_t GPSET1;
    volatile uint32_t Reserved1;
    volatile uint32_t GPCLR0;
    volatile uint32_t GPCLR1;
    volatile uint32_t Reserved2;
    volatile uint32_t GPLEV0;
    volatile uint32_t GPLEV1;
    volatile uint32_t Reserved3;
    volatile uint32_t GPEDS0;
    volatile uint32_t GPEDS1;
    volatile uint32_t Reserved4;
    volatile uint32_t GPREN0;
    volatile uint32_t GPREN1;
    volatile uint32_t Reserved5;
    volatile uint32_t GPFEN0;
    volatile uint32_t GPFEN1;
    volatile uint32_t Reserved6;
    volatile uint32_t GPHEN0;
    volatile uint32_t GPHEN1;
    volatile uint32_t Reserved7;
    volatile uint32_t GPLEN0;
    volatile uint32_t GPLEN1;
    volatile uint32_t Reserved8;
    volatile uint32_t GPAREN0;
    volatile uint32_t GPAREN1;
    volatile uint32_t Reserved9;
    volatile uint32_t GPAFEN0;
    volatile uint32_t GPAFEN1;
    volatile uint32_t Reserved10;
    volatile uint32_t GPPUD;
    volatile uint32_t GPPUDCLK0;
    volatile uint32_t GPPUDCLK1;
    volatile uint32_t Reserved11;
} RaspberryGPIO_t;

RaspberryGPIO_t * GetRaspberryGPIO();

#endif
