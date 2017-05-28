#include "RaspberryIRQ.h"

enum
{
  MaxIRQNumber = 71
};

static RaspberryInterruptHandler_t raspberryIRQHandlers[RASPBERRY_IRQ_MAX];

void RaspberryRegisterIRQHandler(IRQ_t irq, RaspberryInterruptHandler_t handler)
{
    raspberryIRQHandlers[irq] = handler;
}

void vApplicationIRQHandler()
{
    /* Todo: Write a IRQ routing function which routes to proper IRQ handler. */
}
