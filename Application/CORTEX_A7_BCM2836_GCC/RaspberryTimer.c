#include "RaspberryTimer.h"

static RaspberryTimer_t * timer = (RaspberryTimer_t *)RASPBERRY_TIMER_BASE;

RaspberryTimer_t * GetRaspberryTimer()
{
    return timer;
}
