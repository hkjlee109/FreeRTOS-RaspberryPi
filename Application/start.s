.extern __bss_start
.extern __bss_end

//.extern FreeRTOS_IRQ_Handler
//.extern FreeRTOS_SVC_Handler
.extern main

.section .init
.global _start

.equ CPSR_MODE_USER,       0x10
.equ CPSR_MODE_FIQ,        0x11
.equ CPSR_MODE_IRQ,        0x12
.equ CPSR_MODE_SVR,        0x13
.equ CPSR_MODE_ABORT,      0x17
.equ CPSR_MODE_UNDEFINED,  0x1B
.equ CPSR_MODE_SYSTEM,     0x1F
.equ CPSR_MODE_MASK,       0x1F

.equ CPSR_IRQ_INHIBIT,     0x80
.equ CPSR_FIQ_INHIBIT,     0x40
.equ CPSR_THUMB,           0x20

_start:
  ldr pc, _reset_vector
  ldr pc, _undefined_instruction_vector
  ldr pc, _software_interrupt_vector
  ldr pc, _prefetch_abort_vector
  ldr pc, _data_abort_vector
  ldr pc, _unused_vector
  ldr pc, _interrupt_vector
  ldr pc, _fast_interrupt_vector

_reset_vector:                   .word _reset
_undefined_instruction_vector:   .word _undefined_instruction
_software_interrupt_vector:      .word _software_interrupt
_prefetch_abort_vector:          .word _prefetch_abort
_data_abort_vector:              .word _data_abort
_unused_vector:                  .word _unused
_interrupt_vector:               .word _interrupt
_fast_interrupt_vector:          .word _fast_interrupt

_reset:
	cpsid if

_check_HYP_mode:
	mrs r0, cpsr_all
	and r0, r0, #0x1F
	mov r8, #0x1A
	cmp r0, r8
	beq _quit_HYP_mode
	b _boot

_quit_HYP_mode:
	ldr r1, =_boot
	msr ELR_hyp, r1
	mrs r1, cpsr_all
	and r1, r1, #CPSR_MODE_MASK
	orr r1, r1, #CPSR_MODE_SVR
	msr SPSR_hyp, r1
	eret

_boot:
  mov    r0, #0x8000
  mov    r1, #0x0000
  ldmia  r0!,{r2, r3, r4, r5, r6, r7, r8, r9}
  stmia  r1!,{r2, r3, r4, r5, r6, r7, r8, r9}
  ldmia  r0!,{r2, r3, r4, r5, r6, r7, r8, r9}
  stmia  r1!,{r2, r3, r4, r5, r6, r7, r8, r9}

  mov r0, #(CPSR_MODE_IRQ | CPSR_IRQ_INHIBIT | CPSR_FIQ_INHIBIT )
  msr cpsr_c, r0
  mov sp, #(63 * 1024 * 1024)

  mov r0, #(CPSR_MODE_SVR | CPSR_IRQ_INHIBIT | CPSR_FIQ_INHIBIT)
  msr cpsr_c, r0
  mov sp, #(64 * 1024 * 1024)

  ldr r0, =__bss_start
	ldr r1, =__bss_end

	mov r2, #0

_bss_init:
	cmp 	r0,r1
	it		lt
	strlt	r2,[r0], #4
	blt		_bss_init

  bl main

_loop:
  b _loop


_undefined_instruction:
	b _undefined_instruction

_software_interrupt:
	b _software_interrupt

_prefetch_abort:
	b _prefetch_abort

_data_abort:
	b _data_abort

_unused:
	b _unused

_interrupt:
	b _interrupt

_fast_interrupt:
	b _fast_interrupt
