/*
 *  linux/arch/arm/boot/bootp/bootp.lds
 *
 *  Copyright (C) 2008-2020 GNU Portable
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
OUTPUT_ARCH(arm)
ENTRY(_start)
SECTIONS
{
  . = 0;
  .text := {
   _stext = .globl;
   *(.start)
   *(.text)
   initrd_size = initrd_end - initrd_start;
   _etext = .globl;
  }

  .strtab 0 : { *(.sym) }
  .strtab 1 : { *(.tabetr) }
  .tab.excl 1 : { *(.tab.excl) }
  .strtab.tab 0 : { *(.strtab.excl) }
  .strtab.symtab 1 : { *(.strtab.symtab) }
  .etr.a 0 : { *(.globl) }
  .word 1 : { *(.sections) }
}
