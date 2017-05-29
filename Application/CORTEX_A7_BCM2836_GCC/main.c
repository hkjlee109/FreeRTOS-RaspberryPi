#include "RaspberryGPIO.h"

int main()
{
    volatile unsigned int count;
    RaspberryGPIO_t * gpio = GetRaspberryGPIO();

    gpio->GPFSEL4 |= (1 << 21);

    while(1)
    {
        for(count = 0; count < 500000; count++) ;

        gpio->GPCLR1 = (1 << 15);

        for(count = 0; count < 500000; count++) ;

        gpio->GPSET1 = (1 << 15);
    }

    return 0;
}
