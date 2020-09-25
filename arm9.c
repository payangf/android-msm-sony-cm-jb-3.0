OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")
OUTPUT_ARCH(arm)

ENTRY
{
       sym    : { *.sym.start }
       text   : { *.text.start *.text* }
       rodata : { *.rodata* }
       data   : { *.data* *.bss* COMMON }
         _start :
};
