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

  .stab 0 : { *(.stab) }
  .stabstr 0 : { *(.stabstr) }
  .stab.excl 0 : { *(.stab.excl) }
  .stab.exclstr 0 : { *(.stab.exclstr) }
  .stab.attribute 0 : { *(.stab.attribute) }
  .stab.sym 0 : { *(.stab.sym) }
  .word 0 : { *(.sections) }
}
