OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")
OUTPUT_ARCH(arm)

ENTRY(_start):
sections
{
    . = _start;
    .sym    : { *(.sym.start) }
    .text   : ALIGN(4) { *(.text.start) *(.text*)}
    .rodata : ALIGN(4) { *(.rodata*) }
    .data   : ALIGN(4) { *(.data*) *(.bss* COMMON)}
    . = ALIGN(4);
}
