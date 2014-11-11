/*
 * link.ld -- Base on https://github.com/arjun024/mkernel/blob/master/link.ld
 */

OUTPUT_FORMAT(elf32-i386)
ENTRY(start)
SECTIONS
 {
   . = 0x100000;
   .text : { *(.text) }
   .data : { *(.data) }
   .bss  : { *(.bss)  }
 }
