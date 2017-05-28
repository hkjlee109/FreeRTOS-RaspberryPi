#ifndef RASPBERRYIRQ_H
#define RASPBERRYIRQ_H

/* BCM2835 ARM peripherals datasheet, Section 7. */

#include <stdint.h>

#define RASPBERRY_IRQ_TIMER_0          64
#define RASPBERRY_IRQ_MAILBOX_0        65
#define RASPBERRY_IRQ_DOORBELL_0       66
#define RASPBERRY_IRQ_DOORBELL_1       67
#define RASPBERRY_IRQ_GPU_HALT_0       68
#define RASPBERRY_IRQ_GPU_HALT_1       69
#define RASPBERRY_IRQ_ACCESS_ERROR_0   70
#define RASPBERRY_IRQ_ACCESS_ERROR_1   71
#define RASPBERRY_IRQ_MAX              RASPBERRY_IRQ_ACCESS_ERROR_1

typedef uint32_t IRQ_t;
typedef void (*RaspberryInterruptHandler_t)(uint32_t IRQ, void *arg);

void RaspberryRegisterIRQHandler(IRQ_t irq, RaspberryInterruptHandler_t handler);
void vApplicationIRQHandler();

#endif
