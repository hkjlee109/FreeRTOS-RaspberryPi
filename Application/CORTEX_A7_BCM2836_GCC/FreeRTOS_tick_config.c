#include <stdint.h>

#include "FreeRTOS.h"
#include "task.h"
#include "portmacro.h"

#include "RaspberryTimer.h"
#include "RaspberryInterruptController.h"
#include "RaspberryIRQ.h"

extern void FreeRTOS_Tick_Handler();

enum
{
    /* Raspberry Pi 2 GPU clock is 250MHz.                      *
     * To meet the 1MHz of tick, we set prescale value to 250.  */
    PreScaleConstant = 0xF9
};

void vConfigureTickInterrupt()
{
    uint32_t matchValue;
    RaspberryTimer_t* timer = GetRaspberryTimer();

    matchValue = configCPU_CLOCK_HZ / configTICK_RATE_HZ;
	  matchValue = matchValue / (PreScaleConstant + 1);

	  portCPU_IRQ_DISABLE();

	  timer->control    = RASPBERRY_TIMER_CONTROL_DISABLE |
	                    RASPBERRY_TIMER_CONTROL_INTERRUPT_DISABLE;
	  timer->load       = matchValue;
	  timer->reload     = matchValue;
	  timer->preDivider = PreScaleConstant;
	  timer->IRQClear   = 0;
    timer->control    = RASPBERRY_TIMER_CONTROL_ENABLE |
	                    RASPBERRY_TIMER_CONTROL_INTERRUPT_ENABLE;

    RaspberryRegisterIRQHandler(
        RASPBERRY_IRQ_TIMER_0,
        (RaspberryInterruptHandler_t)FreeRTOS_Tick_Handler);

    RaspberryIRQEnable(RASPBERRY_IRQ_TIMER_0);

    portCPU_IRQ_ENABLE();
}

void vClearTickInterrupt( void )
{
    RaspberryTimer_t* timer = GetRaspberryTimer();

    timer->IRQClear = 1;
}
