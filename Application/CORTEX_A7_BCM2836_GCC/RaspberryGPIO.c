#include "RaspberryGPIO.h"

static RaspberryGPIO_t * gpio =
    (RaspberryGPIO_t *)RASPBERRY_GPIO_BASE;

RaspberryGPIO_t * GetRaspberryGPIO()
{
    return gpio;
}
