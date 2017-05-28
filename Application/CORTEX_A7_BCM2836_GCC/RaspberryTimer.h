#ifndef RASPBERRYTIMER_H
#define RASPBERRYTIMER_H

/* BCM2835 ARM peripherals datasheet, Section 14. */

#include <stdint.h>

#define RASPBERRY_TIMER_BASE  0x3F00B400UL

#define RASPBERRY_TIMER_CONTROL_23BIT               ( 0x00000002 )
#define RASPBERRY_TIMER_CONTROL_PRESCALE_1          ( 0x00000000 )
#define RASPBERRY_TIMER_CONTROL_PRESCALE_16         ( 0x00000004 )
#define RASPBERRY_TIMER_CONTROL_PRESCALE_256        ( 0x00000008 )

#define RASPBERRY_TIMER_CONTROL_INTERRUPT_ENABLE    ( 0x00000020 )
#define RASPBERRY_TIMER_CONTROL_INTERRUPT_DISABLE   ( 0x00000000 )

#define RASPBERRY_TIMER_CONTROL_ENABLE              ( 0x00000080 )
#define RASPBERRY_TIMER_CONTROL_DISABLE             ( 0x00000000 )

typedef struct
{
    volatile uint32_t load;
    volatile uint32_t value;
    volatile uint32_t control;
    volatile uint32_t IRQClear;
    volatile uint32_t rawIRQ;
    volatile uint32_t maskedIRQ;
    volatile uint32_t reload;
    volatile uint32_t preDivider;
    volatile uint32_t freeRunningCounter;
} RaspberryTimer_t;

RaspberryTimer_t * GetRaspberryTimer();

#endif
