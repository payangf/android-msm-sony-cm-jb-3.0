.section .symtab, "aw"
.long 0
 
.section .shstrtab, "aw"
.long 0

.type __FRAME_END__, #object
.section eh_frame, "aw"
.align
