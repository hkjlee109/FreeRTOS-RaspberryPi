ENTRY(_start)

MEMORY
{
  RESERVED (r)   : ORIGIN = 0x00000000, LENGTH = 32K
  INIT_RAM (rwx) : ORIGIN = 0x00008000, LENGTH = 32K
  RAM      (rwx) : ORIGIN = 0x00010000, LENGTH = 128M
}

SECTIONS
{
  .init   : { KEEP(*(.init)) } > INIT_RAM = 0
  .text		: { *(.text) } > RAM
  .data 	: { *(.data) } > RAM
  .bss		:
  {
    __bss_start = .;
    *(.bss)
    *(.bss.*)
    __bss_end = .;
  } > RAM

  PROVIDE(__HEAP_START = __bss_end);

  _estack = ORIGIN(RAM) + LENGTH(RAM);
}
