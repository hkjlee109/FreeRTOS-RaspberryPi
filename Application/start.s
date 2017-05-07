.extern FreeRTOS_IRQ_Handler
.extern FreeRTOS_SVC_Handler
.extern main

.section .init
.global _start

.equ CPSR_MODE_USER,       0x10
.equ CPSR_MODE_FIQ,        0x11
.equ CPSR_MODE_IRQ,        0x12
.equ CPSR_MODE_SVR,        0x13
.equ CPSR_MODE_ABORT,      0x17
.equ CPSR_MODE_UNDEFINED,  0x1B
.equ CPSR_MDOE_SYSTEM,     0x1F

.equ CPSR_IRQ_INHIBIT,     0x80
.equ CPSR_FIQ_INHIBIT,     0x40
.equ CPSR_THUMB,           0x20

_start:
  ldr pc, reset_vector
  ldr pc, undefined_instruction_vector
  ldr pc, software_interrupt_vector
  ldr pc, prefetch_abort_vector
  ldr pc, data_abort_vector
  ldr pc, unused_vector
  ldr pc, interrupt_vector
  ldr pc, fast_interrupt_vector
  
reset_vector:                   .word reset
undefined_instruction_vector:   .word reset
software_interrupt_vector:      .word FreeRTOS_SVC_Handler
prefetch_abort_vector:          .word reset
data_abort_vector:              .word reset
unused_vector:                  .word reset
interrupt_vector:               .word FreeRTOS_IRQ_Handler
fast_interrupt_vector:          .word reset

reset: 
  mov    r0, #0x8000
  mov    r1, #0x0000
  ldmia  r0!,{r2, r3, r4, r5, r6, r7, r8, r9}
  stmia  r1!,{r2, r3, r4, r5, r6, r7, r8, r9}
  ldmia  r0!,{r2, r3, r4, r5, r6, r7, r8, r9}
  stmia  r1!,{r2, r3, r4, r5, r6, r7, r8, r9}

  mov r0, #(CPSR_MODE_IRQ | CPSR_IRQ_INHIBIT | CPSR_FIQ_INHIBIT)
  msr cpsr_c, r0
  mov sp, #(63 * 1024 * 1024)
  
  mov r0, #(CPSR_MODE_SVR | CPSR_IRQ_INHIBIT | CPSR_FIQ_INHIBIT)
  msr cpsr_c, r0
  mov sp, #(64 * 1024 * 1024)

  bl main
