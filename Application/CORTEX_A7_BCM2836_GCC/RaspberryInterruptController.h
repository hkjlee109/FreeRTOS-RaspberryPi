#ifndef RASPBERRYINTERRUPTCONTROLLER_H
#define RASPBERRYINTERRUPTCONTROLLER_H

/* BCM2835 ARM peripherals datasheet, Section 7. */

#include <stdint.h>
#include <RaspberryIRQ.h>

#define RASPBERRY_INTERRUPT_CONTROLLER_BASE  0x3F00B200UL

typedef struct
{
    volatile uint32_t IRQBasicPending;
    volatile uint32_t IRQPending1;
    volatile uint32_t IRQPending2;
    volatile uint32_t FIQControl;
    volatile uint32_t enableIRQs1;
    volatile uint32_t enableIRQs2;
    volatile uint32_t enableBasicIRQs;
    volatile uint32_t disableIRQs1;
    volatile uint32_t disableIRQs2;
    volatile uint32_t disableBasicIRQs;
} RaspberryInterruptController_t;

void RaspberryIRQEnable(IRQ_t irq);
void RaspberryIRQDisable(IRQ_t irq);

#endif
