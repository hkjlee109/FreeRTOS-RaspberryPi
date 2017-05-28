#include "RaspberryInterruptController.h"

#define MAP_IRQ_NUMBER_TO_BANK(x)  ( x / 32 )
#define MAP_IRQ_NUMBER_TO_MASK(x)  ( 1 << ( x % 32 ) )

static RaspberryInterruptController_t * controller =
    (RaspberryInterruptController_t *)RASPBERRY_INTERRUPT_CONTROLLER_BASE;

void RaspberryIRQEnable(IRQ_t irq)
{
    uint32_t bank = MAP_IRQ_NUMBER_TO_BANK(irq);
    uint32_t mask = MAP_IRQ_NUMBER_TO_MASK(irq);

    switch(bank)
    {
        case 0:
            controller->enableIRQs1 = mask;
            break;
        case 1:
            controller->enableIRQs2 = mask;
            break;
        case 2:
            controller->enableBasicIRQs = mask;
            break;
    }
}

void RaspberryIRQDisable(IRQ_t irq)
{
  uint32_t bank = MAP_IRQ_NUMBER_TO_BANK(irq);
  uint32_t mask = MAP_IRQ_NUMBER_TO_MASK(irq);

  switch(bank)
  {
      case 0:
          controller->disableIRQs1 = mask;
          break;
      case 1:
          controller->disableIRQs2 = mask;
          break;
      case 2:
          controller->disableBasicIRQs = mask;
          break;
  }
}
